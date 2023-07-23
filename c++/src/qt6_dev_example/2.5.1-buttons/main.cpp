//
// Created by leever on 9/13/2022.
//
#include <QtWidgets/QApplication>
#include "buttons.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Buttons buttons;
    buttons.show();
    return QApplication::exec();
}