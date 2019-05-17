# Relog

[About](#about)

[Documentation](https://filipzajdel.github.io/Relog)

[Requirements](#requirements)

[Building project](#building-the-project-on-linux)

[Usage](#usage)

[Serial port](#serial-port)

[Output format](#output-format-of-data)

## About
Program for reading logs from microcontroller. It has capabilities to send it to TCP Server and save in file.
Required options can be chosen using command line arguments.

## Requirements
1. g++ (>=c++17)
2. cmake 
3. Boost 1.69.0 

## Building the project on Linux
In order to build project:
```
git clone https://github.com/FilipZajdel/AVRLoggerReader
cd AVRLoggerReader
mkdir build
cd build
cmake ..
make -j8	
```

If no errors occured during build, project is accessible in build directory as relog.

## Usage
If project is built it can be accessed in build as LogReader. It can be started by invoking it ./LogReader with following arguments:

* [-d] **_required_** name of serial port  
* [-b] **_required_** baudrate
* [-f] **_optional_** filename  write logs to file
* [-ip] **_optional_** ip of server sends data to server (**required** if --port used)
* [-p] **_optional_** port (**required** if -ip used) 
* [-t] **_optional_** attach timestamp

## Serial port

Currently only one parameter of serial port connection can be chosen: baud rate. The rest of parameters are by default set as follows:
* number of data bits - 8
* no parity bit
* stop bits - 1
* no control signals

## Output format of data

1. Logs to the screen:


*In case of using timestamp option, timestamp is formatted as YYYY-MM-DD HH:MM:SS*

*if [-t] used:*

[timestamp] received data

*otherwise:*

received data


2. Logs to the csv file

*In case of logging to csv file, epoch timestamp is used*

*if [-t] used:*

timestamp; data

*otherwise:*

data

3. Logs sent via network

*Timestamp is formatted as YYYY-MM-DD HH:MM:SS*

[timestamp] received data
