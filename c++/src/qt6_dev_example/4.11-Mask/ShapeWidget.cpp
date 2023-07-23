//
// Created by leever on 9/30/2022.
//

#include "ShapeWidget.h"
#include <QPixmap>
#include <QBitmap>

ShapeWidget::ShapeWidget(QWidget *parent): QWidget(parent) {
    QPixmap pixmap;
    pixmap.load("16.png", nullptr, Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
    resize(pixmap.size());
    setMask(QBitmap(pixmap.mask()));
}

void ShapeWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    } else if (event->button() == Qt::RightButton) {
        close();
    }
}

void ShapeWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

void ShapeWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap("16.png"));
}

ShapeWidget::~ShapeWidget() = default;
