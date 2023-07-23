//
// Created by leever on 9/13/2022.
//
#include "Geometry.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    Geometry geometry;
    geometry.show();
    return QApplication::exec();
}