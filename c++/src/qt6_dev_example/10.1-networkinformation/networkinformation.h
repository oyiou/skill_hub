//
// Created by leever on 2023/6/2.
//

#ifndef C_NETWORKINFORMATION_H
#define C_NETWORKINFORMATION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>

#include <QHostInfo>
#include <QNetworkInterface>

class NetworkInformation: public QWidget {
    Q_OBJECT
public:
    NetworkInformation(QWidget *parent = nullptr);
    ~NetworkInformation();
private:
    QLabel *hostLabel;
    QLineEdit *LineEditLocalHostName;
    QLabel *ipLabel;
    QLineEdit *LineEditAddress;

    QPushButton *detailBtn;

    QGridLayout *mainLayout;
public:
    void getHostInformation();
public slots:
    void slotDetail();
};

#endif //C_NETWORKINFORMATION_H
