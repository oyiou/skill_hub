//
// Created by leever on 2023/5/31.
//
#include <QApplication>
#include "modelex.h"
#include <QTableView>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    ModelEx modelEx;
    QTableView view;
    view.setModel(&modelEx);
    view.setWindowTitle(QObject::tr("modelEx"));
    view.resize(400, 400);
    view.show();
    return QApplication::exec();
}