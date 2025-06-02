//
// Created by ziga zoric on 03.06.25.
//

#ifndef USER_H
#define USER_H
#include <iostream>


class User {
protected:
    std::string name;
    std::string password;
    std::string email;

public:
    User( std::string name, std::string password,std::string email);
    [[nodiscard]] std::string getName()const;
    [[nodiscard]] std::string getPassword()const;
    [[nodiscard]] std::string getEmail()const;
};



#endif //USER_H
