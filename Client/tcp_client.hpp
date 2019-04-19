#ifndef tcp_client_hpp
#define tcp_client_hpp

#include <boost/asio.hpp>
#include <string>
#include <memory>
#include "../Config/config.hpp"

#define DEFAULT_PORT    "4430"
#define LOCAL_HOST_IP   "127.0.0.1"


using std::unique_ptr;

class Client{
public:
    Client(std::string Port = CONFIG_TCP_PORT);
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