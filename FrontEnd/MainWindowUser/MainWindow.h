//
// Created by ziga zoric on 03.06.25.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include "../../BackEnd/Auth/User.h"

class User;

class MainWindow {
public:
   QWidget* mainWindow(const User& user);

};



#endif //MAINWINDOW_H
