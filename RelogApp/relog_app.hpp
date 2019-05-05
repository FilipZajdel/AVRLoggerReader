#ifndef relog_app_hpp
#define relog_app_hpp

#include <thread>
#include <string>

#include "../LogQueue/log_queue.hpp"
#include "../SerialPort/serial_port.hpp"
#include "../Client/tcp_client.hpp"
#include "../Configurator/configurator.hpp"

using std::thread;
using std::string;

class RelogApp{
public:
    RelogApp(int argc, char **argv) noexcept;
private:
    void Configure();
    void SerialPortThrTarget(string PortName, unsigned BaudRate);
    void ClientThreadTarget(string Ip, string Port);
    
    thread *ClientThread;
    thread *SerialPortThread;
    Configurator *AppConfigurator;
    LogStringQueue *LogQueue;
};

#endif