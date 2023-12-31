//
// Created by leever on 2023/6/2.
//
#include "watcher.h"
#include <QVBoxLayout>
#include <QDir>
#include <QMessageBox>
#include <QApplication>

Watcher::Watcher(QWidget *parent): QWidget(parent) {
    QStringList args = qApp->arguments();
    QString path;
    if (args.count() > 1) {
        path = args[1];
    } else {
        path = QDir::currentPath();
    }

    pathLabel = new QLabel;
    pathLabel->setText(tr("监视的目录： ") + path);
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(pathLabel);

    fsWatcher.addPath(path);
    connect(&fsWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(directoryChanged(QString)));
}

void Watcher::directoryChanged(const QString& path) {
    QMessageBox::information(nullptr, tr("目录发生变化"), path);
}
