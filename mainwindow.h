#pragma once

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSpinBox>
#include <QLineEdit>
#include <QProgressBar>
#include <QTimer>
#include <QStringList>
#include "QComboBox"
#include "QtSerialPort/QSerialPortInfo"
#include "QCheckBox"
#include "filedatamanager.h"
#include "tcpmanager.h"
#include "struct.h"
#include "serialmanager.h"


// struct dataStruct {
//     double h1;
//     double h2;
//     double h3;
//     double h4;
//     double h5;
//     QVector<double>dataVector;
// };

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    // void startReading(QString &filePath);
    //  void readNextLine();
    void updateSpinBox(QVector<int> values,int progress);
    void updateSpinBoxTcp(const dataStruct &data);
    void updateSpinBoxSerial(QStringList &data);
    // void readClientData();
    // void clientConnection();
    void listenToServer();
    void loadProts();
    void openPort();
    // void readSerialData();
    void chooseConnection();
    void checboxes();


private:

    QSpinBox *mySpinBox1;
    QSpinBox *mySpinBox2;
    QSpinBox *mySpinBox3;
    QSpinBox *mySpinBox4;
    QSpinBox *mySpinBox5;

    QLineEdit *ipLineEdit ;
    QLineEdit *portLineEdit;
    QProgressBar *myProgress;
    QComboBox *serialComboBox;
    QComboBox *baudRateComboBox;
    QTimer *myTimer = nullptr;
    QCheckBox *tcpCheckBox;
    QCheckBox *serialChekBox;
    QWidget *serialWidget;
    QWidget *ipportWidget;

    QStringList stringLines;

    QTcpServer *myServer = nullptr;
    QTcpSocket *socket = nullptr;

    int currentLineIndex = 0;

    QSerialPort *serialPortTest;
    fileDataManager *dataManagerClass;
    tcpmanager *tcpClass;
    serialmanager *serialClass;


};
