%{
#include <QDebug>
#include <QByteArray>
#include <QStack>
#include <QHash>
#include <QChar>
#include <QString>
#include "public/information.h"
#include "compiler/compiler.h"
#include "function/function.h"

%}

/* ����Ҫ����﷨����������ʹ��%debug�������yydebug��Ϊ1 */
%defines "parser.h"
%output  "parser.cpp"

%{
/*���������������ڱ���ʷ�ɨ������õ��ַ�����ֵ���ַ�������ֵ*/
QChar    wcharval;
QString  wstringval;
void     formWchar(const char* s){ wcharval = QString(s).at(0); }
void     clrWstringval(void){ wstringval.clear(); }
void     formWstring(const char* s){ wstringval.append(s); }



/*Ƕ�ײ�α���*/
int  VarLevel;
/*�����ŵ������*/
int  LBraceNum;
/*��¼��������в����Ĵ���;�����Ŀ*/
int  &ErrNum = CompilerUnit.ErrorSum;
/*��¼����������*/
int  DeclType;


/*����ά������Ϣ
 *��flex��ʹ��
 *��bison��ʼ��*/
int  yycolumn;
/*�ϸ����ս�����к�*/
int  lastNtermCol;
/*�ϸ����ս�����к�*/
int  lastNtermRow;



/*��¼��������з����Ĵ�����߾�����Ϣ*/
QString  ErrStr;
/*����ָ���״̬��־*/
int   ErrState;
void  LexError(const QString &err){ ErrNum++; ErrStr = err; CompilerUnit.RecordCompilerInfo(ErrStr);}



/*ID�Ǻż�FUNNAME�Ǻŷ���ʱ��Identifier�����Ӧ���ַ���ֵ*/
QByteArray  Identifier;
void  SaveIdentStr(const char *s){ Identifier = QByteArray(s); }



/*��¼goup������ת���ĵ�ַ*/
QStack<int>  GUAddr;
/* ��¼��û��д��ַ��godownָ��
 * ��ϣ��ʽ<level,linkhead>
 * ����������
 * fillbackGD�����ַ
*/
QHash<int,int>  GDHash;
void fillbackGD(const int &L, const int &Addr)
{
    if(GDHash.contains(L)){
        int index = GDHash.value(L);
        int pos;
        do{
            pos = CompilerUnit.GetInstruct(index)->Operand1;
            CompilerUnit.GetInstruct(index)->Operand1 = Addr;
            index = pos;
        }while(index >= 0);
        GDHash.remove(L);
    }
}



int  yylex();
void yyerror(const char*);
%}


/*�Ǻſ��Է��������*/
%union{
    int  number;
    struct TNode* TNPtr;
}

/* �����Ǻ� */
%token INT WSTRING  WCHAR
%token IF  WHILE
%token<number> OPERATOR3  OPERATOR1
%token<number> INT_CONST
%token WSTRING_CONST  WCHAR_CONST
%token ID  FUNNAME
%token AND  OR  GODOWN  GOUP


/*�����ս����������*/
%type<TNPtr>  direct_declarator const_exp unary_exp postfix_exp
%type<TNPtr>  variant_exp mult_exp additive_exp
%type<number> relational_exp logical_and_exp logical_or_exp conditional_exp paramlist funcparam

/*����Ĭ�ϵ�λ����Ϣ*/
%locations

/*ÿ��yyparse()����ʱ���ȳ�ʼ����Щ����*/
%initial-action{
    VarLevel = 0;
    ErrNum = 0;
    ErrState = 0;
    LBraceNum = 0;
    yycolumn = 1;

    lastNtermCol = 1;
    lastNtermRow = yylineno = CompilerUnit.StartLineNum;

    ErrStr.clear();
    GUAddr.clear();
    GDHash.clear();
}

%% /***************** ����ΪBNF *******************/
fragment:
| program_list
;
program_list: program  {
    lastNtermRow = @1.last_line;
    lastNtermCol = @1.last_column;

    CompilerUnit.ClearTerminators();
}
| program_list program {
    lastNtermRow = @2.last_line;
    lastNtermCol = @2.last_column;

    CompilerUnit.ClearTerminators();
}
;
program:
  decl
| stat
| error_recover {
     CompilerUnit.RecordCompilerInfo(ErrStr);
     ErrStr.clear();
     ErrState = 0;
     yyerrok;/*��������ָ�ģʽ*/
}
;
error_recover:
  err ';' {
    ErrStr = QString::fromLocal8Bit("<������;ǰ>\n");
}
| err '{' {
    ErrStr = QString::fromLocal8Bit("<������{ǰ>\n");
    yychar = '{';
}
| err '}' {
    if(LBraceNum > 0){
        ErrStr = QString::fromLocal8Bit("<������}ǰ>\n");
        yychar = '}';
    }
    else{
        ErrStr = QString::fromLocal8Bit("�һ�����û��ƥ�䵽��Ӧ�����ţ�\n");
    }
}
| err INT {
    ErrStr = QString::fromLocal8Bit("<�����ڹؼ���intǰ>\n");
    yychar = INT;
}
| err WCHAR {
    ErrStr = QString::fromLocal8Bit("<�����ڹؼ���wcharǰ>\n");
    yychar = WCHAR;
}
| err WSTRING {
    ErrStr = QString::fromLocal8Bit("<�����ڹؼ���wstringǰ>\n");
    yychar = WSTRING;
}
| err IF {
    ErrStr = QString::fromLocal8Bit("<�����ڹؼ���ifǰ>\n");
    yychar = IF;
}
| err WHILE {
    ErrStr = QString::fromLocal8Bit("<�����ڹؼ���whileǰ>\n");
    yychar = WHILE;
}
| err GODOWN {
    ErrStr = QString::fromLocal8Bit("<�����ڹؼ���godownǰ>\n");
    yychar = GODOWN;
}
| err GOUP {
    ErrStr = QString::fromLocal8Bit("<�����ڹؼ���goupǰ>\n");
    yychar = GOUP;
}
;
err: error {
    if(ErrNum > 10){
        YYABORT;
    }
    /*�ڴ���ָ�״̬�£����¸��ǺŲ���Ҫ��ļǺ�ʱ�����ٴν���
     *ErrState���Ƿ�ֹ��δ����Ҫ��ļǺ�ʱ��ֻ�������һ��
    */
    if(!ErrState){
        ErrState = 1;
        if(ErrStr.isEmpty()){
            ErrStr = QString::fromLocal8Bit("%1.%2-%3.%4�������﷨����")
                    .arg(lastNtermRow).arg(lastNtermCol).arg(@1.last_line).arg(@1.last_column);
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
        }
        ErrStr.clear();
    }
}
;
decl: type_spec init_declarator_list ';'
;
type_spec: 
  INT     { DeclType = BT_INT; }
| WCHAR   { DeclType = BT_WCHAR; }
| WSTRING { DeclType = BT_WSTRING; }
;
init_declarator_list: direct_declarator {
    /*�ѱ���ע�ᵽ�������ķ��ű��У����õ�ע���λ��*/
    int pos = CompilerUnit.symboltable.RegisterSym($1->str,$1->dimen,$1->baseType,VarLevel);
    if(!ErrNum){
        switch ($1->baseType) {
        case BT_INT:
             CompilerUnit.FormInstruct(OC_INT,$1->dimen,OT_INTC,pos,OT_INTC);
            break;
        case BT_WCHAR:
             CompilerUnit.FormInstruct(OC_WCHAR,$1->dimen,OT_INTC,pos,OT_INTC);
            break;
        case BT_WSTRING:
             CompilerUnit.FormInstruct(OC_WSTRING,$1->dimen,OT_INTC,pos,OT_INTC);
            break;
        }
    }
}
| init_declarator_list ',' direct_declarator {
    /*�ѱ���ע�ᵽ�������ķ��ű���*/
    int pos = CompilerUnit.symboltable.RegisterSym($3->str,$3->dimen,$3->baseType,VarLevel);
    if(!ErrNum){
        switch ($3->baseType) {
        case BT_INT:
             CompilerUnit.FormInstruct(OC_INT,$3->dimen,OT_INTC,pos,OT_INTC);
          break;
        case BT_WCHAR:
             CompilerUnit.FormInstruct(OC_WCHAR,$3->dimen,OT_INTC,pos,OT_INTC);
          break;
        case BT_WSTRING:
             CompilerUnit.FormInstruct(OC_WSTRING,$3->dimen,OT_INTC,pos,OT_INTC);
          break;
        }
    }
}
;
direct_declarator: ID {
    /*���������*/
    if(CompilerUnit.symboltable.VarConflict(Identifier,VarLevel)){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�����%3�ڲ��%4���Ѿ�����������")
                 .arg(@1.first_line).arg(@1.first_column).arg(QString(Identifier)).arg(VarLevel);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    else{
        $$ = CompilerUnit.NewTerminator(NT_DECL,0,DeclType,Identifier);
    }
}
| direct_declarator '[' INT_CONST ']' {
    if($1->dimen >= 2 ){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У���������%3��ά�Ȳ��ܴ���2��")
                 .arg(@2.first_line).arg(@2.first_column).arg(QString($1->str));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        CompilerUnit.FormInstruct(OC_PSH,$3,OT_INTC,0,OT_STACK);
    }
    $1->dimen++;
    $$ = $1;
}
;
stat: compound_stat
| conditional_stat
| jump_stat ';'
| assignment_exp ';'
| function ';'
;
compound_stat: '{' {
    GUAddr.push(CompilerUnit.InstructNum());
    VarLevel++;
    LBraceNum++;
} fragment '}'{
    GUAddr.pop();
    CompilerUnit.symboltable.DeleteLevel(VarLevel);
    VarLevel--;
    LBraceNum--;
    if(!ErrNum){
        fillbackGD(VarLevel,CompilerUnit.InstructNum());
    }
}
;
conditional_stat:
  IF '(' {
    GUAddr.push(CompilerUnit.InstructNum());
} conditional_exp ')' '{' {
    VarLevel++;    
    LBraceNum++;
    if(!ErrNum){
        int pos = $4;
        instruct* I;
        do{/*��������*/
            I = CompilerUnit.GetInstruct(pos);
            pos = I->Operand1;
            I->Operand1 = $4+1;
        }while(pos >= 0);
    }
} fragment '}'{
    GUAddr.pop();
    CompilerUnit.symboltable.DeleteLevel(VarLevel);
    VarLevel--;    
    LBraceNum--;
    if(!ErrNum){
        int falsepos = CompilerUnit.InstructNum();
        int index = $4;
        instruct* I;
        do{/*�������*/
            I = CompilerUnit.GetInstruct(index);
            index = I->Operand2;
            I->Operand2 = falsepos;
        }while(index >= 0);
        fillbackGD(VarLevel,falsepos);
    }
}
| WHILE '(' {
    GUAddr.push(CompilerUnit.InstructNum());
} conditional_exp ')' '{' {
    VarLevel++;
    LBraceNum++;
    if(!ErrNum){
        int pos = $4;
        instruct* I;
        do{/*��������*/
            I = CompilerUnit.GetInstruct(pos);
            pos = I->Operand1;
            I->Operand1 = $4+1;
        }while(pos >= 0);
    }
} fragment '}' {
    if(!ErrNum){
        CompilerUnit.FormInstruct(OC_GO,GUAddr.top(),OT_INTC,0,OT_INTC);
    }
    GUAddr.pop();
    CompilerUnit.symboltable.DeleteLevel(VarLevel);
    VarLevel--;
    LBraceNum--;
    if(!ErrNum){
        int falsepos = CompilerUnit.InstructNum();
        int index = $4;
        instruct* I;
        do{/*�������*/
            I = CompilerUnit.GetInstruct(index);
            index = I->Operand2;
            I->Operand2 = falsepos;
        }while(index >= 0);
        fillbackGD(VarLevel,falsepos);
    }
}
;
jump_stat: GODOWN ':' INT_CONST {
    int pos = VarLevel - $3;
    if(pos < 0 || $3 == 0){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�godown����ת�����˷�Χ������תֵΪ0��")
                 .arg(@3.first_line).arg(@3.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        int index = CompilerUnit.FormInstruct(OC_GO,-1,OT_INTC,0,OT_INTC);
        if (GDHash.contains(pos)){
            CompilerUnit.GetInstruct(index)->Operand1 = GDHash.value(pos);
            GDHash[pos] = index;
        }
        else{
            GDHash.insert(pos, index);
        }
    }
}
| GOUP ':' INT_CONST {
    int pos = VarLevel - $3;
    if(pos < 0 || $3 == 0){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�goup����ת�����˷�Χ������תֵΪ0��")
                 .arg(@3.first_line).arg(@3.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        CompilerUnit.FormInstruct(OC_GO,GUAddr.at(pos),OT_INTC,0,OT_INTC);
    }
}
;
conditional_exp: logical_or_exp { $$ = $1; }
;
logical_or_exp: logical_and_exp { $$ = $1; }
| logical_or_exp OR logical_and_exp {
    if(!ErrNum){
        int pos = $1;
        instruct* I;
        do{
            I = CompilerUnit.GetInstruct(pos);
            pos = I->Operand2;
            I->Operand2 = $1+1;
        }while(pos >= 0);
        I = CompilerUnit.GetInstruct($3);
        I->Operand1 = $1;
        $$ = $3;
    }
}
;
logical_and_exp: relational_exp { $$ = $1; }
| logical_and_exp AND relational_exp {
    if(!ErrNum){
        int pos = $1;
        instruct* I;
        do{
            I = CompilerUnit.GetInstruct(pos);
            pos = I->Operand1;
            I->Operand1 = $1+1;
        }while(pos >= 0);
        I = CompilerUnit.GetInstruct($3);
        I->Operand2 = $1;
        $$ = $3;
    }
}
;
relational_exp: 
  additive_exp  OPERATOR1  additive_exp {
    int  t1 = $1->baseType;
    int  t3 = $3->baseType;
    if(t1 != t3){
        if((t1==BT_INT && t3==BT_WCHAR)||(t1==BT_WCHAR && t3==BT_INT)){}
        else{
            ErrStr = QString::fromLocal8Bit("��%1�е�%2�У���ϵ�����%3���������ߵıȽ϶������Ͳ�һ�£�")
                     .arg(@2.first_line).arg(@2.first_column).arg(OCMaptoStr($2));
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
        }
    }
    if($1->dimen!=0 || $3->dimen!=0){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У���ϵ�����%3���������ߵıȽ϶����ǻ������ͣ�")
                 .arg(@2.first_line).arg(@2.first_column).arg(OCMaptoStr($2));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        int opd1, ot1, opd2, ot2;
        CompilerUnit.GetOpdandOT($1,opd1,ot1);
        CompilerUnit.GetOpdandOT($3,opd2,ot2);
        CompilerUnit.FormInstruct($2,opd1,ot1,opd2,ot2);
        $$ = CompilerUnit.FormInstruct(OC_IGO,-1,OT_INTC,-1,OT_INTC);
    }
}
| '(' logical_or_exp ')' { $$ = $2; }
;
assignment_exp: variant_exp '='  additive_exp {
    int t1 = $1->baseType;
    int t3 = $3->baseType;
    if(t1 != t3){
        if((t1==BT_INT && t3==BT_WCHAR)||(t3==BT_INT && t1==BT_WCHAR)){}
        else{
            ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�=���ߵĲ����������Ͳ�ͬ��")
                     .arg(@2.first_line).arg(@2.first_column);
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
        }
    }
    if($1->dimen!=0 || $3->dimen!=0){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�=���ߵĲ��������ǻ������ͣ�")
                 .arg(@2.first_line).arg(@2.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        int opd1, ot1, opd2, ot2;
        CompilerUnit.GetOpdandOT($1,opd1,ot1);
        CompilerUnit.GetOpdandOT($3,opd2,ot2);
        CompilerUnit.FormInstruct(OC_ASS,opd1,ot1,opd2,ot2);
    }
}
;
additive_exp: mult_exp { $$ = $1; }
| additive_exp '+' mult_exp {
    if($1->dimen!=0 || $1->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�+���������������ǻ������ͻ��߻����ַ��ͣ�")
                 .arg(@2.first_line).arg(@2.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if($3->dimen!=0 || $3->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�+���Ҳ�����������ǻ������ͻ��߻����ַ��ͣ�")
                 .arg(@2.first_line).arg(@2.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    if(!ErrNum){
        int opd1, ot1, opd2, ot2;
        CompilerUnit.GetOpdandOT($1,opd1,ot1);
        CompilerUnit.GetOpdandOT($3,opd2,ot2);
        CompilerUnit.FormInstruct(OC_ADD,opd1,ot1,opd2,ot2);
    }
    $1->nodeType = NT_EXP;
    $$ = $1;
}
| additive_exp '-' mult_exp {
    if($1->dimen!=0 || $1->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�-���������������ǻ������ͻ��߻����ַ��ͣ�")
                 .arg(@2.first_line).arg(@2.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if($3->dimen!=0 || $3->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�-���Ҳ�����������ǻ������ͻ��߻����ַ��ͣ�")
                 .arg(@2.first_line).arg(@2.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    if(!ErrNum){
        int opd1, ot1, opd2, ot2;
        CompilerUnit.GetOpdandOT($1,opd1,ot1);
        CompilerUnit.GetOpdandOT($3,opd2,ot2);
        CompilerUnit.FormInstruct(OC_SUB,opd1,ot1,opd2,ot2);
    }
    $1->nodeType = NT_EXP;
    $$ = $1;
}
;
mult_exp: unary_exp { $$ = $1; }
| mult_exp OPERATOR3 unary_exp {
    if($1->dimen!=0 || $1->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�%3���������������ǻ������ͻ��߻����ַ��ͣ�")
                 .arg(@2.first_line).arg(@2.first_column).arg(OCMaptoStr($2));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if($3->dimen!=0 || $3->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�%3���Ҳ�����������ǻ������ͻ��߻����ַ��ͣ�")
                 .arg(@2.first_line).arg(@2.first_column).arg(OCMaptoStr($2));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    if(!ErrNum){
        int opd1, ot1;
        int opd2, ot2;
        CompilerUnit.GetOpdandOT($1,opd1,ot1);
        CompilerUnit.GetOpdandOT($3,opd2,ot2);
        CompilerUnit.FormInstruct($2,opd1,ot1,opd2,ot2);
    }
    $1->nodeType = NT_EXP;
    $$ = $1;
}
;
unary_exp: variant_exp { $$ = $1; }
| '(' additive_exp ')' { $$ = $2; }
| const_exp { $$ = $1; }
| '-' unary_exp {
    if($2->dimen!=0 || $2->baseType!=BT_INT){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У��������Ͳſ�����������")
                 .arg(@2.first_line).arg(@2.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        int opd2, ot2;
        CompilerUnit.GetOpdandOT($2,opd2,ot2);
        CompilerUnit.FormInstruct(OC_SUB,0,OT_INTC,opd2,ot2);
    }

    $2->nodeType = NT_EXP;
    $$ = $2;
}
;
variant_exp: postfix_exp {
    int pos = $1->num;/*��ñ����ڱ������Ա��е�λ��*/
    int pnum = CompilerUnit.symboltable.GetVarDimen(pos) - ($1->dimen);/*����±�����ĸ���*/
    if($1->dimen < 0){ $1->dimen = 0;/*�ڱ��﷨��������������wstring���͵��±�����*/ }
    if(pnum){
        $1->nodeType = NT_EXP;
        if(!ErrNum)
            CompilerUnit.FormInstruct(OC_IDX,pos,OT_VAR,pnum,OT_INTC);
    }
    $$ = $1;
}
;
postfix_exp: ID {
   /*��������*/
   int pos = CompilerUnit.symboltable.LookupVar(Identifier);
   if(pos < 0){
       ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�����%3δ������ʹ�ã�")
                .arg(@1.first_line).arg(@1.first_column).arg(QString(Identifier));
       CompilerUnit.RecordCompilerInfo(ErrStr);
       ErrNum++;
       YYERROR;
   }
   else{
      int d = CompilerUnit.symboltable.GetVarDimen(pos);
      int t = CompilerUnit.symboltable.GetVarType(pos);
      $$ = CompilerUnit.NewTerminator(NT_VAR,d,t,pos,Identifier);
   }
}
| postfix_exp '[' additive_exp ']' {
    if($1->dimen <= 0){
        if($1->baseType == BT_WSTRING && $1->dimen==0){
            $1->baseType = BT_WCHAR;
        }
        else{
            ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�����%3�±����㳬����ά�ȷ�Χ��")
                     .arg(@1.first_line).arg(@1.first_column).arg(QString($1->str));
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
        }
    }

    if($3->dimen!=0 || $3->baseType!=BT_INT){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�����%3��[]�е��������ǻ������ͣ�")
                 .arg(@1.first_line).arg(@1.first_column).arg(QString($1->str));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    if(!ErrNum){
        if($3->nodeType == NT_CONST)
            CompilerUnit.FormInstruct(OC_PSH,$3->num,$3->baseType,0,OT_STACK);
        if($3->nodeType == NT_VAR)
            CompilerUnit.FormInstruct(OC_PSH,$3->num,OT_VAR,0,OT_STACK);
    }

    $1->dimen -= 1;
    $$ = $1;
}
;
const_exp: 
  INT_CONST {
    /*����ֱֵ�ӷ��ڽڵ���*/
    $$ = CompilerUnit.NewTerminator(NT_CONST,0,BT_INT,$1);
}
| WSTRING_CONST {
    /*�ַ���ֵ�������ַ������������ڵ�ֻ������Ӧ������λ��*/
    WSCArea.append(wstringval);
    $$ = CompilerUnit.NewTerminator(NT_CONST,0,BT_WSTRING,(WSCArea.size()-1));
}
| WCHAR_CONST {
    /*�ַ�ֵ�������ַ����������ڵ�ֻ������Ӧ������λ��*/
    WCCArea.append(wcharval);
    $$ = CompilerUnit.NewTerminator(NT_CONST,0,BT_WCHAR,(WCCArea.size()-1));
}
;



function: FUNNAME {
    /*�ں������в��Һ���*/
    if(!FuncUnit.lookup(Identifier)){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У�����%3���ں������У�")
                 .arg(@1.first_line).arg(@1.first_column).arg(QString(Identifier));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
}funcparam {
      /*�������ĸ����Ƿ�С��Ҫ��ĸ���*/
      if(FuncUnit.attrPtr[0][1] != $3){
          ErrStr = QString::fromLocal8Bit("��%1�е�%2�У���������С�ں���Ҫ��")
                 .arg(@3.first_line).arg(@3.first_column);
          CompilerUnit.RecordCompilerInfo(ErrStr);
          ErrNum++;
          YYERROR;
      }
    if(!ErrNum){
        CompilerUnit.FormInstruct(OC_FUN,FuncUnit.attrPtr[0][0],OT_INTC,$3,OT_INTC);
    }
}
;
funcparam: '(' ')' { $$ = 0; }
| '(' paramlist ')' { $$ = $2; }
;
paramlist: additive_exp {
    int flag = 0;
    /*�����������Ƿ��������Ҫ��*/
    if($1->baseType != FuncUnit.attrPtr[1][1]){
        flag = 1;
        /*�κλ������Ͷ���������Ҫ��*/
        if(FuncUnit.attrPtr[1][1] == BT_UNDEFINE) flag = 0;
    }
    /*��������ά���Ƿ����Ҫ��*/
    if($1->dimen != FuncUnit.attrPtr[1][0]){ flag = 1; }
    if(flag){
            ErrStr = QString::fromLocal8Bit("��%1�е�%2�У���%3����������")
                   .arg(@1.first_line).arg(@1.first_column).arg(1);
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
    }


    if(!ErrNum){
        if($1->nodeType == NT_CONST)
            CompilerUnit.FormInstruct(OC_PSH,$1->num,$1->baseType,0,OT_STACK);
        if($1->nodeType == NT_VAR)
            CompilerUnit.FormInstruct(OC_PSH,$1->num,OT_VAR,0,OT_STACK);
    }
    $$ = 1;
}
| paramlist ',' additive_exp {
    int flag = 0;
    int pos = $1+1;
    /*�������Ƿ����Ҫ��ĸ���*/
    if(pos > FuncUnit.attrPtr[0][1]){
        ErrStr = QString::fromLocal8Bit("��%1�е�%2�У������������ں�����Ҫ�Ĳ�����")
               .arg(@2.first_line).arg(@2.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    /*�����������Ƿ����Ҫ��*/
    if($3->baseType != FuncUnit.attrPtr[pos][1]){
        flag = 1;
        /*�κλ������Ͷ���������Ҫ��*/
        if(FuncUnit.attrPtr[pos][1] == BT_UNDEFINE) flag = 0;
    }
    /*��������ά���Ƿ����Ҫ��*/
    if($3->dimen != FuncUnit.attrPtr[pos][0]){ flag = 1; }
    if(flag){
            ErrStr = QString::fromLocal8Bit("��%1�е�%2�У���%3����������")
                   .arg(@3.first_line).arg(@3.first_column).arg(pos);
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
    }


    if(!ErrNum){
      if($3->nodeType == NT_CONST)
          CompilerUnit.FormInstruct(OC_PSH,$3->num,$3->baseType,0,OT_STACK);
      if($3->nodeType == NT_VAR)
          CompilerUnit.FormInstruct(OC_PSH,$3->num,OT_VAR,0,OT_STACK);
    }
    $$ = pos;
}
;

%%
void yyerror(const char *) { }


