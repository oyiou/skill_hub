//
// Created by leever on 2023/6/2.
//

#ifndef C_UDPCLIENT_H
#define C_UDPCLIENT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

#include <QUdpSocket>

class UdpClient: public QDialog {
    Q_OBJECT
public:
    UdpClient(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~UdpClient();
private:
    QTextEdit *ReceiveTextEdit;
    QPushButton *CloseBtn;
    QVBoxLayout *mainLayout;
public slots:
    void CloseBtnClicked();
    void dataReceived();
private:
    int port;
    QUdpSocket *udpSocket;
};

#endif //C_UDPCLIENT_H
