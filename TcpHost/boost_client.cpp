#include "boost_client.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <iostream>

LocalHost::LocalHost(std::string Port){

    std::string LocalIp = LOCAL_HOST_IP, LocalPort = DEFAULT_PORT;
    IOService = new boost::asio::io_service();
    Resolver = new boost::asio::ip::tcp::resolver(*IOService);
    Query = new boost::asio::ip::tcp::resolver::query(boost::asio::ip::tcp::v4(), LocalIp, LocalPort);
    Iterator = Resolver->resolve(*Query);
    Socket = new boost::asio::ip::tcp::socket(*IOService);
    Port = Port;
    ConnectionEstablished = false;
}

bool LocalHost::EstablishConnection(){
    boost::system::error_code ErrorCode;
    boost::asio::connect(*Socket, Iterator, ErrorCode);

    if(ErrorCode){
        std::cout << ErrorCode << std::endl;
        ConnectionEstablished = false;
        std::cout << "Connection Establishment failed\n";
    } else {
        std::cout << ErrorCode << std::endl;
        ConnectionEstablished = true;
        std::cout << "Connection Established\n";
    }

    return ConnectionEstablished;
}

void LocalHost::SendData(std::string Data){
    boost::asio::write(*Socket, boost::asio::buffer(Data, Data.length()));
}

bool LocalHost::IsConnectionEstablished(){
    return ConnectionEstablished;
}