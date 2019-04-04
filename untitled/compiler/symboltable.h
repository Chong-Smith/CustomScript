#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include<QByteArray>
#include<QHash>
#include<QVector>

//�������Ա��Ԫ
typedef struct VANode
{
    VANode(){}
    VANode(const int &d,const int &t):dimen(d),baseType(t){}
    int      dimen;
    int      baseType;
}VarAttrElem;

//���ű���Ԫ
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
    /*�ӷ��ű���ɾ��L��L���ϲ�εı���*/
    void DeleteLevel(const int &L);
    /*�ѷ��ű��״̬���˵���α���֮ǰ��״̬*/
    void GobackSym(const int &pos);
    inline bool VarConflict(const QByteArray &name, const int &L)
    {
        if(L > LevelTable.last().level) return false;
        return LevelTable.last().hash.contains(name);
    }
    inline int LookupVar(const QByteArray &name)
    {
        /*�ɸ߲�ε��Ͳ�μ����������߲�εı������ڸǵͲ�ε�ͬ������*/
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
    QVector<VarAttrElem>  VAttrTable;//�������Ա�
    QVector<LevelElem>    LevelTable;//��α�
};

#endif // SYMBOLTABLE_H
