#include "MainWindow.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QString>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

QWidget* MainWindow::mainWindow(const User& user) {
    QWidget* window = new QWidget;
    window->resize(850, 650);
    window->setWindowTitle("System Monitor App");


    QString modernDarkStyle = R"(
        QWidget {
            background-color: #1e1e2f;
            color: #e0e0e0;
            font-family: 'Segoe UI', sans-serif;
        }
        QPushButton {
            background-color: #29293d;
            border: 1px solid #444;
            border-radius: 10px;
            padding: 10px 20px;
            color: white;
        }
        QPushButton:hover {
            background-color: #3c3c5c;
        }
        QPushButton:pressed {
            background-color: #1a1a2a;
        }
    )";
    window->setStyleSheet(modernDarkStyle);


    QPushButton* homeBtn = new QPushButton("🏠 Home");
    QPushButton* usageBtn = new QPushButton("📊 Usages");

    QHBoxLayout* navLayout = new QHBoxLayout;
    navLayout->addStretch();
    navLayout->addWidget(homeBtn);
    navLayout->addWidget(usageBtn);
    navLayout->addStretch();


    QStackedWidget* stackedWidget = new QStackedWidget;

    QLabel* homePage = new QLabel("👤 Logged in as: <b>" + QString::fromStdString(user.getName()) + "</b>");
    homePage->setAlignment(Qt::AlignCenter);

    QLabel* usagePage = new QLabel("📈 Usage statistics will be displayed here...");
    usagePage->setAlignment(Qt::AlignCenter);

    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(usagePage);

    // 🧱 Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(window);
    mainLayout->addLayout(navLayout);
    mainLayout->addWidget(stackedWidget);

    auto fadeSwitch = [=](int index) {
        QWidget* current = stackedWidget->currentWidget();
        QWidget* next = stackedWidget->widget(index);

        QGraphicsOpacityEffect* fadeOutEffect = new QGraphicsOpacityEffect(current);
        current->setGraphicsEffect(fadeOutEffect);

        QPropertyAnimation* fadeOut = new QPropertyAnimation(fadeOutEffect, "opacity");
        fadeOut->setDuration(200);
        fadeOut->setStartValue(1);
        fadeOut->setEndValue(0);

        QObject::connect(fadeOut, &QPropertyAnimation::finished, [=]() {
            stackedWidget->setCurrentIndex(index);

            QGraphicsOpacityEffect* fadeInEffect = new QGraphicsOpacityEffect(next);
            next->setGraphicsEffect(fadeInEffect);

            QPropertyAnimation* fadeIn = new QPropertyAnimation(fadeInEffect, "opacity");
            fadeIn->setDuration(200);
            fadeIn->setStartValue(0);
            fadeIn->setEndValue(1);
            fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
        });

        fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
    };


    QObject::connect(homeBtn, &QPushButton::clicked, [=]() {
        fadeSwitch(0);
    });

    QObject::connect(usageBtn, &QPushButton::clicked, [=]() {
        fadeSwitch(1);
    });

    window->setLayout(mainLayout);
    window->show();
    return window;
}