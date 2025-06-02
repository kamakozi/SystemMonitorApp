#include <iostream>
#include "FrontEnd/LogInWindow/LogInWindow.h"
#include <QWidget>
#include <QApplication>
#include "BackEnd/Tables/ReadSqlTables.h"

int main(int argc,char *argv[]) {
    ReadSqlTables rsq;
    rsq.readSqlFile();

    QApplication app(argc,argv);

    LogInWindow liw;

    QWidget* window = liw.logInWindow();
    window->show();
    return app.exec();
}

