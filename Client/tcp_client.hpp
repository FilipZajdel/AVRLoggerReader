#ifndef tcp_client_hpp
#define tcp_client_hpp

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include "../Config/config.hpp"

using boost::asio::io_service;
using boost::asio::ip::tcp;
using std::string;
using std::unique_ptr;

class Client {
 public:
  /** @brief Constructor. Creates socket
   * @param Port Port required for communication
   * @param iP ip of server to connect to
   */
  Client(string Port, string iP);
  Client(const Client&) = delete;
  virtual ~Client();
  /** @brief Connects to given iP on given Port */
  virtual bool EstablishConnection();
  /** @brief Closes the connection */
  virtual void CloseConnection();
  /** @brief Sends data to given iP on given Port */
  virtual void SendData(string Data);
  /** @brief Checks whether connection has been established */
  virtual bool IsConnectionEstablished();

 private:
  string Port;
  string iP;
  bool ConnectionAlive;

  unique_ptr<io_service> IOService;
  unique_ptr<tcp::resolver> Resolver;
  unique_ptr<tcp::resolver::query> Query;
  unique_ptr<tcp::socket> Socket;
  tcp::resolver::iterator Iterator;
};

#endif