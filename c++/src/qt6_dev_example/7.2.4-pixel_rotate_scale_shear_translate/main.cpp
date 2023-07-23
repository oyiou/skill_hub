//
// Created by leever on 9/13/2022.
//
#include "mainwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    QFont font("ARPL KaitiM GB", 12);
    font.setBold(true);
    QApplication::setFont(font);
    MainWidget mainWidget;
    mainWidget.show();

    return QApplication::exec();
}