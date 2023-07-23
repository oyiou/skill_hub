//
// Created by leever on 9/13/2022.
//
#include "Butterfly.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    auto *scene = new QGraphicsScene;
    scene->setSceneRect(QRectF(-200, -200, 400, 400));

    auto *butterfly = new Butterfly;
    butterfly->setPos(-100, 0);

    scene->addItem(butterfly);

    auto *view = new QGraphicsView;
    view->setScene(scene);
    view->resize(400, 400);
    view->show();

    return QApplication::exec();
}