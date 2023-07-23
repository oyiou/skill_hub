//
// Created by leever on 9/13/2022.
//
#include "Drawer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Drawer drawer;
    drawer.show();
    return QApplication::exec();
}