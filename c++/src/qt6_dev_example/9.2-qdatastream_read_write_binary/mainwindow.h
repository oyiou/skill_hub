//
// Created by leever on 2023/6/2.
//

#ifndef C_MAINWINDOW_H
#define C_MAINWINDOW_H

#include <QMainWindow>

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void fileFun();
};

#endif //C_MAINWINDOW_H
