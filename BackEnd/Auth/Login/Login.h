//
// Created by ziga zoric on 03.06.25.
//

#ifndef LOGIN_H
#define LOGIN_H
#include <qstring.h>

#include "../User.h"


class Login {
public:
    std::optional<User>login(QString username,QString password);
};



#endif //LOGIN_H
