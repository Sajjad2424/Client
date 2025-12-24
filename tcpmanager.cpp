#include "tcpmanager.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QMessageBox>

tcpmanager::tcpmanager(QWidget *parent) : QObject(parent)
{
    _parent= parent;
}


void tcpmanager::listenToServer(const QString &ip, quint16 port)
{
    QString ipAddress = ip;
    QHostAddress host(ipAddress);

    if (myServer) {
        myServer->close();
        myServer->deleteLater();
        myServer = nullptr;
    }

    myServer = new QTcpServer(this);
    if (!myServer->listen(QHostAddress(host), port))
    {
        QMessageBox::warning(_parent,"Status","Can't listen to server");
        return;
    }
    connect(myServer, &QTcpServer::newConnection, this, &tcpmanager::clientConnection);
    QMessageBox::information(_parent, "Status", "Server is listening");
}


void tcpmanager::clientConnection()
{
    if (socket)
    {
        socket->disconnectFromHost();
        socket->deleteLater(); }
    socket = myServer->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &tcpmanager::readClientData);

    QByteArray ackReply("Connect");
    socket->write(ackReply);
    socket->flush();
    qDebug() << "Connected ..";
}

void tcpmanager::readClientData()
{
    QDataStream in(socket);
    dataStruct receivedData;
    in >> receivedData;

    QByteArray ackReply("Ok");
    socket->write(ackReply);
    socket->flush();

    emit tcpSignal(receivedData);

}
