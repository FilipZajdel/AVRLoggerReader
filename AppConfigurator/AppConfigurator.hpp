#ifndef configurator_hpp
#define configurator_hpp

#include "../ArgumentParser/ArgumentParser.hpp"

#include <array>
#include <exception>
#include <string>
#include <vector>

using std::array;
using std::string;
using std::vector;


/** @brief Holds program configuration */
struct ProgramConfig {
  ProgramConfig();

  enum Features {
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

class ConfigurationException : public std::exception {
 public:
  ConfigurationException(const char* what = "ConfigurationException")
      : exc_info(what){};

  virtual const char* what() const throw() { return exc_info; }

 private:
  const char* exc_info;
};

/** @brief Investigates program mode by given arguments */
class AppConfigurator {
 public:
  AppConfigurator(int argc, char** argv);
  /** @brief Gives config evaluated by argc and argv.
   *
   *  Throws ConfigurationException in case of bad arguments specified.
   */
  ProgramConfig GetConfig();
  void ShowDescription();

 private:
  ArgumentParser* argumentParser;
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

  void RemoveDuplicates();
};

#endif