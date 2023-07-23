//
// Created by leever on 9/28/2022.
//

#include "Drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>

Drawer::Drawer(QWidget *parent, Qt::WindowFlags f) : QToolBox(parent, f) {
    setWindowTitle(tr("TM QQ"));

    toolBtn1_1 = new QToolButton;
    toolBtn1_1->setText(tr("张三"));
    toolBtn1_1->setIcon(QPixmap("11.png"));
    toolBtn1_1->setIconSize(QPixmap("11.png").size());
    toolBtn1_1->setAutoRaise(true);
    toolBtn1_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_2 = new QToolButton;
    toolBtn1_2->setText(tr("李四"));
    toolBtn1_2->setIcon(QPixmap("12.png"));
    toolBtn1_2->setIconSize(QPixmap("12.png").size());
    toolBtn1_2->setAutoRaise(true);
    toolBtn1_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_3 = new QToolButton;
    toolBtn1_3->setText(tr("王五"));
    toolBtn1_3->setIcon(QPixmap("13.png"));
    toolBtn1_3->setIconSize(QPixmap("13.png").size());
    toolBtn1_3->setAutoRaise(true);
    toolBtn1_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_4 = new QToolButton;
    toolBtn1_4->setText(tr("赵六"));
    toolBtn1_4->setIcon(QPixmap("14.png"));
    toolBtn1_4->setIconSize(QPixmap("14.png").size());
    toolBtn1_4->setAutoRaise(true);
    toolBtn1_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_5 = new QToolButton;
    toolBtn1_5->setText(tr("周七"));
    toolBtn1_5->setIcon(QPixmap("15.png"));
    toolBtn1_5->setIconSize(QPixmap("15.png").size());
    toolBtn1_5->setAutoRaise(true);
    toolBtn1_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    auto *groupBox1 = new QGroupBox;
    auto *layout1 = new QVBoxLayout(groupBox1);
    layout1->setContentsMargins(10, 10, 10, 10);
    layout1->setAlignment(Qt::AlignHCenter);
    layout1->addWidget(toolBtn1_1);
    layout1->addWidget(toolBtn1_2);
    layout1->addWidget(toolBtn1_3);
    layout1->addWidget(toolBtn1_4);
    layout1->addWidget(toolBtn1_5);
    layout1->addStretch();

    toolBtn2_1 = new QToolButton;
    toolBtn2_1->setText(tr("小王"));
    toolBtn2_1->setIcon(QPixmap("21.png"));
    toolBtn2_1->setIconSize(QPixmap("21.png").size());
    toolBtn2_1->setAutoRaise(true);
    toolBtn2_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn2_2 = new QToolButton;
    toolBtn2_2->setText(tr("小张"));
    toolBtn2_2->setIcon(QPixmap("22.png"));
    toolBtn2_2->setIconSize(QPixmap("22.png").size());
    toolBtn2_2->setAutoRaise(true);
    toolBtn2_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    auto *groupBox2 = new QGroupBox;
    auto *layout2 = new QVBoxLayout(groupBox2);
    layout2->setContentsMargins(10, 10, 10, 10);
    layout2->setAlignment(Qt::AlignHCenter);
    layout2->addWidget(toolBtn2_1);
    layout2->addWidget(toolBtn2_2);

    toolBtn3_1 = new QToolButton;
    toolBtn3_1->setText(tr("小陈"));
    toolBtn3_1->setIcon(QPixmap("21.png"));
    toolBtn3_1->setIconSize(QPixmap("21.png").size());
    toolBtn3_1->setAutoRaise(true);
    toolBtn3_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn3_2 = new QToolButton;
    toolBtn3_2->setText(tr("小李"));
    toolBtn3_2->setIcon(QPixmap("32.png"));
    toolBtn3_2->setIconSize(QPixmap("32.png").size());
    toolBtn3_2->setAutoRaise(true);
    toolBtn3_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    auto *groupBox3 = new QGroupBox;
    auto *layout3 = new QVBoxLayout(groupBox3);
    layout3->setContentsMargins(10, 10, 10, 10);
    layout3->setAlignment(Qt::AlignHCenter);
    layout3->addWidget(toolBtn3_1);
    layout3->addWidget(toolBtn3_2);

    this->addItem((QWidget*)groupBox1, tr("好朋友"));
    this->addItem((QWidget*)groupBox2, tr("陌生人"));
    this->addItem((QWidget*)groupBox3, tr("黑名单"));
}
