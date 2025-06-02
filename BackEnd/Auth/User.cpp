//
// Created by ziga zoric on 03.06.25.
//

#include "User.h"

User::User(std::string name, std::string password,std::string email):name(std::move(name)), password(std::move(password)),email(std::move(email)){
}

std::string User::getName() const {
    return name;
}

std::string User::getPassword() const {
    return password;
}
std::string User::getEmail() const {
    return email;
}


