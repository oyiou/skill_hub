//
// Created by leever on 9/28/2022.
//

#include "ProcessDialog.h"
#include <QProgressDialog>
#include <QFont>

ProcessDialog::ProcessDialog(QWidget *parent) : QDialog(parent) {
    QFont font("ZYSong18030", 12);
    setFont(font);
    setWindowTitle(tr("Process"));

    fileNum = new QLabel;
    fileNum->setText(tr("文件数目："));
    fileNumLineEdit = new QLineEdit;
    fileNumLineEdit->setText(tr("100000"));

    progressType = new QLabel;
    progressType->setText(tr("显示类型："));
    comboBox = new QComboBox;
    comboBox->addItem(tr("progressBar"));
    comboBox->addItem(tr("progressDialog"));

    progressBar = new QProgressBar;

    starBtn = new QPushButton();
    starBtn->setText(tr("开始"));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(fileNum, 0, 0);
    mainLayout->addWidget(fileNumLineEdit, 0, 1);
    mainLayout->addWidget(progressType, 1, 0);
    mainLayout->addWidget(comboBox, 1, 1);
    mainLayout->addWidget(progressBar, 2, 0, 1, 2);
    mainLayout->addWidget(starBtn, 3, 1);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);

    connect(starBtn, SIGNAL(clicked()), this, SLOT(startProgress()));
}

ProcessDialog::~ProcessDialog() = default;

void ProcessDialog::startProgress() {
    bool ok;
    int num = fileNumLineEdit->text().toInt(&ok);
    if (comboBox->currentIndex() == 0) {
        progressBar->setRange(0, num);
        for (int i = 0; i < num+1; i++) {
            progressBar->setValue(i);
        }
    } else if (comboBox->currentIndex() == 1) {
        auto *progressDialog = new QProgressDialog(this);
        QFont font("ZYSong18030", 12);
        progressDialog->setFont(font);
        progressDialog->setWindowModality(Qt::WindowModal);
        progressDialog->setMinimumDuration(5);
        progressDialog->setWindowTitle(tr("Please Wait"));
        progressDialog->setLabelText(tr("Copying..."));
        progressDialog->setCancelButtonText(tr("Cancel"));
        progressDialog->setRange(0, num);
        for (int i = 0; i < num+1; i++) {
            progressDialog->setValue(i);
            if (progressDialog->wasCanceled())
                return;
        }
    }
}
