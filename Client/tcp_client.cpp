#include "tcp_client.hpp"

#include <boost/asio.hpp>

#include <cstdlib>
#include <cstring>
#include <iostream>

Client::Client(string Port, string iP) : Port(Port), iP(iP) {
  IOService = unique_ptr<io_service>(new io_service{});
  Resolver = unique_ptr<tcp::resolver>(new tcp::resolver{*IOService});
  Query = unique_ptr<tcp::resolver::query>(
      new tcp::resolver::query{tcp::v4(), iP, Port});
  Iterator = Resolver->resolve(*Query);
  Socket = unique_ptr<tcp::socket>(new tcp::socket{*IOService});
}

bool Client::EstablishConnection() {
  try {
    boost::system::error_code ErrorCode{};
    boost::asio::connect(*Socket, Iterator, ErrorCode);
    ConnectionAlive = true;
  } catch (boost::wrapexcept<boost::system::system_error>& exception) {
    ConnectionAlive = false;

    return ConnectionAlive;
  }

  return ConnectionAlive;
}

void Client::SendData(std::string Data) {
  try {
    Socket->send(boost::asio::buffer(Data, Data.length()));

    ConnectionAlive = true;
  } catch (boost::wrapexcept<boost::system::system_error>& exception) {
    CloseConnection();
  }
}

bool Client::IsConnectionEstablished() {
  return ConnectionAlive;
}

Client::~Client() {
  CloseConnection();
}

void Client::CloseConnection() {
  try {
    if (Socket->is_open()) {
      Socket->shutdown(tcp::socket::shutdown_send);
      Socket->close();
    }
    ConnectionAlive = false;
  } catch (boost::wrapexcept<boost::system::system_error>& exception) {
    ConnectionAlive = false;
  }
}