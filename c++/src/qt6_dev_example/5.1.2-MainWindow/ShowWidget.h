//
// Created by leever on 9/30/2022.
//

#ifndef QT6_DEV_EXAMPLE_SHOWWIDGET_H
#define QT6_DEV_EXAMPLE_SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QImage>

class ShowWidget: public QWidget {
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = nullptr);
    QImage image;
    QLabel *imageLabel;
    QTextEdit *textEdit;
signals:
public slots:
};


#endif //QT6_DEV_EXAMPLE_SHOWWIDGET_H
