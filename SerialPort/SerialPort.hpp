#ifndef serial_port_hpp
#define serial_port_hpp

#include "../Port/Port.hpp"

#include <boost/asio.hpp>

#include <memory>
#include <string>

using boost::asio::io_service;
using boost::asio::serial_port;
using std::string;
using std::unique_ptr;

/** @brief Represents serial port */
class SerialPort : public Port {
 public:
  /** @brief SerialPort constructor
   * @param Name the name of serial port, ex. /dev/ttyUSB0
   * @param BaudRate BaudRate of connection
   */
  SerialPort(std::string Name, long BaudRate);
  virtual ~SerialPort();
  /** @brief Establishes connection with with given name and baudrate
   *
   * Uses 1 parity bit.
   */
  virtual void Connect();
  /** @brief Closes connection */
  virtual void Disconnect();

  /** @brief For using instance of SerialPort like stream */
  virtual operator bool();
  /** @brief Stream operator for writing to SerialPort*/
  virtual Port& operator<<(Data&);
  /** @brief Stream operator for reading to SerialPort*/
  virtual Port& operator>>(Data&);

 private:
  unique_ptr<io_service> SerialService;
  unique_ptr<serial_port> SerialPortHw;

  string ErrorsDetected;
  const string Name;
  const long BaudRate;

  void OnError(string Where, string What);
};

#endif /* serial_hpp */
