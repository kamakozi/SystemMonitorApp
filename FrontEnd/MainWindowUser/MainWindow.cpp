#include "MainWindow.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QString>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "CpuUsageWidget/CpuUsage.h"

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
            padding: 10px;
            color: white;
            text-align: left;
        }
        QPushButton:hover {
            background-color: #3c3c5c;
        }
        QPushButton:pressed {
            background-color: #1a1a2a;
        }
    )";
    window->setStyleSheet(modernDarkStyle);


    QPushButton* homeBtn = new QPushButton("Home");
    QPushButton* usageBtn = new QPushButton("Usages");

    QHBoxLayout* navLayout = new QHBoxLayout;
    navLayout->addStretch();
    navLayout->addWidget(homeBtn);
    navLayout->addWidget(usageBtn);
    navLayout->addStretch();


    QStackedWidget* stackedWidget = new QStackedWidget;

    QLabel* homePage = new QLabel("Logged in as: <b>" + QString::fromStdString(user.getName()) + "</b>");
    homePage->setAlignment(Qt::AlignCenter);


    QWidget* usagePage = new QWidget;
    QHBoxLayout* usageLayout = new QHBoxLayout(usagePage);


    QVBoxLayout* leftMenuLayout = new QVBoxLayout;
    QPushButton* cpuBtn = new QPushButton("CPU");
    QPushButton* gpuBtn = new QPushButton("GPU");
    QPushButton* ramBtn = new QPushButton("RAM");
    QPushButton* netBtn = new QPushButton("Internet");

    leftMenuLayout->addWidget(cpuBtn);
    leftMenuLayout->addWidget(gpuBtn);
    leftMenuLayout->addWidget(ramBtn);
    leftMenuLayout->addWidget(netBtn);
    leftMenuLayout->addStretch();

    QStackedWidget* graphStack = new QStackedWidget;
    CpuUsage* cpuWidget = new CpuUsage;
    QWidget* gpuWidget = new QLabel("GPU Usage");
    QWidget* ramWidget = new QLabel("RAM Usage");
    QWidget* netWidget = new QLabel("Internet Usage");

    graphStack->addWidget(cpuWidget);
    graphStack->addWidget(gpuWidget);
    graphStack->addWidget(ramWidget);
    graphStack->addWidget(netWidget);

    usageLayout->addLayout(leftMenuLayout);
    usageLayout->addWidget(graphStack);


    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(usagePage);


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

    QObject::connect(cpuBtn, &QPushButton::clicked, [=]() {
        graphStack->setCurrentIndex(0);
    });
    QObject::connect(gpuBtn, &QPushButton::clicked, [=]() {
        graphStack->setCurrentIndex(1);
    });
    QObject::connect(ramBtn, &QPushButton::clicked, [=]() {
        graphStack->setCurrentIndex(2);
    });
    QObject::connect(netBtn, &QPushButton::clicked, [=]() {
        graphStack->setCurrentIndex(3);
    });

    window->setLayout(mainLayout);
    window->show();
    return window;
}