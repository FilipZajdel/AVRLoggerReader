## AVRLoggerReader

Program for interfacing mcu with PC and send data over TCP/IP.

# Requirements
In order to build project, gnu g++, cmake and Boost 1.69.0 are required.

# Build
To build project:
```
git clone https://github.com/FilipZajdel/AVRLoggerReader
cd AVRLoggerReader
mkdir build
cd build
cmake ..
make -j8	
```

If no error occured during build, project is accessible in build directory as SerialHost.
It can be started by ./SerialHost .
