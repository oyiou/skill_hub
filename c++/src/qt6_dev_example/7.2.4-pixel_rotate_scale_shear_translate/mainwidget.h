//
// Created by leever on 2023/5/30.
//

#ifndef C_MAINWIDGET_H
#define C_MAINWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFrame>

#include "pixitem.h"

class MainWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;
    void createControlFrame();
private:
    int angle;
    int scaleValue;
    int shearValue;
    int translateValue;

    QGraphicsView *view;
    QFrame *ctrlFrame;
private:
    PixItem *pixItem;
public slots:
    void slotRotate(int);
    void slotScale(int);
    void slotShear(int);
    void slotTranslate(int);
};

#endif //C_MAINWIDGET_H
