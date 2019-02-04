#ifndef boost_host
#define boost_host

#include <boost/asio.hpp>
#include <string>

#define DEFAULT_PORT    "3500"
#define LOCAL_HOST_IP   "127.0.0.1"

class LocalHost{
public:
    LocalHost(std::string Port = DEFAULT_PORT);
    virtual ~LocalHost(){};
    virtual bool EstablishConnection();
    virtual void SendData(std::string Data);
    virtual bool IsConnectionEstablished();
private:
    std::string Port;
    bool ConnectionEstablished;
    boost::asio::io_service *IOService;
    boost::asio::ip::tcp::resolver *Resolver;
    boost::asio::ip::tcp::resolver::query *Query;
    boost::asio::ip::tcp::resolver::iterator Iterator;
    boost::asio::ip::tcp::socket *Socket;

};


#endif