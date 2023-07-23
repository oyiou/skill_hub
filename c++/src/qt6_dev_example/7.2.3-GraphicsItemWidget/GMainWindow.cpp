//
// Created by leever on 2022/10/11.
//

#include "GMainWindow.h"

GMainWindow::GMainWindow(QWidget *parent) :QMainWindow(parent) {
    createActions();
    createMenus();

    scene = new QGraphicsScene;
    scene->setSceneRect(-200, -200, 400, 400);

    initScene();

    auto view = new QGraphicsView;
    view->setScene(scene);
    view->setMinimumSize(400, 400);
    view->show();

    setCentralWidget(view);
    resize(550, 450);
    setWindowTitle(tr("Graphics Items"));
}

void GMainWindow::createActions() {
    newAct = new QAction(tr("新建"), this);
    clearAct = new QAction(tr("清除"), this);
    exitAct = new QAction(tr("退出"), this);
    addEllipseItemAct = new QAction(tr("加入 椭圆"), this);
    addPolygonItemAct = new QAction(tr("加入 多边形"), this);
    addTextItemAct = new QAction(tr("加入 文字"), this);
    addRectItemAct = new QAction(tr("加入 长方形"), this);
    addAlphaItemAct = new QAction(tr("加入 透明图片"), this);

    connect(newAct, SIGNAL(triggered()), this, SLOT(slotNew()));
    connect(clearAct, SIGNAL(triggered()), this, SLOT(slotClear()));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    connect(addEllipseItemAct, SIGNAL(triggered()), this, SLOT(slotAddEllipseItem()));
    connect(addPolygonItemAct, SIGNAL(triggered()), this, SLOT(slotAddPolygonItem()));
    connect(addTextItemAct, SIGNAL(triggered()), this, SLOT(slotAddTextItem()));
    connect(addRectItemAct, SIGNAL(triggered()), this, SLOT(slotAddRectItem()));
    connect(addAlphaItemAct, SIGNAL(triggered()), this, SLOT(slotAddAlphaItem()));
}

void GMainWindow::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(clearAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    QMenu *itemsMenu = menuBar()->addMenu(tr("元素"));
    itemsMenu->addAction(addEllipseItemAct);
    itemsMenu->addAction(addPolygonItemAct);
    itemsMenu->addAction(addTextItemAct);
    itemsMenu->addAction(addRectItemAct);
    itemsMenu->addAction(addAlphaItemAct);
}

void GMainWindow::initScene() {
    int i;
    for (i = 0; i < 3; i++)
        slotAddPolygonItem();
}

GMainWindow::~GMainWindow() = default;
