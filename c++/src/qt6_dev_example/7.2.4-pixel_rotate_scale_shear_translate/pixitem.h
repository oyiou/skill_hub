//
// Created by leever on 2023/5/30.
//

#ifndef C_PIXITEM_H
#define C_PIXITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class PixItem : public QGraphicsItem {
public:
    explicit PixItem(QPixmap *pixmap);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap pix;    // 作为图元显示的图片
};

#endif //C_PIXITEM_H
