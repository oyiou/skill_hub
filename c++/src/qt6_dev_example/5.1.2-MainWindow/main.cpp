//
// Created by leever on 9/13/2022.
//
#include "ImageProcessor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    QFont font("ZYSong18030", 12);
    QApplication::setFont(font);

    ImageProcessor imageProcessor;
    imageProcessor.show();
    return QApplication::exec();
}