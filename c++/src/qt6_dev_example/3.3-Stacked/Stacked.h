//
// Created by leever on 9/27/2022.
//

#ifndef QT6_DEV_EXAMPLE_STACKED_H
#define QT6_DEV_EXAMPLE_STACKED_H

#include <QStackedWidget>
#include <QListWidget>
#include <QLabel>
#include <QDialog>

class Stacked: public QDialog {
    Q_OBJECT
public:
    Stacked(QWidget *parent = nullptr);
    ~Stacked() override;
private:
    QListWidget *list;
    QStackedWidget *stack;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
};


#endif //QT6_DEV_EXAMPLE_STACKED_H
