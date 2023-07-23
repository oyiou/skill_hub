//
// Created by leever on 2022/10/10.
//

#include "Butterfly.h"
#include <cmath>

const static double PI = 3.1416;

Butterfly::Butterfly(QObject *parent) : QObject(parent) {
    up = true;
    pixmapUp.load("up.png");
    pixmapDown.load("down.png");
    startTimer(100);
}

QRectF Butterfly::boundingRect() const {
    qreal adjust = 2;
    return {-pixmapUp.width()/2.0 - adjust,-pixmapUp.height()/2.0 - adjust,
                  pixmapUp.width() + adjust*2,pixmapUp.height() + adjust*2};
}

void Butterfly::paint(QPainter *painter, const QStyleOptionGraphicsItem *styleOptionGraphicsItem, QWidget *widget) {
    if (up) {
        painter->drawPixmap(boundingRect().topLeft(), pixmapUp);
        up = !up;
    } else {
        painter->drawPixmap(boundingRect().topLeft(), pixmapDown);
        up = !up;
    }
}

void Butterfly::timerEvent(QTimerEvent *) {
    qreal edgeX = scene()->sceneRect().right() + boundingRect().width()/2;
    qreal edgeTop = scene()->sceneRect().top() + boundingRect().height()/2;
    qreal edgeBottom = scene()->sceneRect().bottom() + boundingRect().height()/2;
    if (pos().x() >= edgeX)
        setPos(scene()->sceneRect().left(), pos().y());
    if (pos().y() <= edgeTop)
        setPos(pos().x(), scene()->sceneRect().bottom());
    if (pos().y() >= edgeBottom)
        setPos(pos().x(), scene()->sceneRect().top());
    angle += (rand() % 10) / 20.0;
    qreal dX = fabs(sin(angle * PI) * 10.0);
    qreal dY = (rand() % 20) - 10.0;

    setPos(mapToParent(dX, dY));
}

Butterfly::~Butterfly() = default;
