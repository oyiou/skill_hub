//
// Created by leever on 9/27/2022.
//

#include <QTextEdit>
#include <QDockWidget>
#include "Dock.h"

Dock::Dock(QWidget *parent): QMainWindow(parent) {
    setWindowTitle(tr("Dock")); // 设置主窗口的标题栏文字
    auto *te = new QTextEdit(this); // 定义一个 QTextEdit 对象作为主窗口
    te->setText(tr("Main"));
    te->setAlignment(Qt::AlignCenter);
    setCentralWidget(te);   // 将此编辑框设为主窗口的中央窗体
    // 停靠窗口 1
    auto *dock = new QDockWidget(tr("Dock1"), this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    auto *te1 = new QTextEdit();
    te1->setText(tr("Window1, The dock widget can be moved between dlcoks by th user" ""));
    dock->setWidget(te1);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    // 停靠窗口 2
    dock = new QDockWidget(tr("Dock2"), this);
    dock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    auto *te2 = new QTextEdit();
    te2->setText(tr("Window2, The dock widget can be detached from the main window," "and floated as an independent window, and can be closed"));
    dock->setWidget(te2);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    // 停靠窗口 3
    dock = new QDockWidget(tr("Dock3"), this);
    dock->setFeatures(
            QDockWidget::DockWidgetClosable
            | QDockWidget::DockWidgetMovable
            | QDockWidget::DockWidgetFloatable
            | QDockWidget::DockWidgetVerticalTitleBar
            | QDockWidget::DockWidgetFeatureMask);
    auto te3 = new QTextEdit();
    te3->setText(tr("Window3, The dock widget can be closed, moved, and floated"));
    dock->setWidget(te3);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}

Dock::~Dock() = default;
