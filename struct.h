#ifndef STRUCT_H
#define STRUCT_H
#include <QDataStream>


struct dataStruct {
    double h1;
    double h2;
    double h3;
    double h4;
    double h5;
   //QVector<double>dataVector;
    int progressBar;
};

inline QDataStream &operator>>(QDataStream &in, dataStruct &data)
{
    in >> data.h1 >> data.h2 >> data.h3 >> data.h4 >> data.h5>>data.progressBar;
    return in;
}

#endif // STRUCT_H



