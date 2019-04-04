#include "executor.h"

executor::executor()
{

}


int executor::Run(const QVector<instruct> &ISet)
{
    int pc = 0;
    while (1) {
        switch (ISet.at(pc).OpCode) {
        case OC_LT:
        case OC_GT:
        case OC_LE:
        case OC_GE:
        case OC_JNE:
        case OC_JE:
            Relation(ISet.at(pc));
            pc++;
            break;
        case OC_IDX:
            {
                bool b = Index(ISet.at(pc));
                if(!b){ return 1; }
            }
            pc++;
            break;
        case OC_FUN:
            function(ISet.at(pc));
            pc++;
            break;
        case OC_PSH:
            Push(ISet.at(pc));
            pc++;
            break;
        case OC_POP:

            break;
        case OC_GO:
            pc = ISet.at(pc).Operand1;
            break;
        case OC_IGO:
            {
                if(STACK.pop().value){ pc = ISet.at(pc).Operand1; }
                else{ pc = ISet.at(pc).Operand2; }
            }
            break;
        case OC_REM:
        case OC_MUL:
        case OC_ADD:
        case OC_SUB:
        case OC_DIV:
            if(arithmetic(ISet.at(pc))){ return 1;}
            pc++;
            break;
        case OC_ASS:
            assignment(ISet.at(pc));
            pc++;
            break;
        case OC_INT:
        case OC_WCHAR:
        case OC_WSTRING:
            Declare(ISet.at(pc));
            pc++;
            break;
        case OC_STOP:
            return 0;
            break;
        }
    }
}


VALUE executor::GetValue(const int &t, const int &opd)
{
    VALUE V;
    switch (t) {
    case OT_INTC:
        V.IV = opd;
        V.type = BT_INT;
        break;
    case OT_WCHARC:
        V.CV = WCCArea.at(opd);
        V.type = BT_WCHAR;
        break;
    case OT_WSTRINGC:
        V.SV = WSCArea.at(opd);
        V.type = BT_WSTRING;
        break;
    case OT_VAR:
        {
            int a = attrtable.at(opd).baseAddr;
            int offset = attrtable.at(opd).offset;
            QVector<int> p;
            V = VarSet.GetValue(a,offset,p);
        }
        break;
    case OT_STACK:
        {
            int svalue = STACK.top().value;
            switch (STACK.top().flag) {
            case OT_INTC:
                V.IV = svalue;
                V.type = BT_INT;
                break;
            case OT_WCHARC:
                V.CV = WCCArea.at(svalue);
                V.type = BT_WCHAR;
                break;
            case OT_WSTRINGC:
                V.SV = WSCArea.at(svalue);
                V.type = BT_WSTRING;
                break;
            case OT_VAR:
                {
                    int a = attrtable.at(svalue).baseAddr;
                    int offset = attrtable.at(svalue).offset;
                    V = VarSet.GetValue(a,offset,STACK.top().index);
                }
                break;
            }
            STACK.pop();
        }
        break;
    }
    return V;
}

bool executor::Index(const instruct &I)
{
    stitem item;
    QVector<int> p;
    const QVector<int> &param = attrtable.at(I.Operand1).param;
    int pnum = I.Operand2;
    int value, svalue, a, offset;
    for(int i=0; i<pnum; ++i){
        svalue = STACK.top().value;


        if(STACK.top().flag==OT_INTC){ value = svalue; }
        else{
            a = attrtable.at(svalue).baseAddr;
            offset = attrtable.at(svalue).offset;
            value = VarSet.GetValue(a,offset,STACK.top().index).IV;
        }


        if(value < 0){ return false; }
        if(i==(param.size())){/*Wstring -> wchar*/
            a = attrtable.at(I.Operand1).baseAddr;
            offset = attrtable.at(I.Operand1).offset;
            if(value >= VarSet.GetString0Ref(a,offset,p).size()){ return false; }
        }
        else{
            if(value >= param.at(i)){ return false; }
        }


        p.append(value);
        STACK.pop();
    }
    item.flag = OT_VAR;
    item.index = p;
    item.value = I.Operand1;
    STACK.push(item);
    return true;
}

bool executor::compare(const int &opc,const int &op1,const int &op2)
{
    bool b;
    switch (opc) {
    case OC_LE:
        b = (op1 <= op2);
        break;
    case OC_GE:
        b = (op1 >= op2);
        break;
    case OC_JNE:
        b = (op1 != op2);
        break;
    case OC_JE:
        b = (op1 == op2);
        break;
    case OC_LT:
        b = (op1 < op2);
        break;
    case OC_GT:
        b = (op1 > op2);
        break;
    }
    return b;
}
bool executor::compare(const int &opc,const QChar &op1,const QChar &op2)
{
    bool b;
    switch (opc) {
    case OC_LE:
        b = (op1 <= op2);
        break;
    case OC_GE:
        b = (op1 >= op2);
        break;
    case OC_JNE:
        b = (op1 != op2);
        break;
    case OC_JE:
        b = (op1 == op2);
        break;
    case OC_LT:
        b = (op1 < op2);
        break;
    case OC_GT:
        b = (op1 > op2);
        break;
    }
    return b;
}
bool executor::compare(const int &opc,const QString &op1,const QString &op2)
{
    bool b;
    switch (opc) {
    case OC_LE:
        b = (op1 <= op2);
        break;
    case OC_GE:
        b = (op1 >= op2);
        break;
    case OC_JNE:
        b = (op1 != op2);
        break;
    case OC_JE:
        b = (op1 == op2);
        break;
    case OC_LT:
        b = (op1 < op2);
        break;
    case OC_GT:
        b = (op1 > op2);
        break;
    }
    return b;
}

void executor::Relation(const instruct &I)
{
    bool   b;
    stitem item;
    VALUE  op1, op2;
    /*考虑到两操作数都为栈的情况下，所以先取第二个操作数再第一个*/
    op2 = GetValue(I.type2, I.Operand2);
    op1 = GetValue(I.type1, I.Operand1);
    switch (op1.type) {
    case BT_INT:
        b = compare(I.OpCode, op1.IV, op2.toInt());
        break;
    case BT_WCHAR:
        b = compare(I.OpCode, op1.CV, op2.toChar());
        break;
    case BT_WSTRING:
        b = compare(I.OpCode, op1.SV, op2.SV);
        break;
    }

    item.flag = OT_INTC;
    if(b){ item.value = 1; }
    else { item.value = 0; }
    STACK.push(item);
}
/*此语法的算术操作都是转换为基本整型再计算*/
int  executor::arithmetic(const instruct &I)
{
    int result;
    stitem item;
    VALUE  op1, op2;
    /*考虑到两操作数都为栈的情况下，所以先取第二个操作数再第一个*/
    op2 = GetValue(I.type2, I.Operand2);
    op1 = GetValue(I.type1, I.Operand1);
    switch (I.OpCode) {
    case OC_ADD:
        result = op1.toInt() + op2.toInt();
        break;
    case OC_SUB:
        result = op1.toInt() - op2.toInt();
        break;
    case OC_MUL:
        result = op1.toInt() * op2.toInt();
        break;
    case OC_DIV:
        if(op2.toInt()==0){ return 1; }
        result = op1.toInt() / op2.toInt();
        break;
    case OC_REM:
        if(op2.toInt()<=0){ return 2; }
        result = op1.toInt() % op2.toInt();
        break;
    }
    item.flag = OT_INTC;
    item.value = result;
    STACK.push(item);
    return 0;
}
void executor::assignment(const instruct &I)
{
    VALUE RValue = GetValue(I.type2, I.Operand2);
    int t, a, offset;
    if(I.type1==OT_VAR){
        QVector<int> p;
        t = attrtable.at(I.Operand1).baseType;
        a = attrtable.at(I.Operand1).baseAddr;
        offset = attrtable.at(I.Operand1).offset;
        switch (t) {
            case BT_INT:
                VarSet.GetInt0Ref(a,offset,p) = RValue.toInt();
                break;
            case BT_WCHAR:
                VarSet.GetChar0Ref(a,offset,p) = RValue.toChar();
                break;
            case BT_WSTRING:
                VarSet.GetString0Ref(a,offset,p) = RValue.SV;
                break;
        }
    }
    if(I.type1==OT_STACK){
        int pos = STACK.top().value;
        t = attrtable.at(pos).baseType;
        a = attrtable.at(pos).baseAddr;
        offset = attrtable.at(pos).offset;
        switch (t) {
            case BT_INT:
                VarSet.GetInt0Ref(a,offset,STACK.top().index) = RValue.toInt();
                break;
            case BT_WCHAR:
                VarSet.GetChar0Ref(a,offset,STACK.top().index) = RValue.toChar();
                break;
            case BT_WSTRING:
                if(STACK.top().index.size()==(attrtable.at(pos).param.size()+1)){
                     VarSet.GetChar0Ref(a,offset,STACK.top().index) = RValue.toChar();
                }
                else{
                     VarSet.GetString0Ref(a,offset,STACK.top().index) = RValue.SV;
                }
                break;
        }
        STACK.pop();
    }
}
void executor::function(const instruct &I)
{
    switch (I.Operand1) {
    case UPRINTF:
        {
            VALUE V = GetValue(OT_STACK,0);
            switch (V.type) {
            case BT_INT:
                FuncUnit.UFunction.printf(V.IV,OutputDev);
                break;
            case BT_WCHAR:
                FuncUnit.UFunction.printf(V.CV,OutputDev);
                break;
            case BT_WSTRING:
                FuncUnit.UFunction.printf(V.SV,OutputDev);
                break;
            }
        }
        break;
    }
}
