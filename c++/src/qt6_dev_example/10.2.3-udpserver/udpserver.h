//
// Created by leever on 2023/6/2.
//

#ifndef C_UDPSERVER_H
#define C_UDPSERVER_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <QUdpSocket>
#include <QTimer>

class UdpServer: public QDialog {
    Q_OBJECT
public:
    UdpServer(QWidget *parent = nullptr, Qt::WindowFlags f = static_cast<QFlag>(0));
    ~UdpServer();
private:
    QLabel *TimerLabel;
    QLineEdit *TextLineEdit;
    QPushButton *StartBtn;
    QVBoxLayout *mainLayout;
public slots:
    void StartBtnClicked();
    void timeout();
private:
    int port;
    bool isStarted;
    QUdpSocket *udpSocket;
    QTimer *timer;
};

#endif //C_UDPSERVER_H
