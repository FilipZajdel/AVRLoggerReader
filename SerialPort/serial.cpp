#include "serial.hpp"
#include <iostream>
#include <boost/algorithm/string/replace.hpp>
#include <thread>

SerialPort::SerialPort(){
    PortName = "";
    BaudRate = 0;
    ConnectionEstablished = false;;
}

SerialPortSampler::SerialPortSampler(std::string PortName, unsigned int BaudRate){

    SetPortName(PortName);
    SetBaudRate(BaudRate);
    SetConnectionEstablishment(false);

    SerialService = unique_ptr<boost::asio::io_service>{new boost::asio::io_service()};
    SerialPort = unique_ptr<boost::asio::serial_port>{new boost::asio::serial_port(*SerialService)};
}

void SerialPortSampler::Connect(){
    boost::system::error_code ErrorCode;

    try{
        if(SerialPort->is_open()){
            std::cout << "Port already open\n";
        } else {
            SerialPort->open(GetPortName(), ErrorCode);
            SerialPort->set_option(boost::asio::serial_port_base::baud_rate(GetBaudRate()));
            SerialPort->set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
            SerialPort->set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
            SerialPort->set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));

            SetConnectionEstablishment(SerialPort->is_open());
        }
    } catch (boost::wrapexcept<boost::system::system_error> &err){
        std::cout << err.what() << "\t"<< "in: "<<__func__<<std::endl;
    }
}

void SerialPortSampler::Disconnect(){
    SerialPort->close();
}

std::string SerialPortSampler::GetData(std::string Delimiter){

    std::string CollectedData, ReceivedDataBuffer{1, ' '};

    for(unsigned char ReadingIteration = 0; ReceivedDataBuffer != Delimiter && ReadingIteration < MAXIMUM_AMOUNT_OF_DATA_BYTES; ReadingIteration++){
        SerialPort->read_some(boost::asio::buffer(ReceivedDataBuffer, 1));
        CollectedData +=ReceivedDataBuffer;
    }

    boost::replace_all(CollectedData, Delimiter, "\n");

    return CollectedData;
}

void SerialPortSampler::SendData(std::string Data){
    std::string DataToSend = Data;

    for(auto character : DataToSend){
        SerialPort->write_some(boost::asio::buffer(std::string()+character, 1));
        std::this_thread::sleep_for(std::chrono::microseconds(DEF_DELAY_BETWEEN_SENDING));
    }
}

bool SerialPort::CheckConnectionEstablishment(){
    return ConnectionEstablished;
}

bool SerialPortSampler::CheckConnectionEstablishment(){
    SerialPort::SetConnectionEstablishment(SerialPort->is_open());
    return SerialPort::CheckConnectionEstablishment();
}

void SerialPort::SetPortName(std::string PortName){
    this->PortName = PortName;
}
void SerialPort::SetBaudRate(unsigned int BaudRate){
    this->BaudRate = BaudRate;
}
std::string SerialPort::GetPortName(){
    return PortName;
}
unsigned int SerialPort::GetBaudRate(){
    return BaudRate;
}
void SerialPort::SetConnectionEstablishment(bool ConnectionEstablished){
    this->ConnectionEstablished = ConnectionEstablished;
}
