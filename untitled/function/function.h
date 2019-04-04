#ifndef FUNCTION_H
#define FUNCTION_H

#include <QByteArray>
#include "function/UF/userfunc.h"

class function
{
public:
    /*����ģʽ*/
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
    int (*attrPtr)[2];//ָ���Ӧ�����ĸ�ʽ�������飻
    userfunc UFunction;//�û�������

private:
    explicit function();
    static   function instance;

};

extern function& FuncUnit;

#endif // FUNCTION_H
