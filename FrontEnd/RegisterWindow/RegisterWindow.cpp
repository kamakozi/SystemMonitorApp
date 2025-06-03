#include "../LogInWindow/LogInWindow.h"
#include "RegisterWindow.h"
#include "../../BackEnd/Auth/Register/Register.h"

#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QPropertyAnimation>

QWidget* RegisterWindow::registerWindow() {
    QWidget* window = new QWidget;
    window->resize(850, 560);
    window->setWindowTitle("System Monitor App - Register");


    QString modernStyle = R"(
        QWidget {
            background-color: #121212;
            color: #ffffff;
            font-family: 'Segoe UI';
        }
        QLineEdit {
            background-color: rgba(255, 255, 255, 0.05);
            border: 1px solid #444;
            border-radius: 10px;
            padding: 10px;
        }
        QPushButton {
            background-color: #43a047;
            color: white;
            border: none;
            border-radius: 10px;
            padding: 10px;
        }
        QPushButton:hover {
            background-color: #66bb6a;
        }
        QPushButton:pressed {
            background-color: #2e7d32;
        }
        QLabel#Title {
            font-size: 22px;
            font-weight: bold;
            padding-bottom: 10px;
        }
    )";
    window->setStyleSheet(modernStyle);


    QWidget* card = new QWidget;
    card->setFixedSize(400, 400);
    QVBoxLayout* cardLayout = new QVBoxLayout(card);

    QLabel* logo = new QLabel;
    logo->setAlignment(Qt::AlignCenter);
    logo->setPixmap(QPixmap("/Users/zigazoric/Desktop/cpp/SystemMonitorApp/Resources/Images/image.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel* title = new QLabel("Create Your Account");
    title->setObjectName("Title");
    title->setAlignment(Qt::AlignCenter);

    QLineEdit* usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("Enter username");

    QLineEdit* emailEdit = new QLineEdit;
    emailEdit->setPlaceholderText("Enter email");

    QLineEdit* passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("Enter password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    QPushButton* registerButton = new QPushButton("Register");
    QPushButton* loginButton = new QPushButton("Back to Login");

    cardLayout->addWidget(logo);
    cardLayout->addWidget(title);
    cardLayout->addWidget(usernameEdit);
    cardLayout->addWidget(emailEdit);
    cardLayout->addWidget(passwordEdit);
    cardLayout->addWidget(registerButton);
    cardLayout->addWidget(loginButton);


    QGraphicsOpacityEffect* fadeEffect = new QGraphicsOpacityEffect(card);
    card->setGraphicsEffect(fadeEffect);

    QPropertyAnimation* fadeAnim = new QPropertyAnimation(fadeEffect, "opacity");
    fadeAnim->setDuration(800);
    fadeAnim->setStartValue(0.0);
    fadeAnim->setEndValue(1.0);
    fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);

    QVBoxLayout* layout = new QVBoxLayout(window);
    layout->addStretch();
    layout->addWidget(card, 0, Qt::AlignCenter);
    layout->addStretch();


    QObject::connect(loginButton, &QPushButton::clicked, [=]() {
        LogInWindow liw;
        QWidget* loginWindow = liw.logInWindow();
        loginWindow->show();
        window->close();
    });


    QObject::connect(registerButton, &QPushButton::clicked, [=]() {
        QString username = usernameEdit->text();
        QString password = passwordEdit->text();
        QString email = emailEdit->text();
        if (username.isEmpty()) {
            QMessageBox::warning(window,"Username error","Username cannot be empty");
            return;
        }
        if (password.isEmpty()) {
            QMessageBox::warning(window,"Password error", "Password can't be empty");
            return;
        }
        if (email.isEmpty()) {
            QMessageBox::warning(window,"Email error","Email can't be empty");
            return;
        }

        if (!email.contains("@") || !email.contains(".")) {
            QMessageBox::warning(window, "Invalid Email", "Please enter a valid email address.");
            return;
        }

        if (password.length() < 6) {
            QMessageBox::warning(window, "Weak Password", "Password must be at least 6 characters.");
            return;
        }

        Register reg;
        if (reg.registerUser(username, password, email)) {
            QMessageBox::information(window, "Success", "Account created successfully!");
            LogInWindow liw;
            QWidget* loginWin = liw.logInWindow();
            loginWin->show();
            window->close();
        } else {
            QMessageBox::critical(window, "Error", "Username already taken or network error.");
        }
    });

    window->setLayout(layout);
    window->show();
    return window;
}