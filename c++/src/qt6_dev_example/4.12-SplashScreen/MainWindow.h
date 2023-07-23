//
// Created by leever on 9/30/2022.
//

#ifndef QT6_DEV_EXAMPLE_MAINWINDOW_H
#define QT6_DEV_EXAMPLE_MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};


#endif //QT6_DEV_EXAMPLE_MAINWINDOW_H
