#ifndef FUNCTION_H
#define FUNCTION_H

#include <QByteArray>
#include "function/UF/userfunc.h"

class function
{
public:
    /*单例模式*/
    static function& GetInstance(void);

    inline bool lookup(const QByteArray &name)
    {
        if(name[1] == QChar('s')){
            return false;
        }
        if(name[1] == QChar('u')){
           attrPtr = UFunction.FuncTable.value(name.mid(3),nullptr);
           if(!attrPtr){ return false; }
           return true;
        }
        return false;
    }


public:
    int (*attrPtr)[2];//指向对应函数的格式属性数组；
    userfunc UFunction;//用户函数集

private:
    explicit function();
    static   function instance;

};

extern function& FuncUnit;

#endif // FUNCTION_H
