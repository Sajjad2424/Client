#include "mainwindow.h"
#include "filedatamanager.h"

#include <QFileDialog>
#include <QFile>
#include <QAction>
#include <QToolBar>
#include <QFormLayout>
#include <QWidget>
#include <QGridLayout>
#include <QString>
#include <QFileDevice>
#include <QDebug>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QProgressBar>
#include <QDataStream>
#include "QSerialPort"
#include "QPushButton"
#include "QGroupBox"
#include "QButtonGroup"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    QGridLayout *mainGridLayout = new QGridLayout();
    QWidget *mainWidget = new QWidget();

    QIntValidator *portValidator = new QIntValidator();
    portValidator->setRange(1,65535);


    ipLineEdit = new QLineEdit("0.0.0.0");
    ipLineEdit->setInputMask("000.000.000.000");
    portLineEdit = new QLineEdit("8080",this);
    portLineEdit->setValidator(portValidator);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *openPushButon = new QPushButton("Open");
    QPushButton *listonPishbuton = new QPushButton("Listen");
    buttonLayout->addWidget(openPushButon);
    buttonLayout->addWidget(listonPishbuton);


    QButtonGroup *buttonGroup = new QButtonGroup;
    serialChekBox =new QCheckBox("Serial");
    tcpCheckBox = new QCheckBox("Tcp");
    buttonGroup->addButton(serialChekBox);
    buttonGroup->addButton(tcpCheckBox);
    buttonGroup->setExclusive(true);


    QGroupBox *checkBoxGroupBox = new QGroupBox("Connection");
    QVBoxLayout *checkboxeslayout = new QVBoxLayout();
    checkboxeslayout->addWidget(tcpCheckBox);
    checkboxeslayout->addWidget(serialChekBox);
    checkBoxGroupBox->setLayout(checkboxeslayout);

    ipportWidget = new QWidget();
    QGridLayout *ipportLayout = new QGridLayout();
    QLabel *ipLabel = new QLabel("IP");
    QLabel *portLabel = new QLabel("Port");
    ipportLayout->addWidget(ipLabel);
    ipportLayout->addWidget(portLabel,0,1);
    ipportLayout->addWidget(ipLineEdit,1,0);
    ipportLayout->addWidget(portLineEdit,1,1);
    ipportWidget->setLayout(ipportLayout);

    serialWidget = new QWidget();
    QGridLayout *serialLayout = new QGridLayout();
    QLabel *PortNameLabel= new QLabel("PortName");
    QLabel *buadRateLabel = new QLabel("BuadRate");
    serialComboBox = new QComboBox(this);
    baudRateComboBox = new QComboBox();
    serialWidget->setLayout(serialLayout);

    serialLayout->addWidget(PortNameLabel);
    serialLayout->addWidget(buadRateLabel,0,1);
    serialLayout->addWidget(serialComboBox,1,0);
    serialLayout->addWidget(baudRateComboBox,1,1);

    QGroupBox *connectionGroupBox = new QGroupBox("Config");
    QVBoxLayout *groupLayout = new QVBoxLayout();
    groupLayout->addWidget(ipportWidget);
    groupLayout->addWidget(serialWidget);
    connectionGroupBox->setLayout(groupLayout);


    mySpinBox1 = new QSpinBox(this);
    mySpinBox1->setReadOnly(true);
    mySpinBox1->setRange(0 , 99999);

    mySpinBox2 = new QSpinBox(this);
    mySpinBox2->setReadOnly(true);
    mySpinBox2->setRange(0 , 99999);

    mySpinBox3 = new QSpinBox(this);
    mySpinBox3->setReadOnly(true);
    mySpinBox3->setRange(0 , 99999);

    mySpinBox4 = new QSpinBox(this);
    mySpinBox4->setReadOnly(true);
    mySpinBox4->setRange(0 , 99999);

    mySpinBox5 = new QSpinBox(this);
    mySpinBox5->setReadOnly(true);
    mySpinBox5->setRange(0 , 99999);

    QWidget *spinBoxesWidget = new QWidget();
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    spinBoxesWidget->setLayout(hBoxLayout);

    hBoxLayout->addWidget(mySpinBox1);
    hBoxLayout->addWidget(mySpinBox2);
    hBoxLayout->addWidget(mySpinBox3);
    hBoxLayout->addWidget(mySpinBox4);
    hBoxLayout->addWidget(mySpinBox5);

    myProgress = new QProgressBar(this);
    //myProgress->setValue(0);

    QGroupBox *informationGroupBox = new  QGroupBox("Status");
    QVBoxLayout *informationLayout = new QVBoxLayout();
    informationLayout->addWidget(spinBoxesWidget);
    informationLayout->addWidget(myProgress);
    informationGroupBox->setLayout(informationLayout);

    mainGridLayout->addWidget(checkBoxGroupBox,1,0);
    mainGridLayout->addItem(buttonLayout,0,0);
    mainGridLayout->addWidget(connectionGroupBox,2,0);
    mainGridLayout->addWidget(informationGroupBox,3,0);

    myTimer = new QTimer(this);
    serialPortTest = new QSerialPort(this);

    mainWidget->setLayout(mainGridLayout);
    setCentralWidget(mainWidget);
    setFixedSize(500, 480);

    dataManagerClass =new fileDataManager();
    tcpClass = new tcpmanager(this);
    serialClass = new serialmanager(this);

    connect(dataManagerClass, &fileDataManager::lineReaded, this, &MainWindow::updateSpinBox);
    connect(tcpClass,&tcpmanager::tcpSignal,this,&MainWindow::updateSpinBoxTcp);
    connect(serialClass,&serialmanager::serialSignal,this,&MainWindow::updateSpinBoxSerial);

    connect(openPushButon, &QPushButton::clicked , this ,&MainWindow::openFile);
    connect(listonPishbuton , &QPushButton::clicked, this, &MainWindow::chooseConnection);
    connect(tcpCheckBox, &QCheckBox::toggled,this , &MainWindow::checboxes);
    connect(serialChekBox, &QCheckBox::toggled,this , &MainWindow::checboxes);

    loadProts();
    loadBaudRate();
}

void MainWindow::openFile()
{
    dataManagerClass->openFile(this);
}

void MainWindow::updateSpinBox(QVector<int> values,int progress)
{
    mySpinBox1->setValue(values[0]);
    mySpinBox2->setValue(values[1]);
    mySpinBox3->setValue(values[2]);
    mySpinBox4->setValue(values[3]);
    mySpinBox5->setValue(values[4]);

    myProgress->setValue(progress);
}

void MainWindow::updateSpinBoxTcp(const dataStruct &data)
{
    mySpinBox1->setValue(data.h1);
    mySpinBox2->setValue(data.h2);
    mySpinBox3->setValue(data.h3);
    mySpinBox4->setValue(data.h4);
    mySpinBox5->setValue(data.h5);
    myProgress->setValue(data.progressBar);
}

void MainWindow::updateSpinBoxSerial(QStringList &data)
{
    mySpinBox1->setValue(data[0].toInt());
    mySpinBox2->setValue(data[2].toInt());
    mySpinBox3->setValue(data[3].toInt());
    mySpinBox4->setValue(data[4].toInt());
    mySpinBox5->setValue(data[5].toInt());
}

void MainWindow::listenToServer()
{
    QString ip = ipLineEdit->text();
    quint16 port = portLineEdit->text().toUShort();
    tcpClass->listenToServer(ip,port);
}



MainWindow::~MainWindow()
{
    if (myServer)
    {
        myServer->close();
        myServer->deleteLater();
        myServer = nullptr;
    }
    if (socket)
    {
        socket->disconnectFromHost();
        socket->deleteLater();
        socket = nullptr;
    }
}

void MainWindow::loadBaudRate()
{
    foreach(auto baudRate , QSerialPortInfo::standardBaudRates())
    {
        baudRateComboBox->addItem(QString::number(baudRate));
    }
}

void MainWindow::loadProts()
{
    foreach (auto port, QSerialPortInfo::availablePorts()) {

        serialComboBox->addItem(port.portName());
    }
}

void MainWindow::openPort()
{
    serialClass->openPort(serialComboBox->currentText(),
                          baudRateComboBox->currentText());
}


void MainWindow::chooseConnection()
{
    if (!tcpCheckBox->isChecked() && !serialChekBox->isChecked())
    {
        QMessageBox::warning(this,"Warning","choose a connection first");
    }

    if(tcpCheckBox->isChecked())
    {
        serialPortTest->close();
        listenToServer();
    }

    if(serialChekBox->isChecked())
    {
        openPort();
    }
}

void MainWindow::checboxes()
{
    if(tcpCheckBox->isChecked())
    {
        serialWidget->setEnabled(false);
    }
    else
    {
        serialWidget->setEnabled(true);
    }
    if(serialChekBox->isChecked())
    {
        ipportWidget->setEnabled(false);
    }
    else
    {
        ipportWidget->setEnabled(true);
    }
}


