#ifndef relog_app_hpp
#define relog_app_hpp

#include <thread>
#include <string>
#include <memory>

#include "../LogQueue/log_queue.hpp"
#include "../SerialPort/serial_port.hpp"
#include "../Client/tcp_client.hpp"
#include "../Configurator/configurator.hpp"
#include "../CsvWriter/csv_writer.hpp"
#include "../Timestamp/timestamp.hpp"


using std::thread;
using std::string;
using std::unique_ptr;


class RelogApp{
public:
    RelogApp(int argc, char **argv) noexcept;
private:
    void Configure();

    void SerialPortThrTarget(string PortName, unsigned BaudRate);
    void ClientThreadTarget(string Ip, string Port);
    void CsvWriterThreadTarget(string Filepath);
    
    unique_ptr<thread> ClientThread;
    unique_ptr<thread> SerialPortThread;
    unique_ptr<thread> CsvWriterThread;

    unique_ptr<Configurator> AppConfigurator;
    unique_ptr<LogStringQueue> LogQueue;
    unique_ptr<CsvWriter> CsvFileWriter;
    Timestamp LogTimestamp;

    bool UsingTcpClient;
    bool UsingCsvWriter;
    bool AttachTimestamp;
    bool ScreenOff;
};

#endif