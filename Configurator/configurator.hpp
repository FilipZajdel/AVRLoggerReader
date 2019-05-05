#ifndef configurator_hpp
#define configurator_hpp

#include "../ArgumentParser/argument_parser.hpp"

#include <vector>
#include <array>
#include <string>
#include <exception>

using std::vector;
using std::string;
using std::array;

struct ProgramConfig{

  ProgramConfig();

  enum Features
  {
    SCREEN_LOG, 
    FILE_LOG,
    NETWORK_LOG,
    ENABLE_TRANSMITTING,
    SHOW_HELP,
    SHOW_TIMESTAMP,
    SCREEN_OFF
  };

  string Port;
  string Ip;
  string DeviceName;
  string Filename;
  int BaudRate;
  vector<enum Features> ChosenFeatures;
};

class ConfigurationException : public std::exception
{
public:
  ConfigurationException(const char* what="ConfigurationException") : exc_info(what){};
  virtual const char* what() const throw(){
    return exc_info;
  }
private:
  const char* exc_info;
};

/** @brief Obtains program mode by given arguments */
class Configurator
{
  public:
    Configurator(int argc, char **argv);
    /** @brief Gives config evaluated by argc and argv.
     *  
     *  Throws ConfigurationException in case of bad arguments specified.
     */
    ProgramConfig GetConfig();
    void ShowDescription();

  private:
    ArgumentParser *argumentParser;
    ProgramConfig Config;
    /** @brief Checks against lack of either Port or Ip if the second exists
     * 
     * @return true if arguments provided properly, false otherwise
     */
    bool CheckNetworkParams();
    /** @brief Checks against lack of Device and Baudrate
     * 
     * @return true if arguments provided properly, false otherwise
     */
    bool CheckDeviceAndBaud();
};

#endif