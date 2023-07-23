//
// Created by leever on 9/13/2022.
//
#include "MainWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    QFont font("ZYSing18030", 12);
    QApplication::setFont(font);
    MainWidget mainWidget;
    mainWidget.show();
    return QApplication::exec();
}