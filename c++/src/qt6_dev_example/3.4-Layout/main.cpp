//
// Created by leever on 9/13/2022.
//
#include "Dialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Dialog dialog;
    dialog.show();
    return QApplication::exec();
}