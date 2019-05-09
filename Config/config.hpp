#ifndef config_hpp
#define config_hpp
#include <string>

// General 
// #define LOGS_ON
#ifdef  LOGS_ON 
#define LOG(message)    std::cout<<(message)<<"\n" 
#else   
#define LOG(message)    std::cout<<""
#endif  // LOGS_ON

#define PROGRAM_LOG_ON  true

#if PROGRAM_LOG_ON
#define PROGRAM_LOG(message) std::cout<<"\033[1;37m"<<(message)<<"\n"
#else
#define PROGRAM_LOG(message) std::cout<<""
#endif

// Serial Config
#define CONFIG_DELIMTER "\n"
#define CONFIG_MAX_DATA_BYTES_REC 100
#define CONFIG_SERIAL_ERR  "Serial port error"

// Client Config
#define CONFIG_TCP_PORT   "4430"
#define CONFIG_LOCAL_IP   "127.0.0.1"

// Argument Parser Config
#define CONFIG_ARGUMENTS "help","device","baud","file","port","ip","timestamp","screen_off"
#define CONFIG_ARGUMENTS_NR (8)


enum {CFG_HELP_IDX, CFG_DEVICE_IDX, CFG_BAUD_IDX, CFG_FILE_IDX, CFG_PORT_IDX, CFG_IP_IDX, CFG_TIMESTAMP_IDX,
    CFG_SCREEN_OFF};

#define CONFIG_OPTIONS_DESCRIPTION   "Adjust program with following options"
#define CONFIG_ARGS_OPTIONS ("help,h", "Help")  \
        ("device,d", boost::program_options::value<std::string>(),"Serial port device")  \
        ("baud,b", boost::program_options::value<int>() , "Baudrate")\
        ("file,f", boost::program_options::value<std::string>(),"Save data to csv file") \
        ("port,p", boost::program_options::value<std::string>(),"Send data to this tcp port") \
        ("ip,i", boost::program_options::value<std::string>(),"Send data to this ip")\
        ("timestamp,t", "Attach timestamp to each sample")\
        ("screen_off,o", "Turn off logging through terminal")


// Argument Parser constants
#define MESSAGE_ON_NO_PORT_OR_IP "Ip and/or Port not specified"
#define MESSAGE_ON_NO_DEVICE_OR_BAUD "Device and/or Baudrate not specified"

#endif // config_hpp
