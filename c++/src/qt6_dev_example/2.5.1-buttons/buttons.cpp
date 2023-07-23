//
// Created by leever on 9/26/2022.
//

#include "buttons.h"
#include <QApplication>
#include <QPushButton>
#include <QFont>

Buttons::Buttons(QWidget *parent): QWidget(parent) {
    setMinimumSize(200, 120);
    setMaximumSize(200, 120);
    auto *quit = new QPushButton("Quit", this);
    quit->setGeometry(62, 40, 75, 30);
    quit->setFont(QFont("Times", 18, QFont::Bold));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

Buttons::~Buttons() = default;
