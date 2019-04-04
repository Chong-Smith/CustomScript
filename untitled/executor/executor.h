#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <QVector>
#include <QStack>
#include <QDebug>
#include <QChar>
#include <QString>
#include <QTextBrowser>

#include "public/varmanage.h"
#include "public/information.h"
#include "function/function.h"

/*变量属性单元结构*/
typedef struct AttrNode
{
    int  baseType;
    QVector<int> param;
    int  offset;
    int  baseAddr;
}attritem;

/*运算栈单元结构*/
typedef struct StNode
{
    int flag;/*标记value的类型*/
    QVector<int> index;
    int value;
}stitem;


class executor
{
public:
    executor();

    int Run(const QVector<instruct> &ISet);
    inline void SetOutputDev(QTextBrowser *dev)
    {
        OutputDev = dev;
    }

private:
    VALUE GetValue(const int &t,const int &opd);
    bool  compare(const int &opc,const int &op1,const int &op2);
    bool  compare(const int &opc,const QChar &op1,const QChar &op2);
    bool  compare(const int &opc,const QString &op1,const QString &op2);

    inline void RegisterAttr(const int &pos,const int &t,const QVector<int> &p)
    {
        int i,j;
        attritem item;
        item.baseType = t;
        item.param = p;

        if(pos < attrtable.size()){
            j = attrtable.at(pos).baseAddr;
            i = attrtable.at(pos).offset;
            VarSet.RecycleMemory(j,i);
            attrtable[pos] = item;
        }
        else{
            attrtable.append(item);
        }

        switch (t) {
        case BT_INT:
            VarSet.AllotINT(p,i,j);
            break;
        case BT_WCHAR:
            VarSet.AllotCHAR(p,i,j);
            break;
        case BT_WSTRING:
            VarSet.AllotSTRING(p,i,j);
            break;
        }
        attrtable[pos].baseAddr = j;
        attrtable[pos].offset   = i;
    }
    inline void Declare(const instruct &I)
    {
        QVector<int> param;
        for(int i=0; i<I.Operand1; ++i){
            param.append(STACK.pop().value);
        }
        RegisterAttr(I.Operand2, (I.OpCode)-55, param);
    }
    inline void Push(const instruct &I)
    {
        stitem item;
        item.flag = I.type1;
        item.value = I.Operand1;
        STACK.push(item);
    }
    bool Index(const instruct &I);
    void Relation(const instruct &I);
    int  arithmetic(const instruct &I);
    void assignment(const instruct &I);
    void function(const instruct &I);


private:
    QVector<attritem>  attrtable;
    varmanage          VarSet;
    QStack<stitem>     STACK;

private:
    QTextBrowser       *OutputDev;

};

#endif // EXECUTOR_H
