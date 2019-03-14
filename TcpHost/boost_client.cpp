#include "boost_client.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <iostream>

LocalHost::LocalHost(std::string Port)
{

    std::string LocalIp = LOCAL_HOST_IP, LocalPort = DEFAULT_PORT;
    IOService = new boost::asio::io_service();
    Resolver = new boost::asio::ip::tcp::resolver(*IOService);
    Query = new boost::asio::ip::tcp::resolver::query(boost::asio::ip::tcp::v4(), LocalIp, LocalPort);
    Iterator = Resolver->resolve(*Query);
    Socket = new boost::asio::ip::tcp::socket(*IOService);
    Port = Port;
    ConnectionEstablished = false;
}

bool LocalHost::EstablishConnection()
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

void LocalHost::SendData(std::string Data)
{
    boost::asio::write(*Socket, boost::asio::buffer(Data, Data.length()));
}

bool LocalHost::IsConnectionEstablished()
{
    return ConnectionEstablished;
}