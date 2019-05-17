#ifndef data_hpp
#define data_hpp

#include <string>

using std::string;

/** @brief Base class for data */
typedef struct Data {
  /** @brief Constructor
   * @param Content Data to save 
   */
  Data(string Content) : Content(Content){};
  Data() {}
  string Content;
} Data;

#endif