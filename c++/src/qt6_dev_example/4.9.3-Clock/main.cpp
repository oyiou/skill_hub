//
// Created by leever on 9/13/2022.
//
#include "DigitClock.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    DigitClock digitClock;
    digitClock.show();
    return QApplication::exec();
}