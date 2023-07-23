//
// Created by leever on 2023/6/2.
//

#ifndef C_TCPCLIENT_H
#define C_TCPCLIENT_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include <QHostAddress>
#include <QTcpSocket>

class TcpClient: public QDialog {
    Q_OBJECT
public:
    TcpClient(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~TcpClient();
private:
    QListWidget *contentListWidget;
    QLineEdit *sendLineEdit;
    QPushButton *sendBtn;

    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *serverIpLabel;
    QLineEdit *serverIpLineEdit;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QPushButton *enterBtn;
    QGridLayout *mainLayout;
private:
    bool status;
    int port;
    QHostAddress *serverIp;
    QString userName;
    QTcpSocket *tcpSocket;
public slots:
    void slotEnter();
    void slotConnected();
    void slotDisconnected();
    void dataReceived();
    void slotSend();
};

#endif //C_TCPCLIENT_H
