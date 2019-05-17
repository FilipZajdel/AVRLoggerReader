#ifndef argument_parser
#define argument_parser

#include <boost/program_options.hpp>
#include <string>

namespace boost_arg = boost::program_options;

/** @brief Parser for command line arguments */
class ArgumentParser {
 public:
  /** @brief Constructor
   *
   * @arg argc arguments number
   * @arg argv arguments
   */
  ArgumentParser(int argc, char** argv);
  /** @brief Returns the map of arg : value pairs */
  boost::program_options::variables_map GetVarMap();
  /** @brief Returns description of program usage */
  boost_arg::options_description GetDescription();

 private:
  boost::program_options::variables_map VarMap;
  boost_arg::options_description* description;
  char** argv;
  int argc;
};

#endif /* argument_parser */