#ifndef argument_parser
#define argument_parser
#include <boost/program_options.hpp>
#include <string>

namespace boost_arg = boost::program_options;

class ArgumentParser{
public:
    ArgumentParser(int argc, char **argv);
    boost::program_options::variables_map GetVarMap();
    boost_arg::options_description GetDescription();
private:
    boost::program_options::variables_map VarMap;
    boost_arg::options_description *description;
    char **argv;
    int argc;
};



#endif /* argument_parser */