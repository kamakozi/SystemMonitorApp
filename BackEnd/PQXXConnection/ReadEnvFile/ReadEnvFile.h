//
// Created by ziga zoric on 01.06.25.
//

#ifndef READENVFILE_H
#define READENVFILE_H
#include <sstream>
#include <unordered_map>
#include <spdlog/sinks/basic_file_sink.h>
#include <fstream>

class ReadEnvFile {
public:
    std::unordered_map<std::string,std::string>readEnvFile() {
        std::unordered_map<std::string,std::string> envMap;
        std::ifstream readFile("/Users/zigazoric/Desktop/cpp/SystemMonitorApp/database.env");


        if (!readFile) {
            std::cerr << "Unable to read env file" << std::endl;
            return envMap;
        }

        std::string line;
        while (getline(readFile,line)) {
            size_t pos = line.find("=");
            if (pos != std::string::npos) {
                std::string key = line.substr(0,pos);
                std::string value = line.substr(pos+1);
                envMap[key] = value;
            }
        }
        return envMap;
    }
};



#endif //READENVFILE_H
