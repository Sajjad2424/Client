#include "serialmanager.h"
#include "QSerialPort"
#include "QMessageBox"

serialmanager::serialmanager(QWidget *parent): QObject(parent)
{
    _parent= parent;
    _SerialPort = new QSerialPort();
}


void serialmanager::openPort(const QString &portName, const QString &baudRate)
{


    if (_SerialPort !=nullptr )
    {
        _SerialPort->close();
      delete _SerialPort;
    }

    _SerialPort = new QSerialPort();
    _SerialPort->setPortName(portName);
    _SerialPort->setBaudRate(baudRate.toInt());
    _SerialPort->setParity(QSerialPort::NoParity);
    _SerialPort->setDataBits(QSerialPort::Data8);
    if(_SerialPort->open(QIODevice::ReadWrite))
    {
        QMessageBox::information(_parent,"Result","Port is open");
        connect(_SerialPort ,&QSerialPort::readyRead ,this ,&serialmanager::readSerialData);

    }
    else
    {
        QMessageBox::critical(_parent,"Warining","Port Can't be open");
    }
}

void serialmanager::readSerialData()
{    
    QByteArray data = _SerialPort->readAll();
    QStringList parts = QString(data).split(',');

    if (parts.size() < 5) return;
    _SerialPort->write("Ok");

    emit serialSignal(parts);
}
