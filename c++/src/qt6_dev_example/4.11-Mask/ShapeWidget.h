//
// Created by leever on 9/30/2022.
//

#ifndef QT6_DEV_EXAMPLE_SHAPEWIDGET_H
#define QT6_DEV_EXAMPLE_SHAPEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class ShapeWidget: public QWidget {
    Q_OBJECT
public:
    explicit ShapeWidget(QWidget *parent = nullptr);
    ~ShapeWidget() override;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QPoint dragPosition;
};


#endif //QT6_DEV_EXAMPLE_SHAPEWIDGET_H
