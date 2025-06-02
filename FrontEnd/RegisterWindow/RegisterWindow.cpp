//
// Created by ziga zoric on 03.06.25.
//
#include "../LogInWindow/LogInWindow.h"
#include "RegisterWindow.h"
#include "../../BackEnd/Auth/Register/Register.h"

#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <qpushbutton.h>
#include <QMessageBox>

QWidget* RegisterWindow::registerWindow() {
    QWidget* window = new QWidget;
    window->resize(850, 560);
    window->setWindowTitle("Register");

    QLabel* usernameLabel = new QLabel("Username");
    QLabel* passwordLabel = new QLabel("Password");
    QLabel* emailLabel = new QLabel("Email");

    QLineEdit* usernameEdit = new QLineEdit;
    QLineEdit* passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);
    QLineEdit* emailEdit = new QLineEdit;


    QPushButton* registerButton = new QPushButton("Register");
    QPushButton* loginButton = new QPushButton("Back to login");

    QBoxLayout* box_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    box_layout->addWidget(usernameLabel);
    box_layout->addWidget(usernameEdit);
    box_layout->addWidget(passwordLabel);
    box_layout->addWidget(passwordEdit);
    box_layout->addWidget(emailLabel);
    box_layout->addWidget(emailEdit);
    box_layout->addWidget(registerButton);
    box_layout->addWidget(loginButton);

    QObject::connect(registerButton,&QPushButton::clicked,[=] {
        QString username = usernameEdit->text();
        QString password = passwordEdit->text();
        QString email = emailEdit->text();

        qDebug() << "Username: " << username;
        qDebug() << "Password: " << password;
        qDebug() << "Email: " << email;

        Register reg;
        reg.registerUser(username, password,email);
        if (reg.registerUser(username,password,email)) {
            LogInWindow liw;
            QMessageBox::information(window,"Registration successful", "User was successfully registered!");

            QWidget* logInWindow = liw.logInWindow();
            logInWindow->show();
            window->close();
        }
    });

    QObject::connect(loginButton,&QPushButton::clicked,[=] {
        LogInWindow liw;
        QWidget* loginWindow = liw.logInWindow();
        loginWindow->show();
        window->close();
    });

    window->setLayout(box_layout);
    window->show();

    return window;
}

