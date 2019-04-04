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
参数个数数组
  0         1      ...
函数编号  参数1的维度 ...
参数个数  参数1的类型 ...
*/
void userfunc::SetParamArr()
{
    /*printf函数的参数格式数组*/
    param1[0][0] = UPRINTF; param1[1][0] = 0;
    param1[0][1] = 1;       param1[1][1] = BT_UNDEFINE;
    /**/
}
void userfunc::SetFuncTable()
{
    FuncTable.clear();
    FuncTable.insert(NameList.at(0),param1);
}
