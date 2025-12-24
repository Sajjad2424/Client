#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H
#include "QSerialPort"
#include <QObject>


class serialmanager:public QObject

{ Q_OBJECT

public:
   // serialmanager();
    explicit serialmanager(QWidget *parent = nullptr);

    void openPort(const QString &portName, const QString &baudRate);
    void readSerialData();

signals:
    void *serialSignal(QStringList &list);

private:
    QWidget *_parent;
    QSerialPort *_SerialPort;
};

#endif // SERIALMANAGER_H
