#include "information.h"

QVector<QChar>    WCCArea;
QVector<QString>  WSCArea;

QString OCMaptoStr(const int &oc)
{
    QString str;
    switch (oc) {
    case OC_LE:
        str = "<=";
        break;
    case OC_GE:
        str = ">=";
        break;
    case OC_JNE:
        str = "!=";
        break;
    case OC_JE:
        str = "==";
        break;
    case OC_IDX:
        str = QString::fromLocal8Bit("数组索引");
        break;
    case OC_FUN:
        str = QString::fromLocal8Bit("函数调用");
        break;
    case OC_PSH:
        str = QString::fromLocal8Bit("进栈");
        break;
    case OC_POP:
        str = QString::fromLocal8Bit("出栈");
        break;
    case OC_GO:
        str = QString::fromLocal8Bit("无条件跳转");
        break;
    case OC_IGO:
        str = QString::fromLocal8Bit("条件跳转");
        break;
    case OC_REM:
        str = "%";
        break;
    case OC_MUL:
        str = "*";
        break;
    case OC_ADD:
        str = "+";
        break;
    case OC_SUB:
        str = "-";
        break;
    case OC_DIV:
        str = "/";
        break;
    case OC_LT:
        str = "<";
        break;
    case OC_ASS:
        str = "=";
        break;
    case OC_GT:
        str = ">";
        break;
    case OC_INT:
        str = QString::fromLocal8Bit("声明整型变量");
        break;
    case OC_WCHAR:
        str = QString::fromLocal8Bit("声明单字符变量");
        break;
    case OC_WSTRING:
        str = QString::fromLocal8Bit("声明字符串变量");
        break;
    case OC_STOP:
        str = "Stop running";
        break;
    default:
        break;
    }
    return str;
}

QString GetOpStr(const int &op,const int &type)
{
    QString str;
    switch (type) {
    case OT_INTC:
        str = QString("N<%1>").arg(op);
        break;
    case OT_WCHARC:
        str = QString("C:%1").arg(op);
        break;
    case OT_WSTRINGC:
        str = QString("S:%1").arg(op);
        break;
    case OT_VAR:
        str = QString("V:%1").arg(op);
        break;
    case OT_FUN:
        str = QString("F:%1").arg(op);
        break;
    case OT_STACK:
        str = "$$";
        break;
    default:
        break;
    }
    return str;
}
