//
// Created by leever on 9/28/2022.
//

#ifndef QT6_DEV_EXAMPLE_INPUTDIALOG_H
#define QT6_DEV_EXAMPLE_INPUTDIALOG_H

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>

class InputDialog: public QDialog {
    Q_OBJECT
public:
    explicit InputDialog(QWidget *parent = nullptr);
private slots:
    void ChangeName();
    void ChangeSex();
    void ChangeAge();
    void ChangeScore();
private:
    QLabel *nameLabel1;
    QLabel *sexLabel1;
    QLabel *ageLabel1;
    QLabel * scoreLabel1;
    QLabel *nameLabel2;
    QLabel *sexLabel2;
    QLabel *ageLabel2;
    QLabel * scoreLabel2;
    QPushButton *nameBtn;
    QPushButton *sexBtn;
    QPushButton *ageBtn;
    QPushButton *scoreBtn;
    QGridLayout *mainLayout;
};


#endif //QT6_DEV_EXAMPLE_INPUTDIALOG_H
