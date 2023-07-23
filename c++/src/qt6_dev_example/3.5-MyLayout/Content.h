//
// Created by leever on 9/27/2022.
//

#ifndef QT6_DEV_EXAMPLE_CONTENT_H
#define QT6_DEV_EXAMPLE_CONTENT_H

#include "BaseInfo.h"
#include "Contact.h"
#include "Detail.h"
#include <QStackedWidget>
#include <QPushButton>

class Content: public QFrame{
    Q_OBJECT
public:
    explicit Content(QWidget *parent = nullptr);
    QStackedWidget *stacked;
    QPushButton *AmendBtn;
    QPushButton *CloseBtn;

    BaseInfo *baseInfo;
    Contact *contact;
    Detail *detail;
};


#endif //QT6_DEV_EXAMPLE_CONTENT_H
