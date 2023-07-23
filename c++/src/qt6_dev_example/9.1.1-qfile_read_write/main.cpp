//
// Created by leever on 2023/6/1.
//
#include <QCoreApplication>
#include <QFile>
#include <QtDebug>

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);

    QFile file("textFile1.txt");
    if (file.open(QIODevice::ReadOnly)) {
        char buffer[2048];
        qint64 lineLen = file.readLine(buffer, sizeof(buffer));
        if (lineLen != -1) {
            qDebug() << buffer;
        }
    }
    return QCoreApplication::exec();
}