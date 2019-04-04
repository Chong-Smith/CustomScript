#ifndef INFORMATION_H
#define INFORMATION_H

#include <QVector>
#include <QChar>
#include <QString>


enum NodeType{
    /*表达式点标志*/NT_EXP = 1,
    /*常量节点标志*/NT_CONST,
    /*变量节点标志*/NT_VAR,
    /*声明节点标志*/NT_DECL,
    /*函数节点标志*/NT_FUN = 5
};

enum BaseType{
    /*未定义的类型*/BT_UNDEFINE = 6,
    /*布尔类型*/BT_BOOL,
    /*整型类型*/BT_INT,
    /*宽字符类型*/BT_WCHAR,
    /*宽字符串类型*/BT_WSTRING = 10
};

enum OperatorCode{
    /*小于等于*/OC_LE = 11,
    /*大于等于*/OC_GE,
    /*判断不等于*/OC_JNE,
    /*判断等于*/OC_JE,
    /*数组索引*/OC_IDX,
    /*函数调用*/OC_FUN,
    /*压栈*/OC_PSH,
    /*退栈*/OC_POP,
    /*无条件跳转*/OC_GO,
    /*条件跳转*/OC_IGO,
    /*求余，值与ASCII一致*/OC_REM = 37,
    /*乘，值与ASCII一致*/OC_MUL = 42,
    /*加，值与ASCII一致*/OC_ADD = 43,
    /*减，值与ASCII一致*/OC_SUB = 45,
    /*除，值与ASCII一致*/OC_DIV = 47,
    /*小于，值与ASCII一致*/OC_LT = 60,
    /*赋值，值与ASCII一致*/OC_ASS = 61,
    /*大于，值与ASCII一致*/OC_GT = 62,
    /*声明整型变量*/OC_INT,
    /*声明宽字符变量*/OC_WCHAR,
    /*声明宽字符串变量*/OC_WSTRING,
    /*程序停止*/OC_STOP
};

enum OperandType{
    /*整型常量对象*/OT_INTC = BT_INT,
    /*宽字符常量对象*/OT_WCHARC,
    /*宽字符串常量对象*/OT_WSTRINGC,
    /*变量对象*/OT_VAR = 65,
    /*函数对象*/OT_FUN,
    /*栈对象*/OT_STACK
};


/*自定义二地址码指令格式*/
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

/*根据操作码得到对应的操作码文本*/
extern QString OCMaptoStr(const int &oc);
/*得到指令中操作对象对应的打印文本*/
extern QString GetOpStr(const int &op,const int &type);


/*宽字符常量区*/
extern QVector<QChar>    WCCArea;
/*宽字符串常量区*/
extern QVector<QString>  WSCArea;


#endif // INFORMATION_H
