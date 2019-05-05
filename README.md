# Serial Logger Reader

Program for reading logs from microcontroller. It have capabilities to send it to TCP Server and save in file.
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

If no errors occured during build, project is accessible in build directory as LogReader.

## Usage
If project is built it can be accessed in build as LogReader. It can be started by invoking it ./LogReader with following arguments:

* [-d] name of serial port  *_required_*
* [-b] baudrate *_required_*
* [-f] filename *_optional_*  write logs to file
* [-ip] ip of server *_optional_* sends data to server 
* [-p] port *_optional_* (required if -ip used) 
* [-t] *_optional_* attach timestamp

## Output format of data

#### 1. Logs on the screen:

*if [-t] used:*

[timestamp] received data

*otherwise:*

received data

#### 2. Logs in file (csv)

*if [-t] used:*

timestamp; data

*otherwise:*

data

#### 3. Logs sent via network

tbd
