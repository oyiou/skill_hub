//
// Created by leever on 2022/10/9.
//

#include "PaintArea.h"
#include <QPainter>
#include <utility>
#include <QPainterPath>

PaintArea::PaintArea(QWidget *parent) : QWidget(parent) {
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setMinimumSize(400, 400);
}

void PaintArea::setShape(PaintArea::Shape s) {
    shape = s;
    update();
}

void PaintArea::setPen(QPen p) {
    pen = std::move(p);
    update();
}

void PaintArea::setBrush(QBrush b) {
    brush = std::move(b);
    update();
}

void PaintArea::setFillRule(Qt::FillRule rule) {
    fillRule = rule;
    update();
}

void PaintArea::paintEvent(QPaintEvent *paintEvent) {
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);

    QRect(50, 100, 300, 200);

    static const QPoint points[4] = {
            QPoint(150, 100),
            QPoint(300, 150),
            QPoint(350, 250),
            QPoint(100, 300)
    };
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;

    QPainterPath painterPath;
    painterPath.addRect(150, 150, 100, 100);
    painterPath.moveTo(100, 100);
    painterPath.cubicTo(300, 100, 200, 200, 300, 300);
    painterPath.cubicTo(100, 300, 200, 200, 100, 100);
    painterPath.setFillRule(fillRule);
    switch (shape) {
        case Line:  // 线
            painter.drawLine(rect().topLeft(), rect().bottomRight());
            break;
        case Rectangle: // 长方形
            painter.drawRect(rect());
            break;
        case RoundRect: // 圆角方形
            painter.drawRoundedRect(rect(),1,2);
            break;
        case Ellipse:   // 椭圆形
            painter.drawEllipse(rect());
            break;
        case Polygon:   // 多边形
            painter.drawPolygon(points, 4);
            break;
        case Polyline:  // 多边线
            painter.drawPolyline(points, 4);
            break;
        case Points:    // 点
            painter.drawPoints(points, 4);
            break;
        case Arc:   // 弧
            painter.drawArc(rect(), startAngle, spanAngle);
            break;
        case Path:  // 路径
            painter.drawPath(painterPath);
            break;
        case Text:  // 文字
            painter.drawText(rect(), Qt::AlignCenter, tr("Hello Qt!"));
            break;
        case Pixmap:    // 图片
            painter.drawPixmap(150, 150, QPixmap("butterfly.png"));
            break;
        default:
            break;
    }
}
