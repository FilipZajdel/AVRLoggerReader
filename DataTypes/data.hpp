#ifndef data_hpp
#define data_hpp

#include <string>

using std::string;

typedef struct Data {
  Data(string Content) : Content(Content){};
  Data() {}
  string Content;
} Data;

#endif