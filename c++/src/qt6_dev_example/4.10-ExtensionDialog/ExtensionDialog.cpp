//
// Created by leever on 9/29/2022.
//

#include "ExtensionDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QHBoxLayout>

ExtensionDialog::ExtensionDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("Extension Dialog"));

    createBaseInfo();
    createDetailInfo();

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(baseWidget);
    layout->addWidget(detailWidget);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(10);
}

void ExtensionDialog::createBaseInfo() {
    baseWidget = new QWidget;

    auto *nameLabel = new QLabel(tr("姓名："));
    auto *nameLineEdit = new QLineEdit;

    auto *sexLabel = new QLabel(tr("性别："));
    auto *sexComboBox = new QComboBox;
    sexComboBox->insertItem(0, tr("女"));
    sexComboBox->insertItem(1, tr("男"));

    auto *leftLayout = new QGridLayout;
    leftLayout->addWidget(nameLabel, 0, 0);
    leftLayout->addWidget(nameLineEdit, 0, 1);
    leftLayout->addWidget(sexLabel);
    leftLayout->addWidget(sexComboBox);

    auto *okBtn = new QPushButton(tr("确定"));
    auto *detailBtn = new QPushButton(tr("详细"));
    auto *btnBox = new QDialogButtonBox(Qt::Vertical);
    btnBox->addButton(okBtn, QDialogButtonBox::ActionRole);
    btnBox->addButton(detailBtn, QDialogButtonBox::ActionRole);

    auto *mainLayout = new QHBoxLayout(baseWidget);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(btnBox);
    connect(detailBtn, SIGNAL(clicked()), this, SLOT(showDetailInfo()));
}

void ExtensionDialog::createDetailInfo() {
    detailWidget = new QWidget;

    auto *ageLabel = new QLabel(tr("年龄："));
    auto *ageLineEdit = new QLineEdit;
    ageLineEdit->setText(tr("30"));

    auto *departmentLabel = new QLabel(tr("部门："));
    auto *departmentComboBox = new QComboBox;
    departmentComboBox->addItem(tr("部门 1"));
    departmentComboBox->addItem(tr("部门 2"));
    departmentComboBox->addItem(tr("部门 3"));
    departmentComboBox->addItem(tr("部门 4"));

    auto *emailLabel = new QLabel(tr("email:"));
    auto *emailLineEdit = new QLineEdit;

    auto *mainLayout = new QGridLayout(detailWidget);
    mainLayout->addWidget(ageLabel, 0, 0);
    mainLayout->addWidget(ageLineEdit, 0, 1);
    mainLayout->addWidget(departmentLabel, 1, 0);
    mainLayout->addWidget(departmentComboBox, 1, 1);
    mainLayout->addWidget(emailLabel, 2, 0);
    mainLayout->addWidget(emailLineEdit, 2, 1);

    detailWidget->hide();
}

void ExtensionDialog::showDetailInfo() {
    if (detailWidget->isHidden())
        detailWidget->show();
    else
        detailWidget->hide();
}

ExtensionDialog::~ExtensionDialog() = default;
