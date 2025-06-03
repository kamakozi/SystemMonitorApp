//
// Created by ziga zoric on 03.06.25.
//

#include "MainWindow.h"



QWidget *MainWindow::mainWindow(const User& user) {
    QWidget* window = new QWidget;
    window->resize(850,650);
    window->setWindowTitle("System Monitor app");


    window->show();

    return window;
}
