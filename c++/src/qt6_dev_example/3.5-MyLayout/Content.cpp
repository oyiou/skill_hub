//
// Created by leever on 9/27/2022.
//

#include "Content.h"

Content::Content(QWidget *parent): QFrame(parent) {
    stacked = new QStackedWidget(this);
    stacked->setFrameStyle(QFrame::Panel | QFrame::Raised);
    baseInfo = new BaseInfo();
    contact = new Contact();
    detail = new Detail();
    stacked->addWidget(baseInfo);
    stacked->addWidget(contact);
    stacked->addWidget(detail);

    AmendBtn = new QPushButton(tr("修改"));
    CloseBtn = new QPushButton(tr("关闭"));
    auto *BtnLayout = new QHBoxLayout;
    BtnLayout->addStretch(1);
    BtnLayout->addWidget(AmendBtn);
    BtnLayout->addWidget(CloseBtn);

    auto *RightLayout = new QVBoxLayout(this);
    RightLayout->setContentsMargins(10, 10, 10, 10);
    RightLayout->setSpacing(6);
    RightLayout->addWidget(stacked);
    RightLayout->addLayout(BtnLayout);
}
