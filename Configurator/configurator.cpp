#include "configurator.hpp"
#include "../Config/config.hpp"

#include <iostream>

string PossibleArguments[CONFIG_ARGUMENTS_NR] = {CONFIG_ARGUMENTS};

ProgramConfig::ProgramConfig(){
    Port = "";
    DeviceName = "";
    Ip = "";
    Filename = "";
    BaudRate = 0;
}

Configurator::Configurator(int argc, char **argv)
{
    argumentParser = new ArgumentParser {argc, argv};
}

ProgramConfig Configurator::GetConfig(){
    try{
        boost::program_options::variables_map VarMap = argumentParser->GetVarMap();

        for(int ArgCtr = 0; ArgCtr < CONFIG_ARGUMENTS_NR; ArgCtr++){

            string Argument = PossibleArguments[ArgCtr];

            if(VarMap.count(Argument)){
                switch(ArgCtr){
                    case CFG_HELP_IDX:
                        Config.ChosenFeatures.push_back(ProgramConfig::SHOW_HELP);
                        LOG("help option");
                        break;
                    case CFG_DEVICE_IDX:
                        Config.DeviceName = VarMap[Argument].as<string>();
                        LOG("device option");
                        break;
                    case CFG_FILE_IDX:
                        Config.ChosenFeatures.push_back(ProgramConfig::FILE_LOG);
                        Config.Filename = VarMap[Argument].as<string>();
                        LOG("file option");
                        break;
                    case CFG_IP_IDX:
                        Config.ChosenFeatures.push_back(ProgramConfig::NETWORK_LOG);
                        Config.Ip = VarMap[Argument].as<string>();
                        LOG("ip option");
                        break;
                    case CFG_PORT_IDX:
                        Config.ChosenFeatures.push_back(ProgramConfig::NETWORK_LOG);
                        Config.Port = VarMap[Argument].as<string>();
                        LOG("port option");
                        break;
                    case CFG_TIMESTAMP_IDX:
                        Config.ChosenFeatures.push_back(ProgramConfig::SHOW_TIMESTAMP);
                        LOG("timestamp option");
                        break;
                    case CFG_BAUD_IDX:
                        Config.BaudRate = VarMap[Argument].as<int>();
                        LOG("baud option");
                        break;
                    case CFG_SCREEN_OFF:
                        Config.ChosenFeatures.push_back(ProgramConfig::SCREEN_OFF);
                        LOG("screen off option");
                        break;
                }
            }
        }

        if(!CheckNetworkParams()){
            PROGRAM_LOG(MESSAGE_ON_NO_PORT_OR_IP);
            throw ConfigurationException{MESSAGE_ON_NO_PORT_OR_IP};
        }

        if(!CheckDeviceAndBaud()){
            PROGRAM_LOG(MESSAGE_ON_NO_DEVICE_OR_BAUD);
            throw ConfigurationException{MESSAGE_ON_NO_DEVICE_OR_BAUD};
        }

    } catch(ConfigurationException &exc) {
        throw exc;
    }
    catch( ... ){
        throw ConfigurationException{};
    }
    return Config;
}

bool Configurator::CheckNetworkParams(){

    if(Config.Ip != "" && Config.Port == ""
    || Config.Ip == "" && Config.Port != ""){
        for(int feature_ctr = 0; feature_ctr < Config.ChosenFeatures.size(); feature_ctr++){
            if(Config.ChosenFeatures[feature_ctr] == ProgramConfig::NETWORK_LOG){
                Config.ChosenFeatures.erase(Config.ChosenFeatures.begin() + feature_ctr);
                LOG("erasing ip or port\n");
                return false;
            }
        }
    }
    return true;
}

bool Configurator::CheckDeviceAndBaud(){

    boost::program_options::variables_map VarMap = argumentParser->GetVarMap();
    string DeviceStr = PossibleArguments[CFG_DEVICE_IDX];
    string BaudStr = PossibleArguments[CFG_BAUD_IDX];

    if(VarMap.count(BaudStr) && VarMap.count(DeviceStr)){
        return true;
    } else {
        return false;
    }
}

void Configurator::ShowDescription(){
    PROGRAM_LOG(argumentParser->GetDescription());
}

