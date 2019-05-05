#ifndef tests_hpp
#define tests_hpp

#include <iostream>
#include <iomanip>

#define TEST_OK std::cout<<"\033[1;34m"<<std::left<<std::setw(40) << __func__ << " \033[1;32m PASSED\n"
#define TEST_FAIL std::cout<<"\033[1;34m"<<std::left<<std::setw(40) << __func__ << " \033[1;31m FAILED\n"
#define TEST_EXC std::cout<<"\033[1;34m"<<std::left<<std::setw(40) << __func__ << " \033[1;31m FAILED + EXCEPT\n"
#define PRINT_HEADER std::cout<<"\033[1;37m>>>>>>> " << __func__ << " <<<<<<<\n"
#define TEST_IF(condition)   if(condition){TEST_OK;}else{TEST_FAIL;}

#endif