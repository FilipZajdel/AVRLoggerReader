#include "relog_app.hpp"

RelogApp::RelogApp(int argc, char **argv) noexcept{

    AppConfigurator = new Configurator{argc, argv};
    LogQueue = new LogStringQueue{};

    try{
        Configure();

        if(nullptr != ClientThread){
            ClientThread->join();
        }
        SerialPortThread->join();

    } catch(const ConfigurationException &exception){
        // terminate
    }
}

void RelogApp::Configure(){
    try{
        ProgramConfig Config = AppConfigurator->GetConfig();
        SerialPortThread = new thread(&RelogApp::SerialPortThrTarget, this,Config.DeviceName, Config.BaudRate);

        for(auto Feature : Config.ChosenFeatures){
            switch(Feature){
                case ProgramConfig::SCREEN_LOG:
                    PROGRAM_LOG("Feature SCREEN_LOG");
                    break;
                case ProgramConfig::FILE_LOG:
                    PROGRAM_LOG("Feature FILE_LOG");
                    break;
                case ProgramConfig::NETWORK_LOG:
                    ClientThread = new thread{&RelogApp::ClientThreadTarget, this,Config.Ip, Config.Port};
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
    } catch (const ConfigurationException &exception){
        AppConfigurator->ShowDescription();
        throw ConfigurationException{};
        return;
    }
}

void RelogApp::SerialPortThrTarget(string PortName, unsigned BaudRate){
    
    SerialPort serialPort{PortName, BaudRate};
    serialPort.Connect();

    while(serialPort){
        Data ReceivedData;
        Data DataToSend{"hey esp32"};

        serialPort << DataToSend;
        serialPort >> ReceivedData;

        PROGRAM_LOG(ReceivedData.Content) << std::endl;

        LogQueue->Push(ReceivedData.Content);

        std::this_thread::sleep_for(std::chrono::microseconds(200000));
    }
}

void RelogApp::ClientThreadTarget(string Ip, string Port){
    Client client{Port, Ip};

    while(1){

        if (!client.IsConnectionEstablished()){
            std::cout << "Connection broken\n";
        } 

        if(!LogQueue->IsEmpty()){

            if(client.IsConnectionEstablished()){
                client.SendData(LogQueue->Front());
                LOG(std::cout << LogQueue->Front());
                LogQueue->ClearFront();
            } else {
                client.EstablishConnection();
            }
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1500000));
    }
}