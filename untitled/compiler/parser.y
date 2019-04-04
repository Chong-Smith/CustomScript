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

/* 若需要输出语法分析过程则使用%debug命令，并把yydebug置为1 */
%defines "parser.h"
%output  "parser.cpp"

%{
/*下面两个变量用于保存词法扫描器获得的字符常量值和字符串常量值*/
QChar    wcharval;
QString  wstringval;
void     formWchar(const char* s){ wcharval = QString(s).at(0); }
void     clrWstringval(void){ wstringval.clear(); }
void     formWstring(const char* s){ wstringval.append(s); }



/*嵌套层次变量*/
int  VarLevel;
/*花括号的配对数*/
int  LBraceNum;
/*记录编译过程中产生的错误和警告数目*/
int  &ErrNum = CompilerUnit.ErrorSum;
/*记录声明的类型*/
int  DeclType;


/*用于维护列信息
 *在flex中使用
 *在bison初始化*/
int  yycolumn;
/*上个非终结符的列号*/
int  lastNtermCol;
/*上个非终结符的行号*/
int  lastNtermRow;



/*记录编译过程中发生的错误或者警告信息*/
QString  ErrStr;
/*错误恢复的状态标志*/
int   ErrState;
void  LexError(const QString &err){ ErrNum++; ErrStr = err; CompilerUnit.RecordCompilerInfo(ErrStr);}



/*ID记号及FUNNAME记号返回时，Identifier保存对应的字符串值*/
QByteArray  Identifier;
void  SaveIdentStr(const char *s){ Identifier = QByteArray(s); }



/*记录goup可以跳转到的地址*/
QStack<int>  GUAddr;
/* 记录还没填写地址的godown指令
 * 哈希格式<level,linkhead>
 * 采用拉链法
 * fillbackGD回填地址
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


/*记号可以分配的类型*/
%union{
    int  number;
    struct TNode* TNPtr;
}

/* 声明记号 */
%token INT WSTRING  WCHAR
%token IF  WHILE
%token<number> OPERATOR3  OPERATOR1
%token<number> INT_CONST
%token WSTRING_CONST  WCHAR_CONST
%token ID  FUNNAME
%token AND  OR  GODOWN  GOUP


/*给非终结符设置类型*/
%type<TNPtr>  direct_declarator const_exp unary_exp postfix_exp
%type<TNPtr>  variant_exp mult_exp additive_exp
%type<number> relational_exp logical_and_exp logical_or_exp conditional_exp paramlist funcparam

/*启用默认的位置信息*/
%locations

/*每次yyparse()运行时，先初始化这些变量*/
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

%% /***************** 以下为BNF *******************/
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
     yyerrok;/*跳出错误恢复模式*/
}
;
error_recover:
  err ';' {
    ErrStr = QString::fromLocal8Bit("<错误在;前>\n");
}
| err '{' {
    ErrStr = QString::fromLocal8Bit("<错误在{前>\n");
    yychar = '{';
}
| err '}' {
    if(LBraceNum > 0){
        ErrStr = QString::fromLocal8Bit("<错误在}前>\n");
        yychar = '}';
    }
    else{
        ErrStr = QString::fromLocal8Bit("右花括号没有匹配到对应的括号！\n");
    }
}
| err INT {
    ErrStr = QString::fromLocal8Bit("<错误在关键字int前>\n");
    yychar = INT;
}
| err WCHAR {
    ErrStr = QString::fromLocal8Bit("<错误在关键字wchar前>\n");
    yychar = WCHAR;
}
| err WSTRING {
    ErrStr = QString::fromLocal8Bit("<错误在关键字wstring前>\n");
    yychar = WSTRING;
}
| err IF {
    ErrStr = QString::fromLocal8Bit("<错误在关键字if前>\n");
    yychar = IF;
}
| err WHILE {
    ErrStr = QString::fromLocal8Bit("<错误在关键字while前>\n");
    yychar = WHILE;
}
| err GODOWN {
    ErrStr = QString::fromLocal8Bit("<错误在关键字godown前>\n");
    yychar = GODOWN;
}
| err GOUP {
    ErrStr = QString::fromLocal8Bit("<错误在关键字goup前>\n");
    yychar = GOUP;
}
;
err: error {
    if(ErrNum > 10){
        YYABORT;
    }
    /*在错误恢复状态下，当下个记号不是要求的记号时，会再次进入
     *ErrState就是防止在未遇到要求的记号时，只允许进入一次
    */
    if(!ErrState){
        ErrState = 1;
        if(ErrStr.isEmpty()){
            ErrStr = QString::fromLocal8Bit("%1.%2-%3.%4：存在语法错误！")
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
    /*把变量注册到编译器的符号表中，并得到注册的位置*/
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
    /*把变量注册到编译器的符号表中*/
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
    /*重声明检查*/
    if(CompilerUnit.symboltable.VarConflict(Identifier,VarLevel)){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：符号%3在层次%4中已经存在声明！")
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
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：声明数组%3的维度不能大于2！")
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
        do{/*回填真链*/
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
        do{/*回填假链*/
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
        do{/*回填真链*/
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
        do{/*回填假链*/
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
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：godown的跳转超出了范围或者跳转值为0！")
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
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：goup的跳转超出了范围或者跳转值为0！")
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
            ErrStr = QString::fromLocal8Bit("第%1行第%2列：关系语句中%3操作符两边的比较对象类型不一致！")
                     .arg(@2.first_line).arg(@2.first_column).arg(OCMaptoStr($2));
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
        }
    }
    if($1->dimen!=0 || $3->dimen!=0){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：关系语句中%3操作符两边的比较对象不是基本类型！")
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
            ErrStr = QString::fromLocal8Bit("第%1行第%2列：=两边的操作对象类型不同！")
                     .arg(@2.first_line).arg(@2.first_column);
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
        }
    }
    if($1->dimen!=0 || $3->dimen!=0){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：=两边的操作对象不是基本类型！")
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
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：+的左操作对象必须是基本整型或者基本字符型！")
                 .arg(@2.first_line).arg(@2.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if($3->dimen!=0 || $3->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：+的右操作对象必须是基本整型或者基本字符型！")
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
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：-的左操作对象必须是基本整型或者基本字符型！")
                 .arg(@2.first_line).arg(@2.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if($3->dimen!=0 || $3->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：-的右操作对象必须是基本整型或者基本字符型！")
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
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：%3的左操作对象必须是基本整型或者基本字符型！")
                 .arg(@2.first_line).arg(@2.first_column).arg(OCMaptoStr($2));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if($3->dimen!=0 || $3->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：%3的右操作对象必须是基本整型或者基本字符型！")
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
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：基本整型才可以作负数！")
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
    int pos = $1->num;/*获得变量在变量属性表中的位置*/
    int pnum = CompilerUnit.symboltable.GetVarDimen(pos) - ($1->dimen);/*算出下标参数的个数*/
    if($1->dimen < 0){ $1->dimen = 0;/*在本语法中这种情况针对于wstring类型的下标运算*/ }
    if(pnum){
        $1->nodeType = NT_EXP;
        if(!ErrNum)
            CompilerUnit.FormInstruct(OC_IDX,pos,OT_VAR,pnum,OT_INTC);
    }
    $$ = $1;
}
;
postfix_exp: ID {
   /*检索变量*/
   int pos = CompilerUnit.symboltable.LookupVar(Identifier);
   if(pos < 0){
       ErrStr = QString::fromLocal8Bit("第%1行第%2列：变量%3未声明就使用！")
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
            ErrStr = QString::fromLocal8Bit("第%1行第%2列：变量%3下标运算超出了维度范围！")
                     .arg(@1.first_line).arg(@1.first_column).arg(QString($1->str));
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
        }
    }

    if($3->dimen!=0 || $3->baseType!=BT_INT){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：变量%3的[]中的数必须是基本整型！")
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
    /*整型值直接放在节点里*/
    $$ = CompilerUnit.NewTerminator(NT_CONST,0,BT_INT,$1);
}
| WSTRING_CONST {
    /*字符串值保存在字符串常量区，节点只保留对应的索引位置*/
    WSCArea.append(wstringval);
    $$ = CompilerUnit.NewTerminator(NT_CONST,0,BT_WSTRING,(WSCArea.size()-1));
}
| WCHAR_CONST {
    /*字符值保存在字符常量区，节点只保留对应的索引位置*/
    WCCArea.append(wcharval);
    $$ = CompilerUnit.NewTerminator(NT_CONST,0,BT_WCHAR,(WCCArea.size()-1));
}
;



function: FUNNAME {
    /*在函数库中查找函数*/
    if(!FuncUnit.lookup(Identifier)){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：函数%3不在函数库中！")
                 .arg(@1.first_line).arg(@1.first_column).arg(QString(Identifier));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
}funcparam {
      /*检查参数的个数是否小于要求的个数*/
      if(FuncUnit.attrPtr[0][1] != $3){
          ErrStr = QString::fromLocal8Bit("第%1行第%2列：参数个数小于函数要求！")
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
    /*检查参数类型是否符合类型要求*/
    if($1->baseType != FuncUnit.attrPtr[1][1]){
        flag = 1;
        /*任何基本类型都符合类型要求*/
        if(FuncUnit.attrPtr[1][1] == BT_UNDEFINE) flag = 0;
    }
    /*检查参数的维度是否符合要求*/
    if($1->dimen != FuncUnit.attrPtr[1][0]){ flag = 1; }
    if(flag){
            ErrStr = QString::fromLocal8Bit("第%1行第%2列：第%3个参数错误！")
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
    /*检查参数是否大于要求的个数*/
    if(pos > FuncUnit.attrPtr[0][1]){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：参数个数大于函数需要的参数！")
               .arg(@2.first_line).arg(@2.first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    /*检查参数类型是否符号要求*/
    if($3->baseType != FuncUnit.attrPtr[pos][1]){
        flag = 1;
        /*任何基本类型都符合类型要求*/
        if(FuncUnit.attrPtr[pos][1] == BT_UNDEFINE) flag = 0;
    }
    /*检查参数的维度是否符合要求*/
    if($3->dimen != FuncUnit.attrPtr[pos][0]){ flag = 1; }
    if(flag){
            ErrStr = QString::fromLocal8Bit("第%1行第%2列：第%3个参数错误！")
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


