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

/*�˱��뺯������һ����ȫ����ͼ����Ƭ�α���*/
/*��ÿ����ȷ����Ƭ�κ󣬱�����λص�0���*/
int  Compiler_C::compiler(const QString &inputText ,const int &lineNum)
{
    int before = symboltable.lastItem().nextpos;
    /*��ʼ��ָ�����鼰�ն˽������*/
    instructs.clear();
    terminators.clear();
    /*��ʼ�����������Ϣ�ı���*/
    CompilerInfo.clear();
    /*��ʼ������������*/
    WCCArea.clear();
    WSCArea.clear();

    if(inputText.isEmpty()){
        RecordCompilerInfo(QString::fromLocal8Bit("��������Ч����"));
        return 2;
    }

    QByteArray text = inputText.toUtf8();
    yylex_destroy();/*��ʼ���ʷ�ɨ����*/
    StartLineNum = lineNum;/*�ѱ��봦�Ŀ�ʼ�кŴ��ݸ��ʷ�ɨ����*/
    YY_BUFFER_STATE buffer = yy_scan_string(text.constData());
    //yydebug = 1;
    yyparse();/*�﷨������*/
    yy_delete_buffer(buffer);/*�ǵ��ͷŻ���*/

    if(!ErrorSum){
        RecordCompilerInfo(QString::fromLocal8Bit("\n---����ɹ�---"));
        instructs.append(instruct(OC_STOP,0,OT_INTC,0,OT_INTC));
        return 0;
    }
    else{
        symboltable.GobackSym(before);//�ѷ��ű�ָ����˴α���֮ǰ��״̬
        RecordCompilerInfo(QString::fromLocal8Bit("\n---����ʧ��---"));
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
    /*��ʼ�����������Ϣ�ı���*/
    CompilerInfo.clear();
    /*��ʼ������������*/
    WCCArea.clear();
    WSCArea.clear();
}




Compiler_C& CompilerUnit = Compiler_C::GetInstance();

