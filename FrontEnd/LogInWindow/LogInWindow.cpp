//
// Created by ziga zoric on 01.06.25.
//

#include "LogInWindow.h"
#include "../../BackEnd/Auth/Login/Login.h"
#include "../MainWindowUser/MainWindow.h"
#include <QWidget>
#include <QBoxLayout>
#include <QObject>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <QProgressBar>

#include "../RegisterWindow/RegisterWindow.h"
#include <QPushButton>

QWidget *LogInWindow::logInWindow() {

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


   QObject::connect(registerButton,&QPushButton::clicked,[=] {
       RegisterWindow rw;
       QWidget* regWindow = rw.registerWindow();
       regWindow->show();
       window->close();
   });

    QObject::connect(loginButton, &QPushButton::clicked, [=]() mutable {
    QString user = username->text();
    QString pass = password->text();

    Login lg;
    auto loggedInUser = lg.login(user, pass);
    if (loggedInUser.has_value()) {

        QWidget* loadingScreen = new QWidget;
        loadingScreen->setFixedSize(300, 100);
        loadingScreen->setWindowTitle("Logging in...");

        QVBoxLayout* layout = new QVBoxLayout;
        QProgressBar* progress = new QProgressBar;
        progress->setRange(0, 100);
        layout->addWidget(progress);

        QLabel* label = new QLabel("Loading your dashboard...");
        layout->addWidget(label);

        loadingScreen->setLayout(layout);
        loadingScreen->show();


        QTimer* timer = new QTimer(loadingScreen);
        int* value = new int(0);

        QObject::connect(timer, &QTimer::timeout, [=]() mutable {
            (*value) += 10;
            progress->setValue(*value);

            if (*value >= 100) {
                timer->stop();
                loadingScreen->close();


                MainWindow mw;
                QWidget* newMainWindow = mw.mainWindow(loggedInUser.value());
                newMainWindow->show();
                window->close();
            }
        });

        timer->start(100);
    } else {
        QMessageBox::warning(window, "Login failed", "Invalid credentials.");
    }
});
    window->setLayout(box_layout);
    window->show();


    return window;
}
