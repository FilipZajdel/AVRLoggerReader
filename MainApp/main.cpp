#include "serial_port.hpp"
#include "tcp_client.hpp"
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>

#define PORT_NAME "/dev/ttyUSB0"
#define SAMPLE_DATA "temperature\r"
#define DELIMITER "\r"
#define DEFAULT_DELAY_BETWEEN_SENDING 2000

std::string quit_string = "quit";
std::mutex QueueMutex;
std::queue<std::string> queue;

void ClientThread(void);
void SerialThread(void);

int main(int argc, char **argv){

    std::thread ClientTask(ClientThread);
    std::thread SerialTask(SerialThread);

    SerialTask.join();
    ClientTask.join();

    return 0;
}


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
        queue.push(ReceivedData.Content);
        QueueMutex.unlock();

        std::this_thread::sleep_for(std::chrono::microseconds(200000));
    }
}

void ClientThread(){
    Client client;

    while(1){
        if (!client.IsConnectionEstablished()){
            std::cout << "Connection broken\n";
        } 
        QueueMutex.lock();
        unsigned int CurrentQueueSize = queue.size();
        QueueMutex.unlock();
        if(0 != CurrentQueueSize){
            QueueMutex.lock();

            if(client.IsConnectionEstablished()){
                client.SendData(queue.front());
                std::cout << queue.front();
                queue.pop();
            } else {
                client.EstablishConnection();
            }
            QueueMutex.unlock();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1500000));
    }
}