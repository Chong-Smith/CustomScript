#ifndef USERFUNC_H
#define USERFUNC_H

#include <QHash>
#include <QChar>
#include <QString>
#include <QByteArray>
#include <QTextBrowser>

#include "public/information.h"

enum{
    UPRINTF = 1
};


class userfunc
{
public:
    userfunc();

    void SetNameList();
    void SetParamArr();
    void SetFuncTable();

    int  param1[2][2];//printf
    inline void printf(const int &num,QTextBrowser *dev)
    {
        dev->append(QString().setNum(num));
    }
    inline void printf(const QChar &c,QTextBrowser *dev)
    {
        dev->append(QString(c));
    }
    inline void printf(const QString &s,QTextBrowser *dev)
    {
        dev->append(s);
    }



public:
    QByteArrayList  NameList;
    QHash<QByteArray,int(*)[2]> FuncTable;
};

#endif // USERFUNC_H
