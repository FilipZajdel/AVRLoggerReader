#include "RelogApp.hpp"
#include "../Config/Config.hpp"

RelogApp::RelogApp(int argc, char** argv) noexcept {
  appConfigurator =
      std::move(unique_ptr<AppConfigurator>{new AppConfigurator{argc, argv}});

  UsingTcpClient = false;
  UsingCsvWriter = false;
  AttachTimestamp = false;
  ScreenOff = false;

  try {
    Configure();
    logQueue = std::move(unique_ptr<LogStringQueue>{new LogStringQueue{}});
    DistributionThread = std::move(unique_ptr<thread>(
        new thread(&RelogApp::DistributionThreadTarget, this)));

    if (ConfiguredSuccesfully) {
      SerialPortThread->join();
      DistributionThread->join();
    }

    if (UsingTcpClient) {
      TcpClientThread->join();
    }

    if (UsingCsvWriter) {
      CsvWriterThread->join();
    }

  } catch (const ConfigurationException& exception) {
    // PROGRAM_LOG(exception.what());
    if (csvFileWriter) {
      csvFileWriter->Close();
    }
    // terminate
  }
}

void RelogApp::Configure() {
  try {
    ProgramConfig Config = appConfigurator->GetConfig();
    SerialPortThread = std::move(
        unique_ptr<thread>(new thread(&RelogApp::SerialPortThrTarget, this)));

    for (auto Feature : Config.ChosenFeatures) {
      switch (Feature) {
        case ProgramConfig::FILE_LOG:
          csvFileWriter =
              std::move(unique_ptr<CsvWriter>{new CsvWriter{Config.Filename}});
          UsingCsvWriter = true;
          break;
        case ProgramConfig::NETWORK_LOG:
          UsingTcpClient = true;
          break;
        case ProgramConfig::ENABLE_TRANSMITTING:
          PROGRAM_LOG("Feature TRANSMITTING");
          break;
        case ProgramConfig::SHOW_HELP:
          PROGRAM_LOG("Feature SHOW_HELP");
          break;
        case ProgramConfig::SHOW_TIMESTAMP:
          AttachTimestamp = true;
          break;
        case ProgramConfig::SCREEN_OFF:
          ScreenOff = true;
          break;
        default:
          PROGRAM_LOG("Feature UNKNOWN");
          break;
      }
    }

    ConfiguredSuccesfully = true;
  } catch (const std::exception& exception) {
    appConfigurator->ShowDescription();
    ConfiguredSuccesfully = false;
    throw ConfigurationException{};
  }
}

void RelogApp::SerialPortThrTarget() {
  ProgramConfig Config = appConfigurator->GetConfig();

  SerialPort serialPort{Config.DeviceName, Config.BaudRate};
  serialPort.Connect();

  while (serialPort) {
    Data ReceivedData;
    serialPort >> ReceivedData;

    logQueue->Push(ReceivedData.Content);
  }
}

void RelogApp::ClientThreadTarget(LogStringQueue& ClientQueue) {
  ProgramConfig Config = appConfigurator->GetConfig();
  TcpClient client{Config.Port, Config.Ip};
  client.EstablishConnection();

  while (client.IsConnectionEstablished()) {
    if (!ClientQueue.IsEmpty()) {
      try {
        client.SendData("[" + logTimestamp.GetCurrentTime() + "] " +
                        ClientQueue.Front());
      } catch (std::exception& exc) {
        string ExcMessage{exc.what()};
        PROGRAM_LOG(ExcMessage + " in: " + __func__);
      }
      ClientQueue.ClearFront();
    }
  }

  PROGRAM_LOG("[" + logTimestamp.GetCurrentTime() + "]" +
              " TCP Connection on {" + Config.Ip + " " + Config.Port +
              "} is not alive\n");
}

void RelogApp::CsvWriterThreadTarget(LogStringQueue& CsvQueue) {
  while (1) {
    if (!CsvQueue.IsEmpty()) {
      try {
        csvFileWriter->Write(
            vector<string>{logTimestamp.GetTimestamp(), CsvQueue.Front()});
      } catch (std::exception& exc) {
        string ExcMessage{exc.what()};
        PROGRAM_LOG(ExcMessage + " in: " + __func__);
      }
      CsvQueue.ClearFront();
    }
  }
}

void RelogApp::DistributionThreadTarget() {
  vector<LogStringQueue*> LogQueues{};

  if (UsingCsvWriter) {
    LogStringQueue *CsvQueue = new LogStringQueue;

    CsvWriterThread = std::move(unique_ptr<thread>(new thread(
        &RelogApp::CsvWriterThreadTarget, this, std::ref(*CsvQueue))));

    LogQueues.push_back(CsvQueue);
  } 

  if (UsingTcpClient) {
    LogStringQueue *TcpQueue = new LogStringQueue;
    TcpClientThread = std::move(unique_ptr<thread>(
        new thread(&RelogApp::ClientThreadTarget, this, std::ref(*TcpQueue))));
    LogQueues.push_back(TcpQueue);
  }

  while (1) {
    if (!logQueue->IsEmpty()) {
      for (auto Queue : LogQueues) {
        Queue->Push(logQueue->Front());
      }

      if (!ScreenOff) {
        if (AttachTimestamp) {
          PROGRAM_LOG("[" + logTimestamp.GetCurrentTime() + "] " +
                      logQueue->Front());
        } else {
          PROGRAM_LOG(logQueue->Front());
        }
      }

      logQueue->ClearFront();
    }
  }

  for(auto Queue : LogQueues){
      delete Queue;
  }
}