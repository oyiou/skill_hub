//
// Created by leever on 9/27/2022.
//

#ifndef QT6_DEV_EXAMPLE_CONTACT_H
#define QT6_DEV_EXAMPLE_CONTACT_H

#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>

class Contact: public QWidget {
    Q_OBJECT
public:
    explicit Contact(QWidget *parent = nullptr);
private:
    QLabel *EmailLabel;
    QLineEdit *EmailLineEdit;
    QLabel *AddrLabel;
    QLineEdit *AddrLineEdit;
    QLabel *CodeLabel;
    QLineEdit *CodeLineEdit;
    QLabel *MoveTelLabel;
    QLineEdit *MoveTelLineEdit;
    QCheckBox *MoveTelCheckBox;
    QLabel *ProTelLabel;
    QLineEdit *ProTelLineEdit;
    QGridLayout *mainLayout;
};


#endif //QT6_DEV_EXAMPLE_CONTACT_H
