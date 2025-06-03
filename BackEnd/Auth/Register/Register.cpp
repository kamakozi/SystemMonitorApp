//
// Created by ziga zoric on 03.06.25.
//

#include "Register.h"
#include "../User.h"
#include <memory>
#include "BCrypt.hpp"
#include "../../PQXXConnection/PQXXSingleton/PQXXSingletonConnection.h"
#include <pqxx/pqxx>
#include <iostream>




bool Register::registerUser(QString username,QString password, QString email) {


    std::string usern = username.toStdString();
    std::string pass= password.toStdString();
    std::string userEmail = email.toStdString();

    std::unique_ptr<User> user = std::make_unique<User>(usern,pass,userEmail);

    std::string hashedPassword = BCrypt::generateHash(pass);

    try{
    pqxx::connection& conn = PQXXSingletonConnection::getInstance();

    pqxx::work nxt(conn);
    std::string Query = "INSERT INTO users (username,password,user_role,email) VALUES (" +
        nxt.quote(usern) + " , " +
        nxt.quote(hashedPassword) + " , " +
        nxt.quote("2") + " , " +
        nxt.quote(userEmail) + ");";

        nxt.exec(Query);
        nxt.commit();

    std::cout << "User successfully created!" << std::endl;
    }catch (std::exception& e) {
        std::cerr << "Unable to insert new user into the database!" << std::endl;
    }

    return true;

}

