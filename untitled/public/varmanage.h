#ifndef VARMANAGE_H
#define VARMANAGE_H

#include <QVector>
#include <QChar>
#include <QDebug>
#include <QString>
#include "public/information.h"

typedef QVector<int>      INT0;
typedef QVector<INT0>     INT1;
typedef QVector<INT1>     INT2;
typedef QVector<QChar>    CHAR0;
typedef QVector<CHAR0>    CHAR1;
typedef QVector<CHAR1>    CHAR2;
typedef QVector<QString>  STRING0;
typedef QVector<STRING0>  STRING1;
typedef QVector<STRING1>  STRING2;

/*值*/
typedef struct ValNode
{
    int      IV;
    QChar    CV;
    QString  SV;
    int      type;

    inline int toInt()
    {
        if(type==BT_INT){ return IV; }
        if(type == BT_WCHAR){ return (int)CV.unicode(); }
    }
    inline QChar toChar()
    {
        if(type==BT_INT){ return QChar(IV); }
        if(type == BT_WCHAR){ return CV; }
    }

    ValNode& operator =(const ValNode &other)
    {
        IV   = other.IV;
        CV   = other.CV;
        SV   = other.SV;
        type = other.type;
        return *this;
    }

}VALUE;

/*内存区的定义*/
template<typename T>
class  Memory
{
public:
    Memory(){ nextpos=0; }
    int nextpos;
    T sets;
};


class varmanage
{
public:
    varmanage();

    void AllotINT(const QVector<int> &para, int &offset, int &a);
    void AllotCHAR(const QVector<int> &para, int &offset, int &a);
    void AllotSTRING(const QVector<int> &para, int &offset, int &a);
    void RecycleMemory(const int &a, const int &offset);

    VALUE GetValue(const int &a,const int &offset,const QVector<int> &p);

    inline int&  GetInt0Ref(const int &a,const int &offset,const QVector<int> &p)
    {
        switch (a) {
        case 0:
                return ISet0.sets[offset];
        case 1:
               return ISet1.sets[offset][p.at(0)];
        case 2:
               return ISet2.sets[offset][p.at(1)][p.at(0)];
        }
    }
    inline INT0& GetInt1Ref(const int &a,const int &offset,const QVector<int> &p)
    {
        if(a == 1){ return ISet1.sets[offset]; }
        if(a == 2){ return ISet2.sets[offset][p.at(0)]; }
    }
    inline INT1& GetInt2Ref(const int &offset)
    {
        return ISet2.sets[offset];
    }

    inline QChar& GetChar0Ref(const int &a,const int &offset,const QVector<int> &p)
    {
        switch (a) {
        case 3:
            return CSet0.sets[offset];
        case 4:
            return CSet1.sets[offset][p.at(0)];
        case 5:
            return CSet2.sets[offset][p.at(1)][p.at(0)];
        case 6:
            return *(SSet0.sets[offset].data()+p.at(0));
        case 7:
            return *(SSet1.sets[offset][p.at(1)].data()+p.at(0));
        case 8:
            return *(SSet2.sets[offset][p.at(2)][p.at(1)].data()+p.at(0));
        }
    }
    inline CHAR0& GetChar1Ref(const int &a,const int &offset,const QVector<int> &p)
    {
        if(a == 4){ return CSet1.sets[offset]; }
        if(a == 5){ return CSet2.sets[offset][p.at(0)]; }
    }
    inline CHAR1& GetCahr2Ref(const int &offset)
    {
        return CSet2.sets[offset];
    }

    inline QString& GetString0Ref(const int &a,const int &offset,const QVector<int> &p)
    {
        switch (a) {
        case 6:
                return SSet0.sets[offset];
        case 7:
                return SSet1.sets[offset][p.at(0)];
        case 8:
                return SSet2.sets[offset][p.at(1)][p.at(0)];
        }
    }
    inline STRING0& GetString1Ref(const int &a,const int &offset,const QVector<int> &p)
    {
        if(a == 7){ return SSet1.sets[offset]; }
        if(a == 8){ return SSet2.sets[offset][p.at(0)]; }
    }
    inline STRING1& GetString2Ref(const int &offset)
    {
        return SSet2.sets[offset];
    }

private:
    Memory<INT0>     ISet0;//基址区：0
    Memory<INT1>     ISet1;//基址区：1
    Memory<INT2>     ISet2;//基址区：2
    Memory<CHAR0>    CSet0;//基址区：3
    Memory<CHAR1>    CSet1;//基址区：4
    Memory<CHAR2>    CSet2;//基址区：5
    Memory<STRING0>  SSet0;//基址区：6
    Memory<STRING1>  SSet1;//基址区：7
    Memory<STRING2>  SSet2;//基址区：8
};

#endif // VARMANAGE_H
