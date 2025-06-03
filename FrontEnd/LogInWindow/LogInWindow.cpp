#include "LogInWindow.h"
#include "../../BackEnd/Auth/Login/Login.h"
#include "../MainWindowUser/MainWindow.h"
#include "../RegisterWindow/RegisterWindow.h"

#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QProgressBar>

QWidget* LogInWindow::logInWindow() {
    QWidget* window = new QWidget;
    window->resize(850, 560);
    window->setWindowTitle("System Monitor App");


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
            background-color: #1e88e5;
            color: white;
            border: none;
            border-radius: 10px;
            padding: 10px;
        }
        QPushButton:hover {
            background-color: #42a5f5;
        }
        QPushButton:pressed {
            background-color: #1565c0;
        }
        QLabel#Title {
            font-size: 22px;
            font-weight: bold;
            padding-bottom: 10px;
        }
    )";
    window->setStyleSheet(modernStyle);

    QWidget* card = new QWidget;
    card->setFixedSize(400, 380);
    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(10, 20, 10, 10);
    cardLayout->setSpacing(15);

    QLabel* logo = new QLabel;
    logo->setAlignment(Qt::AlignCenter);
    logo->setPixmap(QPixmap("/Users/zigazoric/Desktop/cpp/SystemMonitorApp/Resources/Images/image.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));


    QLabel* title = new QLabel("Login to System Monitor");
    title->setObjectName("Title");
    title->setAlignment(Qt::AlignCenter);

    QLineEdit* username = new QLineEdit;
    username->setPlaceholderText("Enter username");

    QLineEdit* password = new QLineEdit;
    password->setPlaceholderText("Enter password");
    password->setEchoMode(QLineEdit::Password);

    QPushButton* loginButton = new QPushButton("Login");
    QLabel* noAcc = new QLabel("No account? Register now!");
    noAcc->setAlignment(Qt::AlignCenter);
    QPushButton* registerButton = new QPushButton("Register");

    cardLayout->addWidget(logo);
    cardLayout->addWidget(title);
    cardLayout->addWidget(username);
    cardLayout->addWidget(password);
    cardLayout->addWidget(loginButton);
    cardLayout->addWidget(noAcc);
    cardLayout->addWidget(registerButton);



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


    QObject::connect(registerButton, &QPushButton::clicked, [=]() {
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

    window->setLayout(layout);
    window->show();
    return window;
}