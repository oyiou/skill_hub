//
// Created by leever on 2023/6/2.
//
#include "mainwindow.h"
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent) {
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://www.baidu.com")));
}