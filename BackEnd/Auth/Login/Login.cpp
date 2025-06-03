//
// Created by ziga zoric on 03.06.25.
//

#include "Login.h"
#include "../../PQXXConnection/PQXXSingleton/PQXXSingletonConnection.h"


#include <qstring.h>
#include <pqxx/pqxx>
#include <optional>
#include <iostream>

#include "../Register/BCrypt.hpp"


std::optional<User> Login::login(QString username,QString password) {
    try{

    pqxx::connection& conn = PQXXSingletonConnection::getInstance();

    pqxx::work xtn(conn);


    std::string userName = username.toStdString();
    std::string pass = password.toStdString();

    std::string Query = "SELECT username,password,email FROM users WHERE username=" + xtn.quote(userName);

        pqxx::result r = xtn.exec(Query);
        if (r.empty()) {
            return std::nullopt;
        }
        std::string hashedPasswortFromDb = r[0]["password"].c_str();
        if (!BCrypt::validatePassword(pass,hashedPasswortFromDb)) {
            return std::nullopt;
        }

        std::string email = r[0]["email"].c_str();
        return User(userName,pass,email);
    }catch (std::exception& e) {
        std::cerr << "Unable to login user problems with connection or database" << std::endl;
    }

}
