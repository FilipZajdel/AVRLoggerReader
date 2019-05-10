#include "relog_app.hpp"
#include "../Config/config.hpp"
#include "../CountingQueue/counting_queue.hpp"


RelogApp::RelogApp(int argc, char **argv) noexcept{

    AppConfigurator = std::move(unique_ptr <Configurator> {new Configurator{argc, argv}});

    UsingTcpClient = false;
    UsingCsvWriter = false;
    AttachTimestamp = false;
    ScreenOff = false;

    try{
        Configure();

        LogQueue = std::move(unique_ptr <LogStringQueue> {new CountingQueue{UsingCsvWriter+UsingTcpClient}});

        SerialPortThread->join();

        if(UsingTcpClient){
            ClientThread->join();
        }

        if(UsingCsvWriter){
            CsvWriterThread->join();
        }       

    } catch(const ConfigurationException &exception){
        // PROGRAM_LOG(exception.what());
        CsvFileWriter->Close();
        // terminate
    }
}

void RelogApp::Configure(){
    try{
        ProgramConfig Config = AppConfigurator->GetConfig();
        SerialPortThread = std::move(unique_ptr<thread>(new thread(&RelogApp::SerialPortThrTarget, this,Config.DeviceName, Config.BaudRate)));

        for(auto Feature : Config.ChosenFeatures){
            switch(Feature){
                case ProgramConfig::FILE_LOG:
                    CsvFileWriter = std::move(unique_ptr<CsvWriter> {new CsvWriter{Config.Filename}});
                    CsvWriterThread = std::move(unique_ptr<thread>(new thread(&RelogApp::CsvWriterThreadTarget, this, Config.Filename)));
                    UsingCsvWriter = true;
                    break;
                case ProgramConfig::NETWORK_LOG:
                    ClientThread = std::move(unique_ptr<thread>(new thread(&RelogApp::ClientThreadTarget, this,Config.Ip, Config.Port)));
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
    } catch (const std::exception &exception){
        AppConfigurator->ShowDescription();
        throw ConfigurationException{};
    }
}

void RelogApp::SerialPortThrTarget(string PortName, unsigned BaudRate){
    
    SerialPort serialPort{PortName, BaudRate};
    serialPort.Connect();

    while(serialPort){
        Data ReceivedData;
        serialPort >> ReceivedData;

        LogQueue->Push(ReceivedData.Content);

        if(ScreenOff){
            continue;
        }

        // only for now
        if(AttachTimestamp){
            PROGRAM_LOG("["+LogTimestamp.GetCurrentTime()+"] "+ReceivedData.Content);
        } else {
            PROGRAM_LOG(ReceivedData.Content); 
        }
    }
}

void RelogApp::ClientThreadTarget(string Ip, string Port){

    Client client{Port, Ip};
    client.EstablishConnection();

    while(client.IsConnectionEstablished()){

        if(!LogQueue->IsEmpty()){

            client.SendData("["+LogTimestamp.GetCurrentTime()+"] "+LogQueue->Front());
        }
    }

    PROGRAM_LOG("["+LogTimestamp.GetCurrentTime()+"]" + " TCP Connection on {" + Ip + " " + Port + "} is not alive\n");
}

void RelogApp::CsvWriterThreadTarget(string Filepath){

    while(1){

        if(!LogQueue->IsEmpty()){
            CsvFileWriter->Write(vector<string> {LogTimestamp.GetTimestamp(), LogQueue->Front()});
        }
    }
}
