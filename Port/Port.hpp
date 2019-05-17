#ifndef port_hpp
#define port_hpp

#include "../DataTypes/Data.hpp"

#include <iostream>

/** @brief Interface for Port */
class Port {
 public:
  Port(){};
  virtual ~Port(){};
  virtual void Connect() = 0;
  virtual void Disconnect() = 0;

  virtual operator bool() = 0;
  virtual Port& operator<<(Data&) = 0;
  virtual Port& operator>>(Data&) = 0;
};

#endif