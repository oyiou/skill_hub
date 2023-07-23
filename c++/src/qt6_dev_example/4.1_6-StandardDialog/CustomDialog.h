//
// Created by leever on 9/28/2022.
//

#ifndef QT6_DEV_EXAMPLE_CUSTOMDIALOG_H
#define QT6_DEV_EXAMPLE_CUSTOMDIALOG_H

#include <QDialog>

class CustomDialog: public QDialog {
    Q_OBJECT
public:
    explicit CustomDialog(QWidget *parent = nullptr);
    ~CustomDialog() override;
signals:
public slots:
};


#endif //QT6_DEV_EXAMPLE_CUSTOMDIALOG_H
