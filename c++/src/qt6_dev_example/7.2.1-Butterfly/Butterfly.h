//
// Created by leever on 2022/10/10.
//

#ifndef QT6_DEV_EXAMPLE_BUTTERFLY_H
#define QT6_DEV_EXAMPLE_BUTTERFLY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

class Butterfly: public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit Butterfly(QObject *parent = nullptr);
    ~Butterfly() override;
    void timerEvent(QTimerEvent *) override;
    QRectF boundingRect() const override;
signals:
public slots:
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *styleOptionGraphicsItem, QWidget *widget) override;
private:
    bool up;
    QPixmap pixmapUp;
    QPixmap pixmapDown;
    qreal angle;
};


#endif //QT6_DEV_EXAMPLE_BUTTERFLY_H
