//
// Created by leever on 9/13/2022.
//
#include <QtWidgets/QApplication>
#include "Dock.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Dock dock;
    dock.show();
    return QApplication::exec();
}