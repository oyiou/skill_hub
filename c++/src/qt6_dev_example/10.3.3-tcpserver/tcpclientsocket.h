//
// Created by leever on 2023/6/2.
//

#ifndef C_TCPCLIENTSOCKET_H
#define C_TCPCLIENTSOCKET_H

#include <QTcpServer>
#include <QObject>

class TcpClientSocket: public QTcpServer {
    Q_OBJECT
public:
    TcpClientSocket(QObject *parent = 0);
signals:
    void updateClients(QString, int);
    void disconnected(int);
protected slots:
    void dataReceived();
    void slotDisconnected();
};

#endif //C_TCPCLIENTSOCKET_H
