//
// Created by leever on 2023/6/2.
//
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);

    QFile data("data.txt");
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out << QObject::tr("score:") << qSetFieldWidth(10) << Qt::left << 90 << Qt::endl ;
    }

    return QCoreApplication::exec();
}