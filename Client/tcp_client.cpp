#include "tcp_client.hpp"
#include <cstdlib>
#include <cstring>
#include <boost/asio.hpp>
#include <iostream>

Client::Client(string Port, string iP) : Port(Port), iP(iP)
{
    IOService = unique_ptr<io_service>(new io_service{});
    Resolver = unique_ptr<tcp::resolver>(new tcp::resolver{*IOService});
    Query = unique_ptr<tcp::resolver::query>(new tcp::resolver::query{tcp::v4(), iP, Port});
    Iterator = Resolver->resolve(*Query);
    Socket = unique_ptr<tcp::socket>(new tcp::socket{*IOService});
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
