//
// Created by leever on 9/13/2022.
//
#include "ProcessDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ProcessDialog processDialog;
    processDialog.show();
    return QApplication::exec();
}