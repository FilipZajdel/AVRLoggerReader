#ifndef relog_app_hpp
#define relog_app_hpp

#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "../Client/tcp_client.hpp"
#include "../Configurator/configurator.hpp"
#include "../CsvWriter/csv_writer.hpp"
#include "../LogQueue/log_queue.hpp"
#include "../SerialPort/serial_port.hpp"
#include "../Timestamp/timestamp.hpp"

using std::mutex;
using std::string;
using std::thread;
using std::unique_ptr;

class RelogApp {
 public:
  RelogApp(int argc, char** argv) noexcept;

 private:
  void Configure();

  void SerialPortThrTarget();
  void ClientThreadTarget(LogStringQueue &ClientQueue);
  void CsvWriterThreadTarget(LogStringQueue &CsvWriterQueue);
  void DistributionThreadTarget();

  unique_ptr<thread> DistributionThread;
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
  bool ConfiguredSuccesfully;
};

#endif