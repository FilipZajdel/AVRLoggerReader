#ifndef csv_writer_hpp
#define csv_writer_hpp

#include <string>
#include <fstream>
#include <vector>


using std::string;
using std::ofstream;
using std::vector;


class CsvWriter{
public:
    CsvWriter(string Filepath) noexcept;
    void Write(vector <string> DataToWrite);
    void Close();
private:
    string Filepath;
    ofstream FileStream;
};

#endif