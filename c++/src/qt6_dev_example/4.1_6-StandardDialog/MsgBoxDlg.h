//
// Created by leever on 9/28/2022.
//

#ifndef QT6_DEV_EXAMPLE_MSGBOXDLG_H
#define QT6_DEV_EXAMPLE_MSGBOXDLG_H

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>

class MsgBoxDlg: public QDialog{
    Q_OBJECT
public:
    explicit MsgBoxDlg(QWidget *parent = nullptr);
    ~MsgBoxDlg() override;
private slots:
    void showQuestionMsg();
    void showInformationMsg();
    void showWarningMsg();
    void showCriticalMsg();
    void showAboutMsg();
    void showAboutQtMsg();
private:
    QLabel *label;
    QPushButton *questionBtn;
    QPushButton *informationBtn;
    QPushButton *warningBtn;
    QPushButton *criticalBtn;
    QPushButton *aboutBtn;
    QPushButton *aboutQtBtn;
    QGridLayout *mainLayout;
};


#endif //QT6_DEV_EXAMPLE_MSGBOXDLG_H
