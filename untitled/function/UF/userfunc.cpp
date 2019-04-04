#include "userfunc.h"

userfunc::userfunc()
{
    SetNameList();
    SetParamArr();
    SetFuncTable();
}


void userfunc::SetNameList()
{
    NameList.clear();
    NameList.append("printf");
}

/*
������������
  0         1      ...
�������  ����1��ά�� ...
��������  ����1������ ...
*/
void userfunc::SetParamArr()
{
    /*printf�����Ĳ�����ʽ����*/
    param1[0][0] = UPRINTF; param1[1][0] = 0;
    param1[0][1] = 1;       param1[1][1] = BT_UNDEFINE;
    /**/
}
void userfunc::SetFuncTable()
{
    FuncTable.clear();
    FuncTable.insert(NameList.at(0),param1);
}
