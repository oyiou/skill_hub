//
// Created by leever on 9/13/2022.
//
#include "Palette.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Palette palette;
    palette.show();
    return QApplication::exec();
}