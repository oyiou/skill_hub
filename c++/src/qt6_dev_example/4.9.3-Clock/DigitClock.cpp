//
// Created by leever on 9/29/2022.
//

#include "DigitClock.h"
#include <QPalette>

DigitClock::DigitClock(QWidget *parent) : QLCDNumber(parent) {
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, Qt::blue);
    setPalette(palette);

    setWindowFlags(Qt::FramelessWindowHint);

    setWindowOpacity(0.5);

    auto *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    showTime();
    resize(150, 60);
    showColon = true;
}

void DigitClock::showTime() {
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if (showColon) {
        text[2] = ':';
        showColon = false;
    } else {
        text[2] = ' ';
        showColon = true;
    }
    display(text);
}

void DigitClock::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
    if (event->button() == Qt::RightButton) {
        close();
    }
}

void DigitClock::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

DigitClock::~DigitClock() = default;
