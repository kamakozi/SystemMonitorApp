//
// Created by ziga zoric on 01.06.25.
//

#ifndef PQXXSINGELTONCONNECTION_H
#define PQXXSINGELTONCONNECTION_H
#include <pqxx/pqxx>
#include "../ReadEnvFile/ReadEnvFile.h"
#include <iostream>
#include <memory>


class PQXXSingletonConnection {
public:
    static pqxx::connection &getInstance() {
        static std::unique_ptr<pqxx::connection> conn;

        if (!conn) {
            ReadEnvFile ref;
            auto env = ref.readEnvFile();
            if (env.count("DB_NAME")==0 ||
                env.count("DB_USER")== 0 ||
                env.count("DB_PASSWORD")==0 ||
                env.count("DB_PORT") == 0 ||
                env.count("DB_HOST") == 0
                ) {
                throw std::runtime_error("Some of the databases values are missing in Singelton");
                }

            std::string connStr = "dbname=" + env["DB_NAME"] +
                                  " user=" + env["DB_USER"] +
                                  " password="+ env["DB_PASSWORD"] +
                                  " host=" + env["DB_HOST"] +
                                   " port=" + env["DB_PORT"];

            try{
                conn = std::make_unique<pqxx::connection>(connStr);
                std::cout << "Connect to the database!" << std::endl;
            }catch (std::exception& e) {
                std::cerr << "Unable to connect to database || PQXXSingletonConn" << std::endl;
                throw;
            }
        }
        return *conn;
    }

};



#endif //PQXXSINGELTONCONNECTION_H
