#ifndef relog_app_hpp
#define relog_app_hpp

#include "../TcpClient/TcpClient.hpp"
#include "../AppConfigurator/AppConfigurator.hpp"
#include "../CsvWriter/CsvWriter.hpp"
#include "../LogQueue/LogQueue.hpp"
#include "../SerialPort/SerialPort.hpp"
#include "../Timestamp/Timestamp.hpp"

#include <memory>
#include <mutex>
#include <string>
#include <thread>

using std::mutex;
using std::string;
using std::thread;
using std::unique_ptr;

class RelogApp {
 public:
  /** @brief Constructor. Starts the app. */
  RelogApp(int argc, char** argv) noexcept;

 private:
  void Configure();

  void SerialPortThrTarget();
  void ClientThreadTarget(LogStringQueue &ClientQueue);
  void CsvWriterThreadTarget(LogStringQueue &CsvWriterQueue);
  void DistributionThreadTarget();

  unique_ptr<thread> DistributionThread;
  unique_ptr<thread> TcpClientThread;
  unique_ptr<thread> SerialPortThread;
  unique_ptr<thread> CsvWriterThread;

  unique_ptr<AppConfigurator> appConfigurator;
  unique_ptr<LogStringQueue> logQueue;
  unique_ptr<CsvWriter> csvFileWriter;
  Timestamp logTimestamp;

  bool UsingTcpClient;
  bool UsingCsvWriter;
  bool AttachTimestamp;
  bool ScreenOff;
  bool ConfiguredSuccesfully;
};

#endif