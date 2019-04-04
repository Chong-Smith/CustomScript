#include"compiler.h"

Compiler_C  Compiler_C::instance;
Compiler_C& Compiler_C::GetInstance(void)
{
    return instance;
}


Compiler_C::Compiler_C()
{
    terminators.reserve(20);
    instructs.reserve(5000);
}

/*此编译函数兼容一次性全编译和间接性片段编译*/
/*在每次正确编译片段后，变量层次回到0层次*/
int  Compiler_C::compiler(const QString &inputText ,const int &lineNum)
{
    int before = symboltable.lastItem().nextpos;
    /*初始化指令数组及终端结点数组*/
    instructs.clear();
    terminators.clear();
    /*初始化保存编译信息的变量*/
    CompilerInfo.clear();
    /*初始化常量保存区*/
    WCCArea.clear();
    WSCArea.clear();

    if(inputText.isEmpty()){
        RecordCompilerInfo(QString::fromLocal8Bit("请输入有效内容"));
        return 2;
    }

    QByteArray text = inputText.toUtf8();
    yylex_destroy();/*初始化词法扫描器*/
    StartLineNum = lineNum;/*把编译处的开始行号传递给词法扫描器*/
    YY_BUFFER_STATE buffer = yy_scan_string(text.constData());
    //yydebug = 1;
    yyparse();/*语法分析器*/
    yy_delete_buffer(buffer);/*记得释放缓存*/

    if(!ErrorSum){
        RecordCompilerInfo(QString::fromLocal8Bit("\n---编译成功---"));
        instructs.append(instruct(OC_STOP,0,OT_INTC,0,OT_INTC));
        return 0;
    }
    else{
        symboltable.GobackSym(before);//把符号表恢复到此次编译之前的状态
        RecordCompilerInfo(QString::fromLocal8Bit("\n---编译失败---"));
        return 1;
    }
}
void Compiler_C::printfinstructs(QTextBrowser* dev)
{
    if(dev == nullptr) return;
    dev->clear();
    if(instructs.isEmpty()) return;

    dev->append(QString("[wchar]"));
    if(WCCArea.size()){
        dev->insertPlainText("\n");
        for(int i=0; i<WCCArea.size(); ++i){
            dev->insertPlainText(QString("'%1' ").arg(WCCArea.at(i)));
            if(i/10 == 9)
                dev->insertPlainText("\n");
        }
    }
    dev->append(QString("[wstring]"));
    if(WSCArea.size()){
        for(int i=0; i<WSCArea.size(); ++i){
            dev->append(QString("\"%1\"").arg(WSCArea.at(i)));
        }
    }

    dev->append(QString("[code]"));
    QString str, str1, str2;
    int size = instructs.size();
    for(int i=0; i<size; ++i){
        str1 = GetOpStr(instructs.at(i).Operand1, instructs.at(i).type1);
        str2 = GetOpStr(instructs.at(i).Operand2, instructs.at(i).type2);
        str = QString("%1:(%2, %3, %4)//%5")
                .arg(i,4,10,QLatin1Char('0'))
                .arg(instructs.at(i).OpCode,3)
                .arg(str1,-6)
                .arg(str2,-6)
                .arg(OCMaptoStr(instructs.at(i).OpCode));
        dev->append(str);
    }
}

void Compiler_C::initial()
{
    instructs.clear();
    terminators.clear();
    symboltable.Clear();
    /*初始化保存编译信息的变量*/
    CompilerInfo.clear();
    /*初始化常量保存区*/
    WCCArea.clear();
    WSCArea.clear();
}




Compiler_C& CompilerUnit = Compiler_C::GetInstance();

