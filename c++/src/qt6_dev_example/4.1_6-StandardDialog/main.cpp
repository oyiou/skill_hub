//
// Created by leever on 9/27/2022.
//
#include <QApplication>
#include "Dialog.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    Dialog dialog;
    dialog.show();
    return QApplication::exec();
}