//
// Created by leever on 2022/10/10.
//

#ifndef QT6_DEV_EXAMPLE_MAPWIDGET_H
#define QT6_DEV_EXAMPLE_MAPWIDGET_H

#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>

class MapWidget: public QGraphicsView {
    Q_OBJECT
public:
    MapWidget();
    ~MapWidget() override;

    void readMap();
    QPointF mapTopMap(QPointF);
public slots:
    void slotZoom(int);
private:
    void drawBackground(QPainter *painter, const QRectF &rectF) override;
    void mouseMoveEvent(QMouseEvent *mouseEvent) override;
private:
    QPixmap map;
    qreal zoom;
    QLabel *viewCoord;
    QLabel *sceneCoord;
    QLabel *mapCoord;
    double x1, y1, x2, y2;
};


#endif //QT6_DEV_EXAMPLE_MAPWIDGET_H
