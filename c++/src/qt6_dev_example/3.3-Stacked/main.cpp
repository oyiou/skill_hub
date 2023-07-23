//
// Created by leever on 9/13/2022.
//
#include <QtWidgets/QApplication>
#include "Stacked.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Stacked stacked;
    stacked.show();
    return QApplication::exec();
}