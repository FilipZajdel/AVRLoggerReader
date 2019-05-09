#include "CsvWriterTest.hpp"

#include "../../CsvWriter/csv_writer.hpp"
#include "../tests.hpp"

#include <string>
#include <fstream>
#include <vector>

#include <boost/algorithm/string.hpp>

using std::string;
using std::string_view;
using std::ifstream;
using std::vector;

void TestOfCreatingBlankFile(){

    string Filepath = "relog_test_file.csv";
    string DataToWrite= "";
    CsvWriter csvWriter{""};

    csvWriter.Write(vector<string>{DataToWrite});
    csvWriter.Close();

    ifstream FileStream{Filepath};
    string ReadData;
    FileStream >> ReadData;

    TEST_IF(ReadData == DataToWrite);
}

void TestOfWritingCsvData(){

    vector<string> DataToWrite {"this", "is", "csv", "writer", "test" };
    string Filepath{"relog_test_file.csv"};

    CsvWriter csvWriter{Filepath};
    csvWriter.Write(DataToWrite);
    csvWriter.Close();

    ifstream FileStream{Filepath};
    string ReadData;
    vector <string> ReadDataVect;

    FileStream >> ReadData;
    FileStream.close();

    boost::split(ReadDataVect, ReadData, boost::is_any_of(";"));

    TEST_IF(ReadDataVect == DataToWrite);
}

void CsvWriterTest(){

    PRINT_HEADER;
    TestOfCreatingBlankFile();
    TestOfWritingCsvData();
}