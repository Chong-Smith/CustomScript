#ifndef COMPILER_H
#define COMPILER_H

#include <QVector>
#include <QTextBrowser>
#include <QDebug>
#include "public/information.h"
#include "compiler/symboltable.h"
#include "compiler/scanner.h"
#include "compiler/parser.h"

/*�ս���ڵ�*/
typedef struct TNode
{
    int nodeType;
    int dimen;
    int baseType;
    int        num;//����value
    QByteArray str;//�ַ���value(��¼ID���ߺ�����)
}terminator;


/*
 * ���ڴʷ����������﷨��������������ģ�
 * ���Ա���������õ���ģʽ
*/
class Compiler_C
{
public:
    /*��ĵ���������ʽʵ�֣�*/
    static Compiler_C& GetInstance(void);

    inline int FormInstruct(const int &opc,const int &op1,const int &t1,const int &op2,const int &t2 )
    {
        instructs.append(instruct(opc,op1,t1,op2,t2));
        return (instructs.size()-1);
    }
    inline void RemoveAllInstruct(void)
    {
        instructs.clear();
    }
    inline instruct* GetInstruct(const int &i)
    {
        return (instructs.data() + i);
    }
    inline int InstructNum(void)
    {
        return instructs.size();
    }

    inline terminator*  NewTerminator(const int &kind, const int &D,const int &T,const int &V)
    {
        terminator node;
        node.nodeType = kind;
        node.dimen = D;
        node.baseType = T;
        node.num = V;
        terminators.append(node);
        return (terminators.data() + (terminators.size()-1));
    }
    inline terminator*  NewTerminator(const int &kind, const int &D,const int &T,const QByteArray &V)
    {
        terminator node;
        node.nodeType = kind;
        node.dimen = D;
        node.baseType = T;
        node.str = V;
        terminators.append(node);
        return (terminators.data() + (terminators.size()-1));
    }
    inline terminator*  NewTerminator(const int &kind, const int &D,const int &T,const int &pos,const QByteArray &id)
    {
        terminator node;
        node.nodeType = kind;
        node.dimen = D;
        node.baseType = T;
        node.num = pos;
        node.str = id;
        terminators.append(node);
        return (terminators.data() + (terminators.size()-1));
    }
    inline void ClearTerminators(void)
    {
        terminators.clear();
    }
    /*�����ս���ڵ�õ���ָ���ж�Ӧ��������������*/
    inline void GetOpdandOT(const terminator* node,int &opd, int &ot)
    {
        switch (node->nodeType) {
        case NT_CONST:
            ot = node->baseType;
            opd = node->num;
            break;
        case NT_VAR:
            ot = OT_VAR;
            opd = node->num;
            break;
        case NT_EXP:
            ot = OT_STACK;
            opd = 0;
            break;
        }
    }
    inline void RecordCompilerInfo(const QString &str)
    {
        CompilerInfo.append(str);
    }
    inline QString& GetCompilerInfo(void)
    {
        return CompilerInfo;
    }
    int  compiler(const QString &inputText, const int &lineNum);
    /*��ָ���ӡ��صĺ���*/
    void printfinstructs(QTextBrowser* dev=nullptr);
    void initial();

    inline const QVector<instruct>& GetAllInstruct()
    {
        return instructs;
    }

private:
    explicit Compiler_C();
    static   Compiler_C instance;

private:
    QString   CompilerInfo;/*�����������в�������Ϣ*/

private:
    QVector<terminator>  terminators;
    QVector<instruct>    instructs;

public:
    CSymbolTable  symboltable;
    int           ErrorSum;/*��¼��������еĴ�������*/
    int           StartLineNum;/*����ʱ��ʼ�к�*/
};


extern Compiler_C& CompilerUnit;

#endif // AST_H
