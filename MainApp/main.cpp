#include "serial_port.hpp"
#include "tcp_client.hpp"
#include <thread>
#include <queue>
#include <mutex>
#include <string>
#include <boost/program_options.hpp>
#include <argument_parser.hpp>
#include <configurator.hpp>
#include "../Config/config.hpp"

#include <relog_app.hpp>

using namespace boost::program_options;

using std::string;
std::mutex QueueMutex;
std::queue<std::string> MainQueue;

void ClientThread(void);
void SerialThread(void);
void FileWriterThread(string FileName);

// int main(int argc, char **argv){

//     std::thread ClientTask(ClientThread);
//     std::thread SerialTask(SerialThread);

//     SerialTask.join();
//     ClientTask.join();

//     return 0;
// }

int main(int argc, char **argv){
    RelogApp App{argc, argv};
}

// int main(int argc, char **argv){
//     Configurator *configurator;
//     try{
//         configurator = new Configurator{argc, argv};
//         ProgramConfig programConfig = configurator->GetConfig();

//         for(int Feature : programConfig.ChosenFeatures){
//             switch(Feature){
//                 case ProgramConfig::SCREEN_LOG:
//                     PROGRAM_LOG("Feature SCREEN_LOG");
//                     break;
//                 case ProgramConfig::FILE_LOG:
//                     PROGRAM_LOG("Feature FILE_LOG");
//                     break;
//                 case ProgramConfig::NETWORK_LOG:
//                     PROGRAM_LOG("Feature NETWORK_LOG");
//                     break;
//                 case ProgramConfig::ENABLE_TRANSMITTING:
//                     PROGRAM_LOG("Feature TRANSMITTING");
//                     break;
//                 case ProgramConfig::SHOW_HELP:
//                     PROGRAM_LOG("Feature SHOW_HELP");
//                     break;
//                 case ProgramConfig::SHOW_TIMESTAMP:
//                     PROGRAM_LOG("Feature SHOW_TIMESTAMP");
//                     break;
//                 case ProgramConfig::SCREEN_OFF:
//                     PROGRAM_LOG("Feature SCREEN_OFF");
//                     break;
//                 default:
//                     PROGRAM_LOG("Feature UNKNOWN");
//                     break;                    
//             }
//         }
//     } catch (const ConfigurationException &exc){
//         configurator->ShowDescription();
//         return 0;
//     }
// }

void SerialThread(){
    SerialPort serialPort{"/dev/ttyUSB0", 115200};
    serialPort.Connect();

    while(serialPort){
        Data ReceivedData;
        Data DataToSend{"hey esp32"};

        serialPort << DataToSend;
        serialPort >> ReceivedData;

        LOG(ReceivedData.Content) << std::endl;
        
        QueueMutex.lock();
        MainQueue.push(ReceivedData.Content);
        QueueMutex.unlock();

        std::this_thread::sleep_for(std::chrono::microseconds(200000));
    }
}

void ClientThread(){
    Client client{CONFIG_TCP_PORT, CONFIG_LOCAL_IP};

    while(1){
        if (!client.IsConnectionEstablished()){
            std::cout << "Connection broken\n";
        } 
        QueueMutex.lock();
        unsigned int CurrentQueueSize = MainQueue.size();
        QueueMutex.unlock();
        if(0 != CurrentQueueSize){
            QueueMutex.lock();

            if(client.IsConnectionEstablished()){
                client.SendData(MainQueue.front());
                std::cout << MainQueue.front();
                MainQueue.pop();
            } else {
                client.EstablishConnection();
            }
            QueueMutex.unlock();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1500000));
    }
}
