//
// Created by leever on 9/29/2022.
//

#ifndef QT6_DEV_EXAMPLE_DIGITCLOCK_H
#define QT6_DEV_EXAMPLE_DIGITCLOCK_H

#include <QTime>
#include <QTimer>
#include <QMouseEvent>
#include <QLCDNumber>

class DigitClock : public QLCDNumber {
    Q_OBJECT
public:
    explicit DigitClock(QWidget *parent = nullptr);
    ~DigitClock() override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
public slots:
    void showTime();
private:
    QPoint dragPosition;    //  保存鼠标相对电子时钟窗体左上角的偏移值
    bool showColon; // 用于像是时间时是否显示 :
};


#endif //QT6_DEV_EXAMPLE_DIGITCLOCK_H
