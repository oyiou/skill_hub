//
// Created by leever on 9/13/2022.
//
#include "MapWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    QFont font("ARPL KaitiM GB", 12);
    font.setBold(true);
    QApplication::setFont(font);
    MapWidget mapWidget;
    mapWidget.show();
    return QApplication::exec();
}