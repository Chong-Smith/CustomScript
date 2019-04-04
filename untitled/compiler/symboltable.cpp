#include "symboltable.h"


CSymbolTable::CSymbolTable()
{
    VAttrTable.resize(100);
    LevelTable.reserve(20);

    LevelTable.append(LevelElem());
    LevelTable[0].level = -1;
    LevelTable[0].nextpos = 0;
}


int CSymbolTable::RegisterSym(const QByteArray &name, const int &D, const int &T, const int &L)
{
    /*新符号的属性记录在变量属性表的位置*/
    int pos = LevelTable.last().nextpos;
    int currlevel = LevelTable.last().level;

    if(L > currlevel){
        /*增加新的嵌套层次*/
        LevelElem  NewElem;
        NewElem.hash.insert(name,pos);
        NewElem.level = L;
        NewElem.nextpos = pos + 1;
        LevelTable.append(NewElem);
    }
    else if(L == currlevel){
        /*添加到现有层次中*/
        LevelTable.last().hash.insert(name,pos);
        LevelTable.last().nextpos = pos + 1;
    }

    /*填写属性表*/
    SaveVarAtrr(pos,D,T);
    return pos;
}

void CSymbolTable::DeleteLevel(const int &L)
{
    if(L > LevelTable.last().level)
        return;

    int size  = LevelTable.size();
    int index = size - 1;
    while(L <= LevelTable.at(index).level) index--;
    index++;
    LevelTable.remove(index,size-index);
}
/*每次的回退都是到0层次*/
void CSymbolTable::GobackSym(const int &pos)
{
    int size = LevelTable.size();
    if(pos == 0 ){
        if(size > 1)
            LevelTable.remove(1,size-1);
    }
    else{
        QByteArray name;
        for(int i=pos; i<LevelTable.at(1).nextpos; ++i){
            name = LevelTable.at(1).hash.key(i);
            LevelTable[1].hash.remove(name);
        }
        if(size > 2){
            LevelTable.remove(2,size-2);
        }
        LevelTable[1].nextpos = pos;
    }
}
