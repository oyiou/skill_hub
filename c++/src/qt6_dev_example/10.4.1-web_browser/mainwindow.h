//
// Created by leever on 2023/6/2.
//

#ifndef C_MAINWINDOW_H
#define C_MAINWINDOW_H

#include <QMainWindow>

class QNetworkReply;
class QNetworkAccessManager;

class MainWindow: public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QNetworkAccessManager *manager;
private slots:
    void replyFinished(QNetworkReply*);
};

#endif //C_MAINWINDOW_H
