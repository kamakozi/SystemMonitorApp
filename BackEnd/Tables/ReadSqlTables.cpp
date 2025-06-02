

#include "ReadSqlTables.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "../PQXXConnection/PQXXSingleton/PQXXSingletonConnection.h"
#include <pqxx/pqxx>

void ReadSqlTables::readSqlFile() {
    try {
        pqxx::connection& conn = PQXXSingletonConnection::getInstance();

        std::ifstream readFile("/Users/zigazoric/Desktop/cpp/SystemMonitorApp/BackEnd/Tables/Tables.SQL");
        if (!readFile) {
            std::cerr << " Unable to open Tables.SQL file.\n";
            return;
        }

        std::cout << " Table.sql opened!\n";

        std::vector<std::string> statements;
        std::string line;
        while (std::getline(readFile, line, ';')) {
            std::string statement = line + ";";
            if (statement.find_first_not_of(" \t\n\r") != std::string::npos) {
                statements.push_back(statement);
            }
        }

        pqxx::work txn(conn);

        for (const auto& stmt : statements) {
            try {
                txn.exec(stmt);
            } catch (const std::exception& e) {
                std::cerr << "⚠ SQL Error:\n" << stmt << "\nReason: " << e.what() << "\n";
            }
        }

        txn.commit();
        std::cout << " Tables created/loaded successfully.\n";

    } catch (const std::exception& e) {
        std::cerr << " Exception in ReadSqlTables::readSqlFile(): " << e.what() << "\n";
    }
}