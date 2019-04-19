#ifndef config_hpp
#define config_hpp

// #define LOGS_ON
#define CONFIG_DELIMTER "\n"
#define CONFIG_MAX_DATA_BYTES_REC 100
#define CONFIG_SERIAL_ERR  "Serial port error"

#ifdef  LOGS_ON 
#define LOG(message)    std::cout<<(message) 
#else   
#define LOG(message)    std::cout<<""
#endif  // LOGS_ON

#define CONFIG_TCP_PORT    "4430"

#endif // config_hpp