//
// Created by leever on 9/28/2022.
//

#ifndef QT6_DEV_EXAMPLE_DIALOG_H
#define QT6_DEV_EXAMPLE_DIALOG_H

#include "InputDialog.h"
#include "MsgBoxDlg.h"
#include "CustomDialog.h"
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFrame>

class Dialog: public QDialog {
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;
private:
    QPushButton *fileBtn;
    QLineEdit *fileLineEdit;
    QGridLayout *mainLayout;

    QPushButton *colorBtn;
    QFrame * colorFrame;

    QPushButton *fontBtn;
    QLineEdit *fontLineEdit;

    QPushButton *inputBtn;
    InputDialog *inputDialog;

    QPushButton *msgBtn;
    MsgBoxDlg *msgDlg;

    QPushButton *customBtn;
    QLabel *customLabel;
private slots:
    void showFile();
    void showColor();
    void showFont();
    void showInputDialog();
    void showMsgDlg();
    void showCustomDialog();
};


#endif //QT6_DEV_EXAMPLE_DIALOG_H
