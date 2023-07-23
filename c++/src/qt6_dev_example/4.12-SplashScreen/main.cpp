//
// Created by leever on 9/13/2022.
//
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPixmap pixmap("Qt.png");
    QSplashScreen splashScreen(pixmap);
    splashScreen.show();
    QApplication::processEvents();
    GMainWindow mainWindow;
    mainWindow.show();
    splashScreen.finish(&mainWindow);
    return QApplication::exec();
}