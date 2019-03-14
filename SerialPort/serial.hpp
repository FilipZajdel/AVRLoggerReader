#ifndef serial_hpp
#define serial_hpp

#include <string>
#include <boost/asio.hpp>

#define MAXIMUM_AMOUNT_OF_DATA_BYTES 100
#define DEF_DELAY_BETWEEN_SENDING   2000


class SerialPort{
    std::string PortName;
    unsigned int BaudRate;
    bool ConnectionEstablished;

public:
    SerialPort();
    virtual ~SerialPort(){};
    virtual void Connect()=0;
    virtual void Disconnect()=0;
    virtual void SendData(std::string)=0;
    virtual std::string GetData(std::string Delimiter)=0;

    virtual bool CheckConnectionEstablishment();
    virtual void SetPortName(std::string PortName);
    virtual void SetBaudRate(unsigned int BaudRate);
    virtual std::string GetPortName();
    virtual unsigned int GetBaudRate();
protected:
    virtual void SetConnectionEstablishment(bool ConnEstablish);
};

class SerialPortSampler : public SerialPort{
private:
    boost::asio::io_service *SerialService;
    boost::asio::serial_port *SerialPort;

public:

    SerialPortSampler(std::string PortName, unsigned int BaudRate);
    virtual ~SerialPortSampler(){};
    virtual void Connect();
    virtual void Disconnect();
    virtual std::string GetData(std::string Delimiter);
    virtual void SendData(std::string);
    virtual bool CheckConnectionEstablishment();
};
#endif /* serial_hpp */