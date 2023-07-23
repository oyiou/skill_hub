//
// Created by leever on 2023/5/30.
//
#include "pixitem.h"

PixItem::PixItem(QPixmap *pixmap) {
    pix = *pixmap;
}

QRectF PixItem::boundingRect() const {
    return QRectF(-2-pix.width()/2.0, -2-pix.height()/2.0, pix.width()+4, pix.height()+4);
}

void PixItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-pix.width()/2, -pix.height()/2, pix);
}