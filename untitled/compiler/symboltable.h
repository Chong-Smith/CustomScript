#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include<QByteArray>
#include<QHash>
#include<QVector>

//变量属性表项单元
typedef struct VANode
{
    VANode(){}
    VANode(const int &d,const int &t):dimen(d),baseType(t){}
    int      dimen;
    int      baseType;
}VarAttrElem;

//符号表表项单元
typedef struct LNode
{
    QHash<QByteArray, int> hash;
    int    level;
    int    nextpos;
}LevelElem;


class CSymbolTable
{
public:
    CSymbolTable();

    int RegisterSym(const QByteArray &name, const int &D,
                                const int &T,const int &L);
    /*从符号表中删除L及L以上层次的变量*/
    void DeleteLevel(const int &L);
    /*把符号表的状态回退到这次编译之前的状态*/
    void GobackSym(const int &pos);
    inline bool VarConflict(const QByteArray &name, const int &L)
    {
        if(L > LevelTable.last().level) return false;
        return LevelTable.last().hash.contains(name);
    }
    inline int LookupVar(const QByteArray &name)
    {
        /*由高层次到低层次检索变量，高层次的变量会遮盖低层次的同名变量*/
        int pos=-1;
        for(int i=LevelTable.size()-1; i>0; --i){
            pos = LevelTable.at(i).hash.value(name,(-1));
            if(pos >= 0) return pos;
        }
        return pos;
    }
    inline int GetVarDimen(const int &pos)
    {
        return VAttrTable.at(pos).dimen;
    }
    inline int GetVarType(const int &pos)
    {
        return VAttrTable.at(pos).baseType;
    }
    inline LevelElem& lastItem(void)
    {
        return LevelTable.last();
    }
    inline void Clear(void)
    {
        LevelTable.remove(1,LevelTable.size()-1);
        VAttrTable.resize(100);
    }
private:
    inline void SaveVarAtrr(const int &pos, const int &D, const int &T)
    {
        if(pos >= VAttrTable.size()){
            VAttrTable.append(VarAttrElem(D,T));
        }
        else{
            VAttrTable[pos].dimen = D;
            VAttrTable[pos].baseType = T;
        }
    }

private:
    QVector<VarAttrElem>  VAttrTable;//变量属性表
    QVector<LevelElem>    LevelTable;//层次表
};

#endif // SYMBOLTABLE_H
