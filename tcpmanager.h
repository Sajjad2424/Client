#ifndef TCPMANAGER_H
#define TCPMANAGER_H
#include "QString"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "struct.h"


class tcpmanager :public QObject
{ Q_OBJECT


public:
    explicit tcpmanager(QWidget *parent = nullptr);


signals:
    void spinBoxSignal(const dataStruct &dataSt);

public slots:
    void listenToServer(const QString &ip, quint16 port);
    void clientConnection();
    void readClientData();



private:
    QTcpServer *myServer = nullptr;
    QTcpSocket *socket = nullptr;
    QWidget *_parent;
};



#endif // TCPMANAGER_H
