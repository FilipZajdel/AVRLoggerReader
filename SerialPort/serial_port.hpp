#ifndef serial_port_hpp
#define serial_port_hpp

#include <string>
#include <boost/asio.hpp>
#include <memory>
#include "../Port/port.hpp"

#define DEF_DELAY_BETWEEN_SENDING   2000

using std::unique_ptr;
using std::string;
using boost::asio::io_service;
using boost::asio::serial_port;

class SerialPort : public Port{
public:
    SerialPort(std::string Name, long BaudRate);
    virtual ~SerialPort();
    virtual void Connect();
    virtual void Disconnect();

    virtual operator bool();
    virtual Port &operator<<(Data &);
    virtual Port &operator>>(Data &);

private:
    unique_ptr<io_service> SerialService;
    unique_ptr<serial_port> SerialPortHw;

    string ErrorsDetected;
    const string Name;
    const long BaudRate;

    void OnError(string Where, string What);
};

#endif /* serial_hpp */
