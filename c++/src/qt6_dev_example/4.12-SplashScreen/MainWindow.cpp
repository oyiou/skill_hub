//
// Created by leever on 9/30/2022.
//

#include "MainWindow.h"

#include <QTextEdit>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setWindowTitle("Splash Example");

    auto *edit = new QTextEdit;
    edit->setText("Splash Example!");
    setCentralWidget(edit);

    resize(250, 300);
    Sleep(2*1000);
}

MainWindow::~MainWindow() = default;
