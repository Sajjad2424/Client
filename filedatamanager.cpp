#include "filedatamanager.h"

#include "QFileDialog"
#include "QMessageBox"
#include "QDebug"
#include <QObject>
#include <QStringList>
#include <QTimer>

fileDataManager::fileDataManager(): QObject()
{
    myTimer = new QTimer(this);

    connect(myTimer, &QTimer::timeout, this, &fileDataManager::readingNextLine);

}


void fileDataManager::openFile(QWidget *parent)
{
    QString fileText = QFileDialog::getOpenFileName(parent,"Select Text File", "", "Text Files (*.txt);;All Files (*)");
    if(!fileText.isEmpty())
    {
        readFile(fileText);
    }
    else
    {
        qDebug() << "Can't open the file";
    }
}

void fileDataManager::readFile(const QString &filePath)
{
    QFile mainFile(filePath);
    if (!mainFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't read The File";
        return;
    }

    QTextStream mainText(&mainFile);
    lineStringList.clear();
    while (!mainText.atEnd())
    {
        lineStringList << mainText.readLine();
    }

    currentIndex = 0;

    // myProgress->setMaximum(stringLines.size());
    // myProgress->setValue(0);
    myTimer->start(2000);

}

void fileDataManager::readingNextLine()
{

    if (currentIndex < lineStringList.size())
    {
        QString oneLineText = lineStringList[currentIndex];
        QStringList values = oneLineText.split(',');
        if (values.size() >= 5)
        {
            QVector<int>numbers;
            numbers.append(values[0].toInt());
            numbers.append(values[1].toInt());
            numbers.append(values[2].toInt());
            numbers.append(values[3].toInt());
            numbers.append(values[4].toInt());

          int progress = ((currentIndex + 1) * 100) / lineStringList.size();
           emit lineReaded(numbers,progress);

        }

        currentIndex++;
    }
    else
    {
        qDebug() << "All line Read"; myTimer->stop();
    }
}
