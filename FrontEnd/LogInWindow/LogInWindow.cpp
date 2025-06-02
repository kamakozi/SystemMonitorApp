//
// Created by ziga zoric on 01.06.25.
//

#include "LogInWindow.h"
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "../../BackEnd/Tables/ReadSqlTables.h"
#include <iostream>

QWidget *LogInWindow::logInWindow() {
    try{
    ReadSqlTables rsq;
    rsq.readSqlFile();
    }catch (std::exception& e) {
        std::cerr << "Load failed at the start for tables" << e.what() <<std::endl;
    }
    QWidget* window = new QWidget;
    window->resize(850,560);
    window->setWindowTitle("System monitor app");


    //Buttons
    QPushButton* loginButton = new QPushButton("Login");
    QPushButton* registerButton = new QPushButton("Register");


    //LineEdits
    QLineEdit* username = new QLineEdit();
    username->setPlaceholderText("Enter username");
    QLineEdit* password = new QLineEdit();
    password->setPlaceholderText("Enter Password");


    QLabel* noAcc =new QLabel("No account? Register now!");


    QBoxLayout* box_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    box_layout->addWidget(username);
    box_layout->addWidget(password);
    box_layout->addWidget(loginButton);
    box_layout->addWidget(noAcc);
    box_layout->addWidget(registerButton);

    window->setLayout(box_layout);
    window->show();


    return window;
}
