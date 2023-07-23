//
// Created by leever on 9/27/2022.
//
#include <QMainWindow>
#include <QApplication>
#include <QSplitter>
#include <QTextEdit>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QFont font("ZYSong1830", 12);
    QApplication::setFont(font);
    // 主分隔窗口
    auto *splitterMain = new QSplitter(Qt::Horizontal, nullptr);
    auto *textLeft = new QTextEdit(QObject::tr("Left Widget"), splitterMain);
    textLeft->setAlignment(Qt::AlignCenter);
    // 右部分分割窗口
    auto *splitterRight = new QSplitter(Qt::Vertical, splitterMain);
    splitterRight->setOpaqueResize(false);
    auto *textUp = new QTextEdit(QObject::tr("Top Widget"), splitterRight);
    textUp->setAlignment(Qt::AlignCenter);
    auto *textDown = new QTextEdit(QObject::tr("Bottom Widget"), splitterRight);
    textDown->setAlignment(Qt::AlignCenter);
    splitterMain->setStretchFactor(1, 1);
    splitterMain->setWindowTitle(QObject::tr("Splitter"));
    splitterMain->show();
    // MainWindow w;
    // w.show();
    return QApplication::exec();
}