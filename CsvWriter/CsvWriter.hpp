#ifndef csv_writer_hpp
#define csv_writer_hpp

#include <fstream>
#include <string>
#include <vector>

using std::ofstream;
using std::string;
using std::vector;

/** @brief Class for creating csv files and filling it */
class CsvWriter {
 public:
  /** @brief Constructor
   * 
   * @param Filepath path to file that will be created 
   */
  CsvWriter(string Filepath) noexcept;
  /** @brief Writes specified data to file and separates with ";" */
  void Write(vector<string> DataToWrite);
  /** @brief Closes and saves written data to file */
  void Close();

 private:
  string Filepath;
  ofstream FileStream;
};

#endif