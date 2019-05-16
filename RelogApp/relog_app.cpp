#include "relog_app.hpp"
#include "../Config/config.hpp"
#include "../CountingQueue/counting_queue.hpp"

RelogApp::RelogApp(int argc, char** argv) noexcept {
  AppConfigurator =
      std::move(unique_ptr<Configurator>{new Configurator{argc, argv}});

  UsingTcpClient = false;
  UsingCsvWriter = false;
  AttachTimestamp = false;
  ScreenOff = false;

  try {
    Configure();

    LogQueue = std::move(unique_ptr<LogStringQueue>{
        new CountingQueue{UsingCsvWriter + UsingTcpClient}});
    // LogQueue = std::move(unique_ptr <LogStringQueue> {new LogStringQueue{}});

    if (ConfiguredSuccesfully) {
      SerialPortThread->join();
    }

    if (UsingTcpClient) {
      ClientThread->join();
    }

    if (UsingCsvWriter) {
      CsvWriterThread->join();
    }

  } catch (const ConfigurationException& exception) {
    // PROGRAM_LOG(exception.what());
    if (CsvFileWriter) {
      CsvFileWriter->Close();
    }
    // terminate
  }
}

void RelogApp::Configure() {
  try {
    ProgramConfig Config = AppConfigurator->GetConfig();
    SerialPortThread = std::move(
        unique_ptr<thread>(new thread(&RelogApp::SerialPortThrTarget, this,
                                      Config.DeviceName, Config.BaudRate)));

    for (auto Feature : Config.ChosenFeatures) {
      switch (Feature) {
        case ProgramConfig::FILE_LOG:
          CsvFileWriter =
              std::move(unique_ptr<CsvWriter>{new CsvWriter{Config.Filename}});
          CsvWriterThread = std::move(unique_ptr<thread>(
              new thread(&RelogApp::CsvWriterThreadTarget, this)));
          UsingCsvWriter = true;
          break;
        case ProgramConfig::NETWORK_LOG:
          ClientThread = std::move(unique_ptr<thread>(new thread(
              &RelogApp::ClientThreadTarget, this, Config.Ip, Config.Port)));
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
    AppConfigurator->ShowDescription();
    ConfiguredSuccesfully = false;
    throw ConfigurationException{};
  }
}

void RelogApp::SerialPortThrTarget(string PortName, unsigned BaudRate) {
  SerialPort serialPort{PortName, BaudRate};
  serialPort.Connect();

  while (serialPort) {
    Data ReceivedData;
    serialPort >> ReceivedData;

    std::lock_guard<mutex> QueueLock{QueueMutex};
    LogQueue->Push(ReceivedData.Content);

    if (ScreenOff) {
      continue;
    }

    // only for now
    if (AttachTimestamp) {
      PROGRAM_LOG("[" + LogTimestamp.GetCurrentTime() + "] " +
                  ReceivedData.Content);
    } else {
      PROGRAM_LOG(ReceivedData.Content);
    }
  }
}

void RelogApp::ClientThreadTarget(string Ip, string Port) {
  Client client{Port, Ip};
  client.EstablishConnection();

  while (client.IsConnectionEstablished()) {
    std::lock_guard<mutex> QueueLock{QueueMutex};

    if (!LogQueue->IsEmpty()) {
      try {
        client.SendData("[" + LogTimestamp.GetCurrentTime() + "] " +
                        LogQueue->Front());
      } catch (std::exception& exc) {
        string ExcMessage{exc.what()};
        PROGRAM_LOG(ExcMessage + " in: " + __func__);
      }
    }
  }

  PROGRAM_LOG("[" + LogTimestamp.GetCurrentTime() + "]" +
              " TCP Connection on {" + Ip + " " + Port + "} is not alive\n");
}

void RelogApp::CsvWriterThreadTarget() {
  long RowCtr = 0;

  while (1) {
    std::lock_guard<mutex> QueueLock{QueueMutex};

    if (!LogQueue->IsEmpty()) {
      try {
        string DataToWrite = LogQueue->Front();
        CsvFileWriter->Write(
            vector<string>{LogTimestamp.GetTimestamp(), DataToWrite});
        PROGRAM_LOG(DataToWrite);
      } catch (std::exception& exc) {
        string ExcMessage{exc.what()};
        PROGRAM_LOG(ExcMessage + " in: " + __func__);
      }
      RowCtr++;
    }

    if (RowCtr >= 20) {
      CsvFileWriter->Close();
      break;
    }
  }
}
