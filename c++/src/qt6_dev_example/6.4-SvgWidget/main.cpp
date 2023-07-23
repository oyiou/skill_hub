//
// Created by leever on 9/13/2022.
//
#include "SvgWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    SvgWidget svgWidget;
    svgWidget.show();
    return QApplication::exec();
}