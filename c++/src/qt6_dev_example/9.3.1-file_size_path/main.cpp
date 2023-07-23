//
// Created by leever on 2023/6/2.
//
#include <QCoreApplication>
#include <QStringList>
#include <QDir>
#include <QtDebug>

qint64 du(const QString &path) {
    QDir dir(path);
    qint64 size = 0;
    foreach (QFileInfo fileInfo, dir.entryInfoList(QDir::Files)) {
        size += fileInfo.size();
    }

    foreach (QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        size += du(path + QDir::separator() + subDir);
    }

    char unit = 'B';
    qint64  curSize = size;
    if (curSize > 1024) {
        curSize /= 1024;
        unit = 'K';
        if (curSize > 1024) {
            curSize /= 1024;
            unit = 'M';
            if (curSize > 1024) {
                curSize /= 1024;
                unit = 'G';
            }
        }
    }
    qDebug() << curSize << unit << "\t" << qPrintable(path) << Qt::endl;
    return size;
}

int main (int argc, char *argv[]) {
    QCoreApplication application(argc, argv);

    QStringList args = QCoreApplication::arguments();
    QString path;
    if (args.count() > 1) {
        path = args[1];
    } else {
        path = QDir::currentPath();
    }
    qDebug() << path << Qt::endl;
    du(path);
    return QCoreApplication::exec();
}