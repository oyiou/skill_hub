//
// Created by leever on 9/30/2022.
//

#include "ShowWidget.h"
#include <QHBoxLayout>

ShowWidget::ShowWidget(QWidget *parent): QWidget(parent) {
    imageLabel = new QLabel;
    imageLabel->setScaledContents(true);

    textEdit = new QTextEdit;

    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(textEdit);
}
