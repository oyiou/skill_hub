//
// Created by leever on 9/27/2022.
//

#include <QHBoxLayout>
#include "Stacked.h"

Stacked::Stacked(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("Stacked"));
    list = new QListWidget(this);
    list->insertItem(0, tr("Window1"));
    list->insertItem(1, tr("Window2"));
    list->insertItem(2, tr("Window3"));
    label1 = new QLabel(tr("WindowTest1"));
    label2 = new QLabel(tr("WindowTest2"));
    label3 = new QLabel(tr("WindowTest3"));
    stack = new QStackedWidget(this);
    stack->addWidget(label1);
    stack->addWidget(label2);
    stack->addWidget(label3);
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);
    mainLayout->addWidget(list);
    mainLayout->addWidget(stack, 0, Qt::AlignHCenter);
    mainLayout->setStretchFactor(list, 1);
    mainLayout->setStretchFactor(stack, 3);
    connect(list, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));
}

Stacked::~Stacked() = default;
