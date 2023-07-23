//
// Created by leever on 9/27/2022.
//
#include "Content.h"
#include <QApplication>
#include <QSplitter>
#include <QListWidget>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    QFont font("AR PL KaitiM GB", 12);
    QApplication::setFont(font);

    auto *splitterMain = new QSplitter(Qt::Horizontal, nullptr);
    splitterMain->setOpaqueResize(true);
    auto *list = new QListWidget(splitterMain);
    list->insertItem(0, QObject::tr("基本信息"));
    list->insertItem(1, QObject::tr("联系方式"));
    list->insertItem(2, QObject::tr("详细资料"));

    auto *content = new Content(splitterMain);
    QObject::connect(list, SIGNAL(currentRowChanged(int)), content->stacked, SLOT(setCurrentIndex(int)));
    splitterMain->setWindowTitle(QObject::tr("修改用户资料"));
    splitterMain->setMinimumSize(splitterMain->minimumSize());
    splitterMain->setMaximumSize(splitterMain->maximumSize());
    splitterMain->show();

    return QApplication::exec();
}