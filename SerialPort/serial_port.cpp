#include "serial_port.hpp"
#include <boost/algorithm/string/replace.hpp>
#include <thread>
#include "../Config/config.hpp"

SerialPort::SerialPort(string Name, long BaudRate)
    : Name(Name), BaudRate(BaudRate) {
  SerialService = unique_ptr<io_service>{new boost::asio::io_service()};
  SerialPortHw =
      unique_ptr<serial_port>{new boost::asio::serial_port(*SerialService)};
}
SerialPort::~SerialPort() {
  if (SerialPortHw->is_open()) {
    SerialPortHw->close();
  }
}

void SerialPort::Connect() {
  boost::system::error_code ErrorCode;

  try {
    if (SerialPortHw->is_open()) {
      std::cout << "Port already open\n";
    } else {
      SerialPortHw->open(Name, ErrorCode);
      SerialPortHw->set_option(
          boost::asio::serial_port_base::baud_rate(BaudRate));
      SerialPortHw->set_option(boost::asio::serial_port_base::parity(
          boost::asio::serial_port_base::parity::none));
      SerialPortHw->set_option(boost::asio::serial_port_base::flow_control(
          boost::asio::serial_port_base::flow_control::none));
      SerialPortHw->set_option(boost::asio::serial_port_base::stop_bits(
          boost::asio::serial_port_base::stop_bits::one));
    }
  } catch (boost::wrapexcept<boost::system::system_error>& err) {
    std::cout << CONFIG_SERIAL_ERR << std::endl;
  }
}

void SerialPort::Disconnect() {
  SerialPortHw->close();
}

Port& SerialPort::operator<<(Data& data) {
  try {
    SerialPortHw->write_some(
        boost::asio::buffer(data.Content, data.Content.size()));
  } catch (boost::wrapexcept<boost::system::system_error>& err) {
    OnError(__func__, err.what());
    SerialPortHw->close();
    return *this;
  }
  return *this;
}

Port& SerialPort::operator>>(Data& ReceivedData) {
  string CollectedData, ReceivedDataBuffer{" "};

  try {
    for (unsigned char ReadingIteration = 0;
         ReceivedDataBuffer != CONFIG_DELIMTER &&
         ReadingIteration < CONFIG_MAX_DATA_BYTES_REC &&
         SerialPortHw->is_open();
         ReadingIteration++) {
      SerialPortHw->read_some(boost::asio::buffer(ReceivedDataBuffer, 1));
      CollectedData += ReceivedDataBuffer;
    }
  } catch (boost::wrapexcept<boost::system::system_error>& err) {
    OnError(__func__, err.what());
    SerialPortHw->close();
    ReceivedData.Content = "";
    return *this;
  }

  boost::replace_all(CollectedData, CONFIG_DELIMTER, "");

  ReceivedData.Content = CollectedData;

  return *this;
}

SerialPort::operator bool() {
  return SerialPortHw->is_open() ? true : false;
}

void SerialPort::OnError(string Func, string What) {
  ErrorsDetected += Func + " " + What + "\n";
  LOG(ErrorsDetected);
}