//
// Created by leever on 9/13/2022.
//
#include "DrawWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    DrawWidget drawWidget;
    drawWidget.show();
    return QApplication::exec();
}