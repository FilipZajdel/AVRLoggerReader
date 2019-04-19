#include "tcp_client.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <iostream>

Client::Client(std::string Port)
{
    std::string iP = LOCAL_HOST_IP, port = DEFAULT_PORT;
    IOService = unique_ptr<boost::asio::io_service>(new  boost::asio::io_service{});
    Resolver = unique_ptr<boost::asio::ip::tcp::resolver>(new boost::asio::ip::tcp::resolver{*IOService});
    Query = unique_ptr<boost::asio::ip::tcp::resolver::query>(new boost::asio::ip::tcp::resolver::query{boost::asio::ip::tcp::v4(), iP, port});
    Iterator = Resolver->resolve(*Query);
    Socket = unique_ptr<boost::asio::ip::tcp::socket>(new boost::asio::ip::tcp::socket{*IOService});
    Port = Port;
    ConnectionEstablished = false;
}

bool Client::EstablishConnection()
{
    try {
        boost::system::error_code ErrorCode{};
        boost::asio::connect(*Socket, Iterator, ErrorCode);
    }
    catch (boost::wrapexcept<boost::system::system_error> &err){
        std::cout << err.what() << std::endl;
        ConnectionEstablished = false;
        return ConnectionEstablished;
    }

    ConnectionEstablished = true;
    return ConnectionEstablished;
}

void Client::SendData(std::string Data)
{
    boost::asio::write(*Socket, boost::asio::buffer(Data, Data.length()));
}

bool Client::IsConnectionEstablished()
{
    return ConnectionEstablished;
}