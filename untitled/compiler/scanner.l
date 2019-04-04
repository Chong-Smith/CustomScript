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
/*标记需要闭合的位置*/
int  closePos;

/*保存位置信息，以便错误查找*/
/*yylineno由flex自动对其进行维护*/
/*yycolumn的初始化放在bison的初始化动作中完成*/
extern int  yycolumn;

/*用于更新位置信息的宏定义*/
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
                            LexError(QString::fromLocal8Bit("第%1行第%2列：%3 ")
                                     .arg(yylineno).arg(yylloc.first_column).arg(QString(yytext)));
                            return 0;
                       }
                       if(yytext[yyleng-1] != '\''){
                            LexError(QString::fromLocal8Bit("第%1行第%2列：%3 ")
                                     .arg(yylineno).arg(yylloc.first_column).arg(QString(yytext)));
                            return 0;
                        }
                       if(yytext[1] == '\n'){ yycolumn = 2;/*因为后面还有个'符号，所有从2开始*/ }
                       formWchar(yytext+1);/*从yytext+1生成的字符是包含了'的*/
                       return WCHAR_CONST;
}




\"                         { BEGIN StringMode;/* 切换到字符串匹配模式 */ clrWstringval(); closePos = yylineno; }
<StringMode>\"             { BEGIN INITIAL; /* 回到正常匹配模式 */ return WSTRING_CONST; }
<StringMode>\n             { yycolumn = 1; }
<StringMode><<EOF>>        {
                             YY_USER_ACTION/*由于匹配到EOF时flex不会自动添加此宏定义，所以手动添加已更新位置信息*/
                             LexError(QString::fromLocal8Bit("第%1行：字符串没有闭合!").arg(closePos));
                             return 0;
}
<StringMode>\\{unicode}    { formWstring(yytext+1); }
<StringMode>{unicode}      { formWstring(yytext); }


"/*"                  { BEGIN CommentMode; closePos = yylineno; /* 切换到注释模式 */ }
<CommentMode>"*/"     { BEGIN INITIAL; /* 回到正常匹配状态 */ }
<CommentMode>\n       {/*换行*/ yycolumn = 1; }
<CommentMode><<EOF>>  {/*遇到终结符，注释模式还未结束*/
                       YY_USER_ACTION/*由于匹配到EOF时flex不会自动添加此宏定义，所以手动添加已更新位置信息*/
                       LexError(QString::fromLocal8Bit("第%1行：注释没有闭合！").arg(closePos));
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

\n                   { /*忽略换行*/ yycolumn = 1; }
[ \t]                { /*忽略空白字符*/ }
<<EOF>>              {
                       YY_USER_ACTION/*由于匹配到EOF时flex不会自动添加此宏定义，所以手动添加已更新位置信息*/
                       if(LBraceNum > 0){
                           LexError(QString::fromLocal8Bit("还有%1个左花括号没被匹配到！").arg(LBraceNum));
                       }
                       return 0;
}
{unicode}            { /*无法的识别字符，可以在此添加报错语句*/
                       LexError(QString::fromLocal8Bit("第%1行第%2列：无法识别的字符：%3")
                                .arg(yylineno).arg(yylloc.first_column).arg(QString(yytext)));
                       return 0;
}

%%
