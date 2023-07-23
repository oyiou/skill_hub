//
// Created by leever on 9/13/2022.
//
#include "ExtensionDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ExtensionDialog extensionDialog;
    extensionDialog.show();
    return QApplication::exec();
}