//
// Created by leever on 9/29/2022.
//

#ifndef QT6_DEV_EXAMPLE_EXTENSIONDIALOG_H
#define QT6_DEV_EXAMPLE_EXTENSIONDIALOG_H

#include <QDialog>

class ExtensionDialog : public QDialog {
    Q_OBJECT
public:
    explicit ExtensionDialog(QWidget *parent = nullptr);
    ~ExtensionDialog() override;
private slots:
    void showDetailInfo();
private:
    void createBaseInfo();
    void createDetailInfo();
    QWidget *baseWidget;
    QWidget *detailWidget;
};


#endif //QT6_DEV_EXAMPLE_EXTENSIONDIALOG_H
