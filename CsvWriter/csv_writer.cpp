#include "csv_writer.hpp"
#include <cstdint>

CsvWriter::CsvWriter(string Filepath) noexcept
    : Filepath(Filepath), FileStream(ofstream{Filepath}) {}

void CsvWriter::Write(vector<string> DataToWrite) {
  string Row{};

  for (uint8_t ColumnCtr = 0; ColumnCtr < DataToWrite.size(); ColumnCtr++) {
    Row += DataToWrite[ColumnCtr] +
           ((ColumnCtr == DataToWrite.size() - 1) ? "" : ";");
  }

  FileStream << Row;
}

void CsvWriter::Close() {
  FileStream.close();
}