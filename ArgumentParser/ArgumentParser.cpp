#include "ArgumentParser.hpp"
#include "../Config/Config.hpp"

#include <boost/program_options.hpp>

#include <iostream>
#include <string>

ArgumentParser::ArgumentParser(int argc, char** argv) {
  this->description =
      new boost_arg::options_description{CONFIG_OPTIONS_DESCRIPTION};
  this->argc = argc;
  this->argv = argv;

  this->description->add_options() CONFIG_ARGS_OPTIONS;
}

boost_arg::variables_map ArgumentParser::GetVarMap() {
  boost_arg::store(boost_arg::parse_command_line(argc, argv, *description),
                   VarMap);
  boost_arg::notify(VarMap);

  return VarMap;
}

boost_arg::options_description ArgumentParser::GetDescription() {
  return *description;
}