//
// Created by leever on 9/13/2022.
//
#include "ShapeWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ShapeWidget shapeWidget;
    shapeWidget.show();
    return QApplication::exec();
}