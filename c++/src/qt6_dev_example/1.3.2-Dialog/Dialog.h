//
// Created by leever on 9/22/2022.
//

#ifndef QT6_DEV_EXAMPLE_DIALOG_H
#define QT6_DEV_EXAMPLE_DIALOG_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

const static double PI = 3.14;

class Dialog: public QDialog {
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;
private:
    QLabel *label1,*label2;
    QLineEdit *lineEdit;
    QPushButton *button;
private slots:
    void showArea();
};


#endif //QT6_DEV_EXAMPLE_DIALOG_H
