#ifndef boost_host
#define boost_host

#include <boost/asio.hpp>
#include <string>
#include <memory>

#define DEFAULT_PORT    "3500"
#define LOCAL_HOST_IP   "127.0.0.1"


using std::unique_ptr;

class Client{
public:
    Client(std::string Port = DEFAULT_PORT);
    Client(const Client&)=delete;
    virtual ~Client(){};
    virtual bool EstablishConnection();
    virtual void SendData(std::string Data);
    virtual bool IsConnectionEstablished();
private:
    std::string Port;
    bool ConnectionEstablished;
    
    unique_ptr<boost::asio::io_service> IOService;
    unique_ptr<boost::asio::ip::tcp::resolver> Resolver;
    unique_ptr<boost::asio::ip::tcp::resolver::query> Query;
    unique_ptr<boost::asio::ip::tcp::socket> Socket;

    boost::asio::ip::tcp::resolver::iterator Iterator;
};


#endif