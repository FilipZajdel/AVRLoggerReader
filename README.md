AVRLoggerReader

Program using Boost for interfacing mcu with PC and send data by TCP/IP.

In order to build project, gnu g++, cmake and Boost are required.

To build project simply:
1. clone this repo
2. cd AVRLoggerReader
3. mkdir build
4. cd build
5. cmake ..
6. make -j4	(4 is an example, of course it's not specified how many threads must be used)

If no error occured during build, project is accessible in build directory.
It can be started by ./SerialHost .
