%{
#include <cstdlib>
#include "public/information.h"
#include "parser.h"


void  formWchar(const char* s);
void  clrWstringval(void);
void  formWstring(const char* s);
void  SaveIdentStr(const char *s);
void  LexError(const QString &err);

extern int  LBraceNum;
/*�����Ҫ�պϵ�λ��*/
int  closePos;

/*����λ����Ϣ���Ա�������*/
/*yylineno��flex�Զ��������ά��*/
/*yycolumn�ĳ�ʼ������bison�ĳ�ʼ�����������*/
extern int  yycolumn;

/*���ڸ���λ����Ϣ�ĺ궨��*/
#define YY_USER_ACTION  yylloc.first_line = yylloc.last_line = yylineno;\
    yylloc.first_column = yycolumn;\
    if(yytext[0] & 0x80){ yylloc.last_column = yycolumn; yycolumn += 1; }\
    else{ yylloc.last_column = yycolumn+yyleng-1; yycolumn += yyleng; }

int   yylex();
void  yyerror(const char *);

%}

%option header-file="scanner.h"
%option outfile="scanner.cpp"

%option noyywrap
%option nounput
%option yylineno

%x StringMode
%x CommentMode

ASC      [\x00-\x7f]
U        [\x80-\xbf]
U2       [\xc0-\xdf]
U3       [\xe0-\xef]
unicode  {ASC}|{U2}{U}|{U3}{U}{U}

%%       
[1-9][0-9]*|0        { yylval.number = atoi(yytext); return INT_CONST;}
"int"                { return INT; }
"wstring"            { return WSTRING; }
"wchar"              { return WCHAR; }
"if"                 { return IF; }
"while"              { return WHILE; }
"godown"             { return GODOWN; }
"goup"               { return GOUP; }
f[us]_[a-zA-Z][a-zA-Z0-9]* { SaveIdentStr(yytext); return FUNNAME; }
[a-zA-Z][a-zA-Z0-9]*       { SaveIdentStr(yytext); return ID; }




\'{unicode}{0,2}     { if(yyleng <= 2){
                            LexError(QString::fromLocal8Bit("��%1�е�%2�У�%3 ")
                                     .arg(yylineno).arg(yylloc.first_column).arg(QString(yytext)));
                            return 0;
                       }
                       if(yytext[yyleng-1] != '\''){
                            LexError(QString::fromLocal8Bit("��%1�е�%2�У�%3 ")
                                     .arg(yylineno).arg(yylloc.first_column).arg(QString(yytext)));
                            return 0;
                        }
                       if(yytext[1] == '\n'){ yycolumn = 2;/*��Ϊ���滹�и�'���ţ����д�2��ʼ*/ }
                       formWchar(yytext+1);/*��yytext+1���ɵ��ַ��ǰ�����'��*/
                       return WCHAR_CONST;
}




\"                         { BEGIN StringMode;/* �л����ַ���ƥ��ģʽ */ clrWstringval(); closePos = yylineno; }
<StringMode>\"             { BEGIN INITIAL; /* �ص�����ƥ��ģʽ */ return WSTRING_CONST; }
<StringMode>\n             { yycolumn = 1; }
<StringMode><<EOF>>        {
                             YY_USER_ACTION/*����ƥ�䵽EOFʱflex�����Զ����Ӵ˺궨�壬�����ֶ������Ѹ���λ����Ϣ*/
                             LexError(QString::fromLocal8Bit("��%1�У��ַ���û�бպ�!").arg(closePos));
                             return 0;
}
<StringMode>\\{unicode}    { formWstring(yytext+1); }
<StringMode>{unicode}      { formWstring(yytext); }


"/*"                  { BEGIN CommentMode; closePos = yylineno; /* �л���ע��ģʽ */ }
<CommentMode>"*/"     { BEGIN INITIAL; /* �ص�����ƥ��״̬ */ }
<CommentMode>\n       {/*����*/ yycolumn = 1; }
<CommentMode><<EOF>>  {/*�����ս����ע��ģʽ��δ����*/
                       YY_USER_ACTION/*����ƥ�䵽EOFʱflex�����Զ����Ӵ˺궨�壬�����ֶ������Ѹ���λ����Ϣ*/
                       LexError(QString::fromLocal8Bit("��%1�У�ע��û�бպϣ�").arg(closePos));
                       return 0;
}
<CommentMode>.


"<="                 { yylval.number =OC_LE;  return OPERATOR1; }
">="                 { yylval.number =OC_GE;  return OPERATOR1; }
"=="                 { yylval.number =OC_JE;  return OPERATOR1; }
"!="                 { yylval.number =OC_JNE; return OPERATOR1; }
">"                  { yylval.number =OC_GT;  return OPERATOR1; }
"<"                  { yylval.number =OC_LT;  return OPERATOR1; }
"&&"                 { return AND; }
"||"                 { return OR; }

"+"|"-"              { return *yytext; }
"*"|"/"|"%"          { yylval.number =(int)(*yytext); return OPERATOR3; }

","|";"|":"|"("|")"|"["|"]"|"="|"{"|"}" { return *yytext; }

\n                   { /*���Ի���*/ yycolumn = 1; }
[ \t]                { /*���Կհ��ַ�*/ }
<<EOF>>              {
                       YY_USER_ACTION/*����ƥ�䵽EOFʱflex�����Զ����Ӵ˺궨�壬�����ֶ������Ѹ���λ����Ϣ*/
                       if(LBraceNum > 0){
                           LexError(QString::fromLocal8Bit("����%1��������û��ƥ�䵽��").arg(LBraceNum));
                       }
                       return 0;
}
{unicode}            { /*�޷���ʶ���ַ��������ڴ����ӱ������*/
                       LexError(QString::fromLocal8Bit("��%1�е�%2�У��޷�ʶ����ַ���%3")
                                .arg(yylineno).arg(yylloc.first_column).arg(QString(yytext)));
                       return 0;
}

%%