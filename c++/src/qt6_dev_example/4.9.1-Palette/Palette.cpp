//
// Created by leever on 9/29/2022.
//

#include "Palette.h"
#include <QHBoxLayout>
#include <QGridLayout>

Palette::Palette(QWidget *parent) : QDialog(parent) {
    createCtrlFrame();
    createContentFrame();
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(ctrlFrame);
    mainLayout->addWidget(contentFrame);
}

void Palette::createCtrlFrame() {
    ctrlFrame = new QFrame;
    windowLabel = new QLabel(tr("QPalette::Window: "));
    windowComboBox = new QComboBox;
    fillColorList(windowComboBox);
    connect(windowComboBox, SIGNAL(activated(int)), this, SLOT(showWindow()));

    windowTextLabel = new QLabel(tr("QPalette::WindowText: "));
    windowTextComboBox = new QComboBox;
    fillColorList(windowTextComboBox);
    connect(windowTextComboBox, SIGNAL(activated(int)), this, SLOT(showWindowText()));

    buttonLabel = new QLabel(tr("QPalette::Button: "));
    buttonComboBox = new QComboBox;
    fillColorList(buttonComboBox);
    connect(buttonComboBox, SIGNAL(activated(int)), this, SLOT(showButton()));

    buttonTextLabel = new QLabel(tr("QPalette::ButtonText: "));
    buttonTextComboBox = new QComboBox;
    fillColorList(buttonTextComboBox);
    connect(buttonTextComboBox, SIGNAL(activated(int)), this, SLOT(showButtonText()));

    baseLabel = new QLabel(tr("QPalette::Base: "));
    baseComboBox = new QComboBox;
    fillColorList(baseComboBox);
    connect(baseComboBox, SIGNAL(activated(int)), this, SLOT(showBase()));

    auto *mainLayout = new QGridLayout(ctrlFrame);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(windowLabel, 0, 0);
    mainLayout->addWidget(windowComboBox, 0, 1);
    mainLayout->addWidget(windowTextLabel, 1, 0);
    mainLayout->addWidget(windowTextComboBox, 1, 1);
    mainLayout->addWidget(buttonLabel, 2, 0);
    mainLayout->addWidget(buttonComboBox, 2, 1);
    mainLayout->addWidget(buttonTextLabel, 3, 0);
    mainLayout->addWidget(buttonTextComboBox, 3, 1);
    mainLayout->addWidget(baseLabel, 4, 0);
    mainLayout->addWidget(baseComboBox, 4, 1);
}

void Palette::createContentFrame() {
    contentFrame = new QFrame;
    label1 = new QLabel(tr("请选择一个值："));
    comboBox1 = new QComboBox;

    label2 = new QLabel(tr("请输入字符串："));
    lineEdit2 = new QLineEdit;

    textEdit = new QTextEdit;

    auto *topLayout = new QGridLayout;
    topLayout->addWidget(label1, 0, 0);
    topLayout->addWidget(comboBox1, 0, 1);
    topLayout->addWidget(label2, 1, 0);
    topLayout->addWidget(lineEdit2, 1, 1);
    topLayout->addWidget(textEdit, 2, 0, 1, 2);

    okBtn = new QPushButton(tr("确认"));
    cancelBtn = new QPushButton(tr("取消"));

    auto *buttomLayout = new QHBoxLayout;
    buttomLayout->addStretch(1);
    buttomLayout->addWidget(okBtn);
    buttomLayout->addWidget(cancelBtn);

    auto *mainLayout = new QVBoxLayout(contentFrame);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(buttomLayout);
}

void Palette::fillColorList(QComboBox *comboBox) {
    QStringList colorList = QColor::colorNames();
    QString color;
    foreach(color, colorList) {
        QPixmap pixmap(QSize(70, 20));
        pixmap.fill(QColor(color));
        comboBox->addItem(QIcon(pixmap), nullptr);
        comboBox->setIconSize(QSize(70, 20));
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

void Palette::showWindow() {
    QStringList colorList = QColor::colorNames();
    auto color = QColor(colorList[windowComboBox->currentIndex()]);

    QPalette palette = contentFrame->palette();
    palette.setColor(QPalette::Window, color);
    contentFrame->setPalette(palette);
    contentFrame->update();
}

void Palette::showWindowText() {
    QStringList colorList = QColor::colorNames();
    QColor color = colorList[windowTextComboBox->currentIndex()];

    QPalette palette = contentFrame->palette();
    palette.setColor(QPalette::WindowText, color);
    contentFrame->setPalette(palette);
}

void Palette::showButton() {
    QStringList colorList = QColor::colorNames();
    auto color = QColor(colorList[buttonComboBox->currentIndex()]);

    QPalette palette = contentFrame->palette();
    palette.setColor(QPalette::Button, color);
    contentFrame->setPalette(palette);
    contentFrame->update();
}

void Palette::showButtonText() {
    QStringList  colorList = QColor::colorNames();
    auto color = QColor(colorList[buttonTextComboBox->currentIndex()]);

    QPalette palette = contentFrame->palette();
    palette.setColor(QPalette::ButtonText, color);
    contentFrame->setPalette(palette);
}

void Palette::showBase() {
    QStringList colorList = QColor::colorNames();
    auto color = QColor(colorList[baseComboBox->currentIndex()]);

    QPalette palette = contentFrame->palette();
    palette.setColor(QPalette::Base, color);
    contentFrame->setPalette(palette);
}

Palette::~Palette() = default;
