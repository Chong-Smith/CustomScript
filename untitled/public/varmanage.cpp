#include "varmanage.h"

varmanage::varmanage(){}

void varmanage::AllotINT(const QVector<int> &para, int &offset,int &a)
{
    switch (para.size()) {
    case 0:
        {
            a = 0;
            offset = ISet0.nextpos;
            if(offset < ISet0.sets.size()){
                ISet0.sets[offset] = 0;
            }
            else{
                ISet0.sets.append(0);
            }
            ISet0.nextpos++;
        }
        break;
    case 1:
        {
            a = 1;
            offset = ISet1.nextpos;
            INT0 x(para.at(0),0);
            if(offset < ISet1.sets.size()){
                ISet1.sets[offset] = x;
            }
            else{
                ISet1.sets.append(x);
            }
            ISet1.nextpos++;
        }
        break;
    case 2:
        {
            a = 2;
            offset = ISet2.nextpos;
            INT0 x(para.at(0),0);
            INT1 y(para.at(1),x);
            if(offset < ISet2.sets.size()){
                ISet2.sets[offset] = y;
            }
            else{
                ISet2.sets.append(y);
            }
            ISet2.nextpos++;
        }
        break;
    }
}
void varmanage::AllotCHAR(const QVector<int> &para, int &offset,int &a)
{
    switch (para.size()) {
    case 0:{
        a = 3;
        offset = CSet0.nextpos;
        if(offset < CSet0.sets.size()){
            CSet0.sets[offset] = QChar();
        }
        else{
            CSet0.sets.append(QChar());
        }
        CSet0.nextpos++;
    }
        break;
    case 1:{
        a = 4;
        offset = CSet1.nextpos;
        CHAR0 x(para.at(0),QChar());
        if(offset < CSet1.sets.size()){
            CSet1.sets[offset] = x;
        }
        else{
            CSet1.sets.append(x);
        }
        CSet1.nextpos++;
    }
        break;
    case 2:{
        a = 5;
        offset = CSet2.nextpos;
        CHAR0 x(para.at(0),QChar());
        CHAR1 y(para.at(1),x);
        if(offset < CSet2.sets.size()){
            CSet2.sets[offset] = y;
        }
        else{
            CSet2.sets.append(y);
        }
        CSet2.nextpos++;
    }
        break;
    }
}
void varmanage::AllotSTRING(const QVector<int> &para, int &offset, int &a)
{
    switch (para.size()) {
    case 0:{
        a = 6;
        offset = SSet0.nextpos;
        if(offset < SSet0.sets.size()){
            SSet0.sets[offset] = QString();
        }
        else{
            SSet0.sets.append(QString());
        }
        SSet0.nextpos++;
    }
        break;
    case 1:{
        a = 7;
        offset = SSet1.nextpos;
        STRING0 x(para.at(0),QString());
        if(offset < SSet1.sets.size()){
            SSet1.sets[offset] = x;
        }
        else{
            SSet1.sets.append(x);
        }
        SSet1.nextpos++;
    }
        break;
    case 2:{
        a = 8;
        offset = SSet2.nextpos;
        STRING0 x(para.at(0),QString());
        STRING1 y(para.at(1),x);
        if(offset < SSet2.sets.size()){
            SSet2.sets[offset] = y;
        }
        else{
            SSet2.sets.append(y);
        }
        SSet2.nextpos++;
    }
        break;
    }
}
void varmanage::RecycleMemory(const int &a, const int &offset)
{
    switch (a) {
    case 0:
        if(offset < ISet0.nextpos)
            ISet0.nextpos = offset;
        break;
    case 1:
        if(offset < ISet1.nextpos)
            ISet1.nextpos = offset;
        break;
    case 2:
        if(offset < ISet2.nextpos)
            ISet2.nextpos = offset;
        break;
    case 3:
        if(offset < CSet0.nextpos)
            CSet0.nextpos = offset;
        break;
    case 4:
        if(offset < CSet1.nextpos)
            CSet1.nextpos = offset;
        break;
    case 5:
        if(offset < CSet2.nextpos)
            CSet2.nextpos = offset;
        break;
    case 6:
        if(offset < SSet0.nextpos)
            SSet0.nextpos = offset;
        break;
    case 7:
        if(offset < SSet1.nextpos)
            SSet1.nextpos = offset;
        break;
    case 8:
        if(offset < SSet2.nextpos)
            SSet2.nextpos = offset;
        break;
    }
}

VALUE  varmanage::GetValue(const int &a, const int &offset, const QVector<int> &p)
{
    VALUE V;
    switch (a) {
    case 0:
        V.IV = ISet0.sets.at(offset);
        V.type = BT_INT;
        break;
    case 1:
        V.IV = ISet1.sets.at(offset).at(p[0]);
        V.type = BT_INT;
        break;
    case 2:
        V.IV = ISet2.sets.at(offset).at(p[1]).at(p[0]);
        V.type = BT_INT;
        break;
    case 3:
        V.CV = CSet0.sets.at(offset);
        V.type = BT_WCHAR;
        break;
    case 4:
        V.CV = CSet1.sets.at(offset).at(p[0]);
        V.type = BT_WCHAR;
        break;
    case 5:
        V.CV = CSet2.sets.at(offset).at(p[1]).at(p[0]);
        V.type = BT_WCHAR;
        break;
    case 6:
        if(p.size()==1){
            V.CV = SSet0.sets.at(offset).at(p[0]);
            V.type = BT_WCHAR;
        }
        else{
            V.SV = SSet0.sets.at(offset);
            V.type = BT_WSTRING;
        }
        break;
    case 7:
        if(p.size()==2){
            V.CV = SSet1.sets.at(offset).at(p[1]).at(p[0]);
            V.type = BT_WCHAR;
        }
        else{
            V.SV = SSet1.sets.at(offset).at(p[0]);
            V.type = BT_WSTRING;
        }
        break;
    case 8:
        if(p.size()==3){
            V.CV = SSet2.sets.at(offset).at(p[2]).at(p[1]).at(p[0]);
            V.type = BT_WCHAR;
        }
        else{
            V.SV = SSet2.sets.at(offset).at(p[1]).at(p[0]);
            V.type = BT_WSTRING;
        }
        break;
    }
    return V;
}

