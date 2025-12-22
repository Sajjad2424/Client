#ifndef FILEDATAMANAGER_H
#define FILEDATAMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QWidget>
#include <QFile>
#include <QTextStream>

class fileDataManager : public QObject
{ Q_OBJECT


public:
    fileDataManager();

    void openFile(QWidget *paerent);
    void readFile(const QString &filePath);

signals:
    void lineReaded(QVector<int> values,int progress);

private slots:
    void readingNextLine();




private:

    QStringList lineStringList;
    int currentIndex =0;
    QTimer *myTimer;


};

#endif // FILEDATAMANAGER_H
