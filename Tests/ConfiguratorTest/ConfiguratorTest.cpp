#include <configurator.hpp>
#include <exception>
#include "../tests.hpp"

void ProgramConfigWithNoParamsSpecified()
{
    try
    {
        char *argv[1];
        int argc = 1;
        Configurator configurator(argc, argv);
        ProgramConfig config = configurator.GetConfig();

        TEST_FAIL;
    }
    catch (...)
    {
        TEST_OK;
    }
}

void ArgumentsSpecifiedForVector()
{
    try
    {
        char *argv[6] = {(char *)"program_name",(char*)"-d",(char*) "mock", (char*)"-b",(char*) "6500", (char *)"-t"};
        int argc = 6;

        Configurator configurator(argc, argv);
        ProgramConfig config = configurator.GetConfig();

        if (config.ChosenFeatures.size() == 1)
        {
            TEST_OK;
        }
        else
        {
            TEST_FAIL;
        }
    }
    catch (...)
    {
        TEST_EXC;
    }
}

void BaudRateSpecified()
{
    try
    {
        char *argv[5] = {(char *)"program_name",(char*)"-d",(char*)"mock", (char *)"-b",(char*)"9600"};
        int argc = 5;

        Configurator configurator(argc, argv);
        ProgramConfig config = configurator.GetConfig();

        if (config.BaudRate == 9600)
        {
            TEST_OK;
        }
        else
        {
            TEST_FAIL;
        }
    }
    catch (...)
    {
        TEST_EXC;
    }
}

void BaudRateWithNoValue()
{
    try
    {
        char *argv[5] = {(char *)"program_name", (char*)"-d",(char*) "mock", (char *)"-b"};
        int argc = 5;

        Configurator configurator(argc, argv);
        ProgramConfig config = configurator.GetConfig();
    }
    catch (ConfigurationException &exc)
    {
        TEST_OK;
        return;
    }
}

void TimestampPicked()
{
    try
    {
        char *argv[6] = {(char *)"program_name",(char*)"-d",(char*)"mock", (char *)"-b",(char*)"6500", (char *)"-t"};
        int argc = 6;

        Configurator configurator(argc, argv);
        ProgramConfig config = configurator.GetConfig();

        if (config.ChosenFeatures[0] == ProgramConfig::SHOW_TIMESTAMP)
        {
            TEST_OK;
        }
        else
        {
            TEST_FAIL;
        }
    }
    catch (...)
    {
        TEST_EXC;
    }
}

void IpWithNoPort(){
    try
    {
        char *argv[7] = {(char *)"program_name",(char*)"-d",(char*)"mock", (char *)"-b",(char*)"6500", (char *)"-i", (char*)"127"};
        int argc = 7;

        Configurator configurator(argc, argv);
        ProgramConfig config = configurator.GetConfig();

        if( config.ChosenFeatures.end() == std::find(config.ChosenFeatures.begin(), config.ChosenFeatures.end(), ProgramConfig::NETWORK_LOG) ){
            TEST_OK;
        } else {
            TEST_FAIL;
        }
    }
    catch (...)
    {
        TEST_OK;
        return;
    }
}

void PortWithNoIp(){
    try
    {
        char *argv[3] = {(char *)"program_name", (char *)"-p", (char*)"127"};
        int argc = 3;

        Configurator configurator(argc, argv);
        ProgramConfig config = configurator.GetConfig();

        if( config.ChosenFeatures.end() == std::find(config.ChosenFeatures.begin(), config.ChosenFeatures.end(), ProgramConfig::NETWORK_LOG) ){
            TEST_OK;
        } else {
            TEST_FAIL;
        }
    }
    catch (...)
    {
        TEST_OK;
        return;
    }
}

void ThrowConfigurationExcept(){
    try
    {
        char *argv[3] = {(char *)"program_name", (char *)"-p", (char*)"127"};
        int argc = 3;

        Configurator configurator(argc, argv);
        ProgramConfig config = configurator.GetConfig();

        // Getting here means fault
        TEST_FAIL;
    }
    catch (ConfigurationException &exc)
    {
        TEST_OK;
        return;
    }
}

void ConfiguratorTest()
{
    PRINT_HEADER;
    ProgramConfigWithNoParamsSpecified();
    ArgumentsSpecifiedForVector();
    BaudRateSpecified();
    TimestampPicked();
    BaudRateWithNoValue();
    IpWithNoPort();
    PortWithNoIp();
    ThrowConfigurationExcept();
}
