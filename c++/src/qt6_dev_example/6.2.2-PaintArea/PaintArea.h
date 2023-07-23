//
// Created by leever on 2022/10/9.
//

#ifndef QT6_DEV_EXAMPLE_PAINTAREA_H
#define QT6_DEV_EXAMPLE_PAINTAREA_H

#include <QPen>
#include <QBrush>
#include <QWidget>
#include <QPaintEvent>

class PaintArea: public QWidget {
    Q_OBJECT
public:
    enum Shape {
        Line, Rectangle, RoundRect, Ellipse, Polygon,
        Polyline, Points, Arc, Path, Text, Pixmap
    };
    explicit PaintArea(QWidget *parent = nullptr);

    void setShape(Shape);
    void setPen(QPen);
    void setBrush(QBrush);
    void setFillRule(Qt::FillRule);
    void paintEvent(QPaintEvent *) override;
signals:
public slots:
private:
    Shape shape;
    QPen pen;
    QBrush brush;
    Qt::FillRule fillRule;
};


#endif //QT6_DEV_EXAMPLE_PAINTAREA_H
