#include "serial.hpp"
#include "boost_client.hpp"
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

void SerialThread(void);
void ClientThread(void);

int main(int argc, char **argv){

    std::thread SerialTask(SerialThread);
    std::thread ClientTask(ClientThread);

    SerialTask.join();
    ClientTask.join();
}


void SerialThread(){
    SerialPortSampler SerialPort(PORT_NAME, 9600);
    SerialPort.Connect();

    while(1){
        if(!SerialPort.CheckConnectionEstablishment()){
            std::cout << PORT_NAME << "unexpectedly closed" << PORT_NAME << "\n";
            break;
        } 

        SerialPort.SendData("temperature\r");
        QueueMutex.lock();
        queue.push(SerialPort.GetData(DELIMITER));
        QueueMutex.unlock();

        std::this_thread::sleep_for(std::chrono::microseconds(2000000));
    }

}
void ClientThread(){
    LocalHost LocalHostMachine;

    while(1){
        if (!LocalHostMachine.IsConnectionEstablished()){
            std::cout << "Connection broken\n";
        } 
        QueueMutex.lock();
        unsigned int CurrentQueueSize = queue.size();
        QueueMutex.unlock();
        if(0 != CurrentQueueSize){
            QueueMutex.lock();

            if(LocalHostMachine.IsConnectionEstablished()){
                LocalHostMachine.SendData(queue.front());
                std::cout << queue.front();
                queue.pop();
            } else {
                LocalHostMachine.EstablishConnection();
            }
            QueueMutex.unlock();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1500000));
    }
}