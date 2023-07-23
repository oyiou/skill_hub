//
// Created by leever on 9/28/2022.
//

#ifndef QT6_DEV_EXAMPLE_DRAWER_H
#define QT6_DEV_EXAMPLE_DRAWER_H

#include <QToolBox>
#include <QToolButton>

class Drawer : public QToolBox {
    Q_OBJECT
public:
    explicit Drawer(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Widget);
private:
    QToolButton *toolBtn1_1;
    QToolButton *toolBtn1_2;
    QToolButton *toolBtn1_3;
    QToolButton *toolBtn1_4;
    QToolButton *toolBtn1_5;
    QToolButton *toolBtn2_1;
    QToolButton *toolBtn2_2;
    QToolButton *toolBtn3_1;
    QToolButton *toolBtn3_2;
};


#endif //QT6_DEV_EXAMPLE_DRAWER_H
