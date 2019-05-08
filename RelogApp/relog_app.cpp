#include "relog_app.hpp"
#include "../Config/config.hpp"

RelogApp::RelogApp(int argc, char **argv) noexcept{

    AppConfigurator = new Configurator{argc, argv};
    LogQueue = new LogStringQueue{};
    UsingTcpClient = false;

    try{
        Configure();

        SerialPortThread->join();

        if(UsingTcpClient){
            ClientThread->join();
        }

    } catch(const ConfigurationException &exception){
        // PROGRAM_LOG(exception.what());
        // terminate
    }
}

void RelogApp::Configure(){
    try{
        ProgramConfig Config = AppConfigurator->GetConfig();
        SerialPortThread = std::move(unique_ptr<thread>(new thread(&RelogApp::SerialPortThrTarget, this,Config.DeviceName, Config.BaudRate)));

        for(auto Feature : Config.ChosenFeatures){
            switch(Feature){
                case ProgramConfig::SCREEN_LOG:
                    PROGRAM_LOG("Feature SCREEN_LOG");
                    break;
                case ProgramConfig::FILE_LOG:
                    PROGRAM_LOG("Feature FILE_LOG");
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
                    PROGRAM_LOG("Feature SHOW_TIMESTAMP");
                    break;
                case ProgramConfig::SCREEN_OFF:
                    PROGRAM_LOG("Feature SCREEN_OFF");
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

        PROGRAM_LOG(ReceivedData.Content); // only for now
        LogQueue->Push(ReceivedData.Content);
    }
}

void RelogApp::ClientThreadTarget(string Ip, string Port){

    Client client{Port, Ip};
    client.EstablishConnection();

    while(client.IsConnectionEstablished()){

        if(!LogQueue->IsEmpty()){

            client.SendData(LogQueue->Front());
            LogQueue->ClearFront();
        }
    }

    PROGRAM_LOG("TCP Connection on {" + Ip + " " + Port + "} is not alive\n");
}