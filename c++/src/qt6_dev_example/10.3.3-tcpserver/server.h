//
// Created by leever on 2023/6/2.
//

#ifndef C_SERVER_H
#define C_SERVER_H

#include <QTcpServer>
#include <QObject>

#include "tcpclientsocket.h"

class Server: public QTcpServer {
    Q_OBJECT
public:
    Server(QObject *parent = nullptr, int port = 0);
    QList<TcpClientSocket*> tcpClientSocketList;
signals:
    void updateServer(QString, int);
public slots:
    void updateClients(QString, int);
    void slotDisconnected(int);
protected:
    void incomingConnection(int socketDescriptor);
};

#endif //C_SERVER_H
