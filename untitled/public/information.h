#ifndef INFORMATION_H
#define INFORMATION_H

#include <QVector>
#include <QChar>
#include <QString>


enum NodeType{
    /*���ʽ���־*/NT_EXP = 1,
    /*�����ڵ��־*/NT_CONST,
    /*�����ڵ��־*/NT_VAR,
    /*�����ڵ��־*/NT_DECL,
    /*�����ڵ��־*/NT_FUN = 5
};

enum BaseType{
    /*δ���������*/BT_UNDEFINE = 6,
    /*��������*/BT_BOOL,
    /*��������*/BT_INT,
    /*���ַ�����*/BT_WCHAR,
    /*���ַ�������*/BT_WSTRING = 10
};

enum OperatorCode{
    /*С�ڵ���*/OC_LE = 11,
    /*���ڵ���*/OC_GE,
    /*�жϲ�����*/OC_JNE,
    /*�жϵ���*/OC_JE,
    /*��������*/OC_IDX,
    /*��������*/OC_FUN,
    /*ѹջ*/OC_PSH,
    /*��ջ*/OC_POP,
    /*��������ת*/OC_GO,
    /*������ת*/OC_IGO,
    /*���ֵ࣬��ASCIIһ��*/OC_REM = 37,
    /*�ˣ�ֵ��ASCIIһ��*/OC_MUL = 42,
    /*�ӣ�ֵ��ASCIIһ��*/OC_ADD = 43,
    /*����ֵ��ASCIIһ��*/OC_SUB = 45,
    /*����ֵ��ASCIIһ��*/OC_DIV = 47,
    /*С�ڣ�ֵ��ASCIIһ��*/OC_LT = 60,
    /*��ֵ��ֵ��ASCIIһ��*/OC_ASS = 61,
    /*���ڣ�ֵ��ASCIIһ��*/OC_GT = 62,
    /*�������ͱ���*/OC_INT,
    /*�������ַ�����*/OC_WCHAR,
    /*�������ַ�������*/OC_WSTRING,
    /*����ֹͣ*/OC_STOP
};

enum OperandType{
    /*���ͳ�������*/OT_INTC = BT_INT,
    /*���ַ���������*/OT_WCHARC,
    /*���ַ�����������*/OT_WSTRINGC,
    /*��������*/OT_VAR = 65,
    /*��������*/OT_FUN,
    /*ջ����*/OT_STACK
};


/*�Զ������ַ��ָ���ʽ*/
typedef struct INode
{
    INode(){}
    INode(const int &opc,const int &op1,const int &t1,const int &op2,const int &t2 ):
         OpCode(opc),Operand1(op1),type1(t1),Operand2(op2),type2(t2){ }

    int  OpCode;
    int  Operand1;
    int  type1;
    int  Operand2;
    int  type2;
}instruct;

/*���ݲ�����õ���Ӧ�Ĳ������ı�*/
extern QString OCMaptoStr(const int &oc);
/*�õ�ָ���в��������Ӧ�Ĵ�ӡ�ı�*/
extern QString GetOpStr(const int &op,const int &type);


/*���ַ�������*/
extern QVector<QChar>    WCCArea;
/*���ַ���������*/
extern QVector<QString>  WSCArea;


#endif // INFORMATION_H
