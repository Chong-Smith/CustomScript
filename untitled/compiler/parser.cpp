/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "parser.y"

#include <QDebug>
#include <QByteArray>
#include <QStack>
#include <QHash>
#include <QChar>
#include <QString>
#include "public/information.h"
#include "compiler/compiler.h"
#include "function/function.h"

/* Line 371 of yacc.c  */
#line 18 "parser.y"

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

/* Line 371 of yacc.c  */
#line 154 "parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     WSTRING = 259,
     WCHAR = 260,
     IF = 261,
     WHILE = 262,
     OPERATOR3 = 263,
     OPERATOR1 = 264,
     INT_CONST = 265,
     WSTRING_CONST = 266,
     WCHAR_CONST = 267,
     ID = 268,
     FUNNAME = 269,
     AND = 270,
     OR = 271,
     GODOWN = 272,
     GOUP = 273
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 93 "parser.y"

    int  number;
    struct TNode* TNPtr;


/* Line 387 of yacc.c  */
#line 221 "parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 262 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNRULES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   273

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      25,    26,     2,    29,    22,    30,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    27,    19,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    23,     2,    24,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    20,     2,    21,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    13,    15,    17,
      20,    23,    26,    29,    32,    35,    38,    41,    44,    47,
      49,    53,    55,    57,    59,    61,    65,    67,    72,    74,
      76,    79,    82,    85,    86,    91,    92,    93,   103,   104,
     105,   115,   119,   123,   125,   127,   131,   133,   137,   141,
     145,   149,   151,   155,   159,   161,   165,   167,   171,   173,
     176,   178,   180,   185,   187,   189,   191,   192,   196,   199,
     203,   205
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    -1,    33,    -1,    34,    -1,    33,    34,
      -1,    37,    -1,    41,    -1,    35,    -1,    36,    19,    -1,
      36,    20,    -1,    36,    21,    -1,    36,     3,    -1,    36,
       5,    -1,    36,     4,    -1,    36,     6,    -1,    36,     7,
      -1,    36,    17,    -1,    36,    18,    -1,     1,    -1,    38,
      39,    19,    -1,     3,    -1,     5,    -1,     4,    -1,    40,
      -1,    39,    22,    40,    -1,    13,    -1,    40,    23,    10,
      24,    -1,    42,    -1,    44,    -1,    49,    19,    -1,    54,
      19,    -1,    61,    19,    -1,    -1,    20,    43,    32,    21,
      -1,    -1,    -1,     6,    25,    45,    50,    26,    20,    46,
      32,    21,    -1,    -1,    -1,     7,    25,    47,    50,    26,
      20,    48,    32,    21,    -1,    17,    27,    10,    -1,    18,
      27,    10,    -1,    51,    -1,    52,    -1,    51,    16,    52,
      -1,    53,    -1,    52,    15,    53,    -1,    55,     9,    55,
      -1,    25,    51,    26,    -1,    58,    28,    55,    -1,    56,
      -1,    55,    29,    56,    -1,    55,    30,    56,    -1,    57,
      -1,    56,     8,    57,    -1,    58,    -1,    25,    55,    26,
      -1,    60,    -1,    30,    57,    -1,    59,    -1,    13,    -1,
      59,    23,    55,    24,    -1,    10,    -1,    11,    -1,    12,
      -1,    -1,    14,    62,    63,    -1,    25,    26,    -1,    25,
      64,    26,    -1,    55,    -1,    64,    22,    55,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   133,   133,   134,   136,   142,   150,   151,   152,   160,
     163,   167,   176,   180,   184,   188,   192,   196,   200,   205,
     224,   227,   228,   229,   231,   248,   266,   279,   294,   295,
     296,   297,   298,   300,   300,   315,   317,   315,   346,   348,
     346,   381,   401,   415,   417,   418,   433,   434,   450,   478,
     480,   508,   509,   534,   560,   561,   588,   589,   590,   591,
     609,   621,   637,   671,   675,   680,   689,   689,   712,   713,
     715,   742
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "WSTRING", "WCHAR", "IF", "WHILE",
  "OPERATOR3", "OPERATOR1", "INT_CONST", "WSTRING_CONST", "WCHAR_CONST",
  "ID", "FUNNAME", "AND", "OR", "GODOWN", "GOUP", "';'", "'{'", "'}'",
  "','", "'['", "']'", "'('", "')'", "':'", "'='", "'+'", "'-'", "$accept",
  "fragment", "program_list", "program", "error_recover", "err", "decl",
  "type_spec", "init_declarator_list", "direct_declarator", "stat",
  "compound_stat", "$@1", "conditional_stat", "$@2", "$@3", "$@4", "$@5",
  "jump_stat", "conditional_exp", "logical_or_exp", "logical_and_exp",
  "relational_exp", "assignment_exp", "additive_exp", "mult_exp",
  "unary_exp", "variant_exp", "postfix_exp", "const_exp", "function",
  "$@6", "funcparam", "paramlist", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    59,
     123,   125,    44,    91,    93,    40,    41,    58,    61,    43,
      45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    32,    33,    33,    34,    34,    34,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    36,
      37,    38,    38,    38,    39,    39,    40,    40,    41,    41,
      41,    41,    41,    43,    42,    45,    46,    44,    47,    48,
      44,    49,    49,    50,    51,    51,    52,    52,    53,    53,
      54,    55,    55,    55,    56,    56,    57,    57,    57,    57,
      58,    59,    59,    60,    60,    60,    62,    61,    63,    63,
      64,    64
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       3,     1,     1,     1,     1,     3,     1,     4,     1,     1,
       2,     2,     2,     0,     4,     0,     0,     9,     0,     0,
       9,     3,     3,     1,     1,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     2,
       1,     1,     4,     1,     1,     1,     0,     3,     2,     3,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    19,    21,    23,    22,     0,     0,    61,    66,     0,
       0,    33,     0,     0,     4,     8,     0,     6,     0,     7,
      28,    29,     0,     0,     0,    60,     0,    35,    38,     0,
       0,     0,     0,     1,     5,    12,    14,    13,    15,    16,
      17,    18,     9,    10,    11,    26,     0,    24,    30,    31,
       0,     0,    32,     0,     0,     0,    67,    41,    42,     0,
      20,     0,     0,    63,    64,    65,     0,     0,    50,    51,
      54,    56,    58,     0,     0,     0,    43,    44,    46,     0,
       0,    68,    70,     0,    34,    25,     0,     0,    59,     0,
       0,     0,    62,     0,     0,     0,     0,     0,     0,     0,
       0,    69,    27,    57,    52,    53,    55,    49,    36,    45,
      47,    48,    39,    71,     0,     0,     0,     0,    37,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,    17,    18,    46,    47,
      19,    20,    32,    21,    53,   114,    54,   115,    22,    75,
      76,    77,    78,    23,    79,    69,    70,    71,    25,    72,
      26,    29,    56,    83
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -64
static const yytype_int8 yypact[] =
{
      53,   -64,   -64,   -64,   -64,     6,    17,   -64,   -64,    -2,
      19,   -64,    49,    16,   -64,   -64,   124,   -64,    38,   -64,
     -64,   -64,    36,    44,    37,    41,    50,   -64,   -64,    43,
      62,    65,    73,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,    21,    58,   -64,   -64,
      92,    92,   -64,    96,    96,    86,   -64,   -64,   -64,    61,
     -64,    38,    75,   -64,   -64,   -64,    92,    92,   -21,    80,
     -64,   -64,   -64,   -18,    96,    63,    76,    85,   -64,    18,
      69,   -64,   -21,   -12,   -64,    58,    77,     9,   -64,    92,
      92,    92,   -64,   -11,    15,    90,    96,    96,    92,    93,
      92,   -64,   -64,   -64,    80,    80,   -64,   -64,   -64,    85,
     -64,   -21,   -64,   -21,    73,    73,    97,    98,   -64,   -64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -64,   -31,   -64,   107,   -64,   -64,   -64,   -64,   -64,    64,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,    70,
      59,    27,    35,   -64,   -48,   -28,   -63,     0,   -64,   -64,
     -64,   -64,   -64,   -64
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const yytype_int8 yytable[] =
{
      24,    59,    68,    73,    88,    96,    92,    82,    89,    90,
     100,    89,    90,    24,   101,   107,    -3,     1,    87,     2,
       3,     4,     5,     6,    98,    30,    94,    98,   106,     7,
       8,    27,    24,     9,    10,   103,    11,    -3,    89,    90,
      60,   103,    28,    61,    89,    90,    31,    89,    90,    33,
     111,    45,   113,    -2,     1,    48,     2,     3,     4,     5,
       6,   104,   105,    49,    51,    50,     7,     8,    55,    52,
       9,    10,    57,    11,     1,    58,     2,     3,     4,     5,
       6,    62,    84,   116,   117,    86,     7,     8,    91,    95,
       9,    10,    96,    11,    -2,    99,    63,    64,    65,     7,
      97,   102,    63,    64,    65,     7,    63,    64,    65,     7,
     108,    66,    81,   112,    24,    24,    67,    66,   118,   119,
      34,    74,    67,   109,    80,    85,    67,    35,    36,    37,
      38,    39,   110,    93,     0,     0,     0,     0,     0,     0,
       0,    40,    41,    42,    43,    44
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-64)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       0,    32,    50,    51,    67,    16,    24,    55,    29,    30,
      22,    29,    30,    13,    26,    26,     0,     1,    66,     3,
       4,     5,     6,     7,     9,    27,    74,     9,    91,    13,
      14,    25,    32,    17,    18,    26,    20,    21,    29,    30,
      19,    26,    25,    22,    29,    30,    27,    29,    30,     0,
      98,    13,   100,     0,     1,    19,     3,     4,     5,     6,
       7,    89,    90,    19,    23,    28,    13,    14,    25,    19,
      17,    18,    10,    20,     1,    10,     3,     4,     5,     6,
       7,    23,    21,   114,   115,    10,    13,    14,     8,    26,
      17,    18,    16,    20,    21,    26,    10,    11,    12,    13,
      15,    24,    10,    11,    12,    13,    10,    11,    12,    13,
      20,    25,    26,    20,   114,   115,    30,    25,    21,    21,
      13,    25,    30,    96,    54,    61,    30,     3,     4,     5,
       6,     7,    97,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,    13,    14,    17,
      18,    20,    32,    33,    34,    35,    36,    37,    38,    41,
      42,    44,    49,    54,    58,    59,    61,    25,    25,    62,
      27,    27,    43,     0,    34,     3,     4,     5,     6,     7,
      17,    18,    19,    20,    21,    13,    39,    40,    19,    19,
      28,    23,    19,    45,    47,    25,    63,    10,    10,    32,
      19,    22,    23,    10,    11,    12,    25,    30,    55,    56,
      57,    58,    60,    55,    25,    50,    51,    52,    53,    55,
      50,    26,    55,    64,    21,    40,    10,    55,    57,    29,
      30,     8,    24,    51,    55,    26,    16,    15,     9,    26,
      22,    26,    24,    26,    56,    56,    57,    26,    20,    52,
      53,    55,    20,    55,    46,    48,    32,    32,    21,    21
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;


/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
/* Line 1575 of yacc.c  */
#line 117 "parser.y"
{
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
/* Line 1575 of yacc.c  */
#line 1515 "parser.cpp"
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
/* Line 1792 of yacc.c  */
#line 136 "parser.y"
    {
    lastNtermRow = (yylsp[(1) - (1)]).last_line;
    lastNtermCol = (yylsp[(1) - (1)]).last_column;

    CompilerUnit.ClearTerminators();
}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 142 "parser.y"
    {
    lastNtermRow = (yylsp[(2) - (2)]).last_line;
    lastNtermCol = (yylsp[(2) - (2)]).last_column;

    CompilerUnit.ClearTerminators();
}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 152 "parser.y"
    {
     CompilerUnit.RecordCompilerInfo(ErrStr);
     ErrStr.clear();
     ErrState = 0;
     yyerrok;/*跳出错误恢复模式*/
}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 160 "parser.y"
    {
    ErrStr = QString::fromLocal8Bit("<错误在;前>\n");
}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 163 "parser.y"
    {
    ErrStr = QString::fromLocal8Bit("<错误在{前>\n");
    yychar = '{';
}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 167 "parser.y"
    {
    if(LBraceNum > 0){
        ErrStr = QString::fromLocal8Bit("<错误在}前>\n");
        yychar = '}';
    }
    else{
        ErrStr = QString::fromLocal8Bit("右花括号没有匹配到对应的括号！\n");
    }
}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 176 "parser.y"
    {
    ErrStr = QString::fromLocal8Bit("<错误在关键字int前>\n");
    yychar = INT;
}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 180 "parser.y"
    {
    ErrStr = QString::fromLocal8Bit("<错误在关键字wchar前>\n");
    yychar = WCHAR;
}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 184 "parser.y"
    {
    ErrStr = QString::fromLocal8Bit("<错误在关键字wstring前>\n");
    yychar = WSTRING;
}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 188 "parser.y"
    {
    ErrStr = QString::fromLocal8Bit("<错误在关键字if前>\n");
    yychar = IF;
}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 192 "parser.y"
    {
    ErrStr = QString::fromLocal8Bit("<错误在关键字while前>\n");
    yychar = WHILE;
}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 196 "parser.y"
    {
    ErrStr = QString::fromLocal8Bit("<错误在关键字godown前>\n");
    yychar = GODOWN;
}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 200 "parser.y"
    {
    ErrStr = QString::fromLocal8Bit("<错误在关键字goup前>\n");
    yychar = GOUP;
}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 205 "parser.y"
    {
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
                    .arg(lastNtermRow).arg(lastNtermCol).arg((yylsp[(1) - (1)]).last_line).arg((yylsp[(1) - (1)]).last_column);
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
        }
        ErrStr.clear();
    }
}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 227 "parser.y"
    { DeclType = BT_INT; }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 228 "parser.y"
    { DeclType = BT_WCHAR; }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 229 "parser.y"
    { DeclType = BT_WSTRING; }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 231 "parser.y"
    {
    /*把变量注册到编译器的符号表中，并得到注册的位置*/
    int pos = CompilerUnit.symboltable.RegisterSym((yyvsp[(1) - (1)].TNPtr)->str,(yyvsp[(1) - (1)].TNPtr)->dimen,(yyvsp[(1) - (1)].TNPtr)->baseType,VarLevel);
    if(!ErrNum){
        switch ((yyvsp[(1) - (1)].TNPtr)->baseType) {
        case BT_INT:
             CompilerUnit.FormInstruct(OC_INT,(yyvsp[(1) - (1)].TNPtr)->dimen,OT_INTC,pos,OT_INTC);
            break;
        case BT_WCHAR:
             CompilerUnit.FormInstruct(OC_WCHAR,(yyvsp[(1) - (1)].TNPtr)->dimen,OT_INTC,pos,OT_INTC);
            break;
        case BT_WSTRING:
             CompilerUnit.FormInstruct(OC_WSTRING,(yyvsp[(1) - (1)].TNPtr)->dimen,OT_INTC,pos,OT_INTC);
            break;
        }
    }
}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 248 "parser.y"
    {
    /*把变量注册到编译器的符号表中*/
    int pos = CompilerUnit.symboltable.RegisterSym((yyvsp[(3) - (3)].TNPtr)->str,(yyvsp[(3) - (3)].TNPtr)->dimen,(yyvsp[(3) - (3)].TNPtr)->baseType,VarLevel);
    if(!ErrNum){
        switch ((yyvsp[(3) - (3)].TNPtr)->baseType) {
        case BT_INT:
             CompilerUnit.FormInstruct(OC_INT,(yyvsp[(3) - (3)].TNPtr)->dimen,OT_INTC,pos,OT_INTC);
          break;
        case BT_WCHAR:
             CompilerUnit.FormInstruct(OC_WCHAR,(yyvsp[(3) - (3)].TNPtr)->dimen,OT_INTC,pos,OT_INTC);
          break;
        case BT_WSTRING:
             CompilerUnit.FormInstruct(OC_WSTRING,(yyvsp[(3) - (3)].TNPtr)->dimen,OT_INTC,pos,OT_INTC);
          break;
        }
    }
}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 266 "parser.y"
    {
    /*重声明检查*/
    if(CompilerUnit.symboltable.VarConflict(Identifier,VarLevel)){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：符号%3在层次%4中已经存在声明！")
                 .arg((yylsp[(1) - (1)]).first_line).arg((yylsp[(1) - (1)]).first_column).arg(QString(Identifier)).arg(VarLevel);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    else{
        (yyval.TNPtr) = CompilerUnit.NewTerminator(NT_DECL,0,DeclType,Identifier);
    }
}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 279 "parser.y"
    {
    if((yyvsp[(1) - (4)].TNPtr)->dimen >= 2 ){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：声明数组%3的维度不能大于2！")
                 .arg((yylsp[(2) - (4)]).first_line).arg((yylsp[(2) - (4)]).first_column).arg(QString((yyvsp[(1) - (4)].TNPtr)->str));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        CompilerUnit.FormInstruct(OC_PSH,(yyvsp[(3) - (4)].number),OT_INTC,0,OT_STACK);
    }
    (yyvsp[(1) - (4)].TNPtr)->dimen++;
    (yyval.TNPtr) = (yyvsp[(1) - (4)].TNPtr);
}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 300 "parser.y"
    {
    GUAddr.push(CompilerUnit.InstructNum());
    VarLevel++;
    LBraceNum++;
}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 304 "parser.y"
    {
    GUAddr.pop();
    CompilerUnit.symboltable.DeleteLevel(VarLevel);
    VarLevel--;
    LBraceNum--;
    if(!ErrNum){
        fillbackGD(VarLevel,CompilerUnit.InstructNum());
    }
}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 315 "parser.y"
    {
    GUAddr.push(CompilerUnit.InstructNum());
}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 317 "parser.y"
    {
    VarLevel++;    
    LBraceNum++;
    if(!ErrNum){
        int pos = (yyvsp[(4) - (6)].number);
        instruct* I;
        do{/*回填真链*/
            I = CompilerUnit.GetInstruct(pos);
            pos = I->Operand1;
            I->Operand1 = (yyvsp[(4) - (6)].number)+1;
        }while(pos >= 0);
    }
}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 329 "parser.y"
    {
    GUAddr.pop();
    CompilerUnit.symboltable.DeleteLevel(VarLevel);
    VarLevel--;    
    LBraceNum--;
    if(!ErrNum){
        int falsepos = CompilerUnit.InstructNum();
        int index = (yyvsp[(4) - (9)].number);
        instruct* I;
        do{/*回填假链*/
            I = CompilerUnit.GetInstruct(index);
            index = I->Operand2;
            I->Operand2 = falsepos;
        }while(index >= 0);
        fillbackGD(VarLevel,falsepos);
    }
}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 346 "parser.y"
    {
    GUAddr.push(CompilerUnit.InstructNum());
}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 348 "parser.y"
    {
    VarLevel++;
    LBraceNum++;
    if(!ErrNum){
        int pos = (yyvsp[(4) - (6)].number);
        instruct* I;
        do{/*回填真链*/
            I = CompilerUnit.GetInstruct(pos);
            pos = I->Operand1;
            I->Operand1 = (yyvsp[(4) - (6)].number)+1;
        }while(pos >= 0);
    }
}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 360 "parser.y"
    {
    if(!ErrNum){
        CompilerUnit.FormInstruct(OC_GO,GUAddr.top(),OT_INTC,0,OT_INTC);
    }
    GUAddr.pop();
    CompilerUnit.symboltable.DeleteLevel(VarLevel);
    VarLevel--;
    LBraceNum--;
    if(!ErrNum){
        int falsepos = CompilerUnit.InstructNum();
        int index = (yyvsp[(4) - (9)].number);
        instruct* I;
        do{/*回填假链*/
            I = CompilerUnit.GetInstruct(index);
            index = I->Operand2;
            I->Operand2 = falsepos;
        }while(index >= 0);
        fillbackGD(VarLevel,falsepos);
    }
}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 381 "parser.y"
    {
    int pos = VarLevel - (yyvsp[(3) - (3)].number);
    if(pos < 0 || (yyvsp[(3) - (3)].number) == 0){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：godown的跳转超出了范围或者跳转值为0！")
                 .arg((yylsp[(3) - (3)]).first_line).arg((yylsp[(3) - (3)]).first_column);
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
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 401 "parser.y"
    {
    int pos = VarLevel - (yyvsp[(3) - (3)].number);
    if(pos < 0 || (yyvsp[(3) - (3)].number) == 0){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：goup的跳转超出了范围或者跳转值为0！")
                 .arg((yylsp[(3) - (3)]).first_line).arg((yylsp[(3) - (3)]).first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        CompilerUnit.FormInstruct(OC_GO,GUAddr.at(pos),OT_INTC,0,OT_INTC);
    }
}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 415 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (1)].number); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 417 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (1)].number); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 418 "parser.y"
    {
    if(!ErrNum){
        int pos = (yyvsp[(1) - (3)].number);
        instruct* I;
        do{
            I = CompilerUnit.GetInstruct(pos);
            pos = I->Operand2;
            I->Operand2 = (yyvsp[(1) - (3)].number)+1;
        }while(pos >= 0);
        I = CompilerUnit.GetInstruct((yyvsp[(3) - (3)].number));
        I->Operand1 = (yyvsp[(1) - (3)].number);
        (yyval.number) = (yyvsp[(3) - (3)].number);
    }
}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 433 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (1)].number); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 434 "parser.y"
    {
    if(!ErrNum){
        int pos = (yyvsp[(1) - (3)].number);
        instruct* I;
        do{
            I = CompilerUnit.GetInstruct(pos);
            pos = I->Operand1;
            I->Operand1 = (yyvsp[(1) - (3)].number)+1;
        }while(pos >= 0);
        I = CompilerUnit.GetInstruct((yyvsp[(3) - (3)].number));
        I->Operand2 = (yyvsp[(1) - (3)].number);
        (yyval.number) = (yyvsp[(3) - (3)].number);
    }
}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 450 "parser.y"
    {
    int  t1 = (yyvsp[(1) - (3)].TNPtr)->baseType;
    int  t3 = (yyvsp[(3) - (3)].TNPtr)->baseType;
    if(t1 != t3){
        if((t1==BT_INT && t3==BT_WCHAR)||(t1==BT_WCHAR && t3==BT_INT)){}
        else{
            ErrStr = QString::fromLocal8Bit("第%1行第%2列：关系语句中%3操作符两边的比较对象类型不一致！")
                     .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column).arg(OCMaptoStr((yyvsp[(2) - (3)].number)));
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
        }
    }
    if((yyvsp[(1) - (3)].TNPtr)->dimen!=0 || (yyvsp[(3) - (3)].TNPtr)->dimen!=0){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：关系语句中%3操作符两边的比较对象不是基本类型！")
                 .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column).arg(OCMaptoStr((yyvsp[(2) - (3)].number)));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        int opd1, ot1, opd2, ot2;
        CompilerUnit.GetOpdandOT((yyvsp[(1) - (3)].TNPtr),opd1,ot1);
        CompilerUnit.GetOpdandOT((yyvsp[(3) - (3)].TNPtr),opd2,ot2);
        CompilerUnit.FormInstruct((yyvsp[(2) - (3)].number),opd1,ot1,opd2,ot2);
        (yyval.number) = CompilerUnit.FormInstruct(OC_IGO,-1,OT_INTC,-1,OT_INTC);
    }
}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 478 "parser.y"
    { (yyval.number) = (yyvsp[(2) - (3)].number); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 480 "parser.y"
    {
    int t1 = (yyvsp[(1) - (3)].TNPtr)->baseType;
    int t3 = (yyvsp[(3) - (3)].TNPtr)->baseType;
    if(t1 != t3){
        if((t1==BT_INT && t3==BT_WCHAR)||(t3==BT_INT && t1==BT_WCHAR)){}
        else{
            ErrStr = QString::fromLocal8Bit("第%1行第%2列：=两边的操作对象类型不同！")
                     .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column);
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
        }
    }
    if((yyvsp[(1) - (3)].TNPtr)->dimen!=0 || (yyvsp[(3) - (3)].TNPtr)->dimen!=0){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：=两边的操作对象不是基本类型！")
                 .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        int opd1, ot1, opd2, ot2;
        CompilerUnit.GetOpdandOT((yyvsp[(1) - (3)].TNPtr),opd1,ot1);
        CompilerUnit.GetOpdandOT((yyvsp[(3) - (3)].TNPtr),opd2,ot2);
        CompilerUnit.FormInstruct(OC_ASS,opd1,ot1,opd2,ot2);
    }
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 508 "parser.y"
    { (yyval.TNPtr) = (yyvsp[(1) - (1)].TNPtr); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 509 "parser.y"
    {
    if((yyvsp[(1) - (3)].TNPtr)->dimen!=0 || (yyvsp[(1) - (3)].TNPtr)->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：+的左操作对象必须是基本整型或者基本字符型！")
                 .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if((yyvsp[(3) - (3)].TNPtr)->dimen!=0 || (yyvsp[(3) - (3)].TNPtr)->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：+的右操作对象必须是基本整型或者基本字符型！")
                 .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    if(!ErrNum){
        int opd1, ot1, opd2, ot2;
        CompilerUnit.GetOpdandOT((yyvsp[(1) - (3)].TNPtr),opd1,ot1);
        CompilerUnit.GetOpdandOT((yyvsp[(3) - (3)].TNPtr),opd2,ot2);
        CompilerUnit.FormInstruct(OC_ADD,opd1,ot1,opd2,ot2);
    }
    (yyvsp[(1) - (3)].TNPtr)->nodeType = NT_EXP;
    (yyval.TNPtr) = (yyvsp[(1) - (3)].TNPtr);
}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 534 "parser.y"
    {
    if((yyvsp[(1) - (3)].TNPtr)->dimen!=0 || (yyvsp[(1) - (3)].TNPtr)->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：-的左操作对象必须是基本整型或者基本字符型！")
                 .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if((yyvsp[(3) - (3)].TNPtr)->dimen!=0 || (yyvsp[(3) - (3)].TNPtr)->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：-的右操作对象必须是基本整型或者基本字符型！")
                 .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    if(!ErrNum){
        int opd1, ot1, opd2, ot2;
        CompilerUnit.GetOpdandOT((yyvsp[(1) - (3)].TNPtr),opd1,ot1);
        CompilerUnit.GetOpdandOT((yyvsp[(3) - (3)].TNPtr),opd2,ot2);
        CompilerUnit.FormInstruct(OC_SUB,opd1,ot1,opd2,ot2);
    }
    (yyvsp[(1) - (3)].TNPtr)->nodeType = NT_EXP;
    (yyval.TNPtr) = (yyvsp[(1) - (3)].TNPtr);
}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 560 "parser.y"
    { (yyval.TNPtr) = (yyvsp[(1) - (1)].TNPtr); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 561 "parser.y"
    {
    if((yyvsp[(1) - (3)].TNPtr)->dimen!=0 || (yyvsp[(1) - (3)].TNPtr)->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：%3的左操作对象必须是基本整型或者基本字符型！")
                 .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column).arg(OCMaptoStr((yyvsp[(2) - (3)].number)));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if((yyvsp[(3) - (3)].TNPtr)->dimen!=0 || (yyvsp[(3) - (3)].TNPtr)->baseType==BT_WSTRING){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：%3的右操作对象必须是基本整型或者基本字符型！")
                 .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column).arg(OCMaptoStr((yyvsp[(2) - (3)].number)));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    if(!ErrNum){
        int opd1, ot1;
        int opd2, ot2;
        CompilerUnit.GetOpdandOT((yyvsp[(1) - (3)].TNPtr),opd1,ot1);
        CompilerUnit.GetOpdandOT((yyvsp[(3) - (3)].TNPtr),opd2,ot2);
        CompilerUnit.FormInstruct((yyvsp[(2) - (3)].number),opd1,ot1,opd2,ot2);
    }
    (yyvsp[(1) - (3)].TNPtr)->nodeType = NT_EXP;
    (yyval.TNPtr) = (yyvsp[(1) - (3)].TNPtr);
}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 588 "parser.y"
    { (yyval.TNPtr) = (yyvsp[(1) - (1)].TNPtr); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 589 "parser.y"
    { (yyval.TNPtr) = (yyvsp[(2) - (3)].TNPtr); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 590 "parser.y"
    { (yyval.TNPtr) = (yyvsp[(1) - (1)].TNPtr); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 591 "parser.y"
    {
    if((yyvsp[(2) - (2)].TNPtr)->dimen!=0 || (yyvsp[(2) - (2)].TNPtr)->baseType!=BT_INT){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：基本整型才可以作负数！")
                 .arg((yylsp[(2) - (2)]).first_line).arg((yylsp[(2) - (2)]).first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
    if(!ErrNum){
        int opd2, ot2;
        CompilerUnit.GetOpdandOT((yyvsp[(2) - (2)].TNPtr),opd2,ot2);
        CompilerUnit.FormInstruct(OC_SUB,0,OT_INTC,opd2,ot2);
    }

    (yyvsp[(2) - (2)].TNPtr)->nodeType = NT_EXP;
    (yyval.TNPtr) = (yyvsp[(2) - (2)].TNPtr);
}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 609 "parser.y"
    {
    int pos = (yyvsp[(1) - (1)].TNPtr)->num;/*获得变量在变量属性表中的位置*/
    int pnum = CompilerUnit.symboltable.GetVarDimen(pos) - ((yyvsp[(1) - (1)].TNPtr)->dimen);/*算出下标参数的个数*/
    if((yyvsp[(1) - (1)].TNPtr)->dimen < 0){ (yyvsp[(1) - (1)].TNPtr)->dimen = 0;/*在本语法中这种情况针对于wstring类型的下标运算*/ }
    if(pnum){
        (yyvsp[(1) - (1)].TNPtr)->nodeType = NT_EXP;
        if(!ErrNum)
            CompilerUnit.FormInstruct(OC_IDX,pos,OT_VAR,pnum,OT_INTC);
    }
    (yyval.TNPtr) = (yyvsp[(1) - (1)].TNPtr);
}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 621 "parser.y"
    {
   /*检索变量*/
   int pos = CompilerUnit.symboltable.LookupVar(Identifier);
   if(pos < 0){
       ErrStr = QString::fromLocal8Bit("第%1行第%2列：变量%3未声明就使用！")
                .arg((yylsp[(1) - (1)]).first_line).arg((yylsp[(1) - (1)]).first_column).arg(QString(Identifier));
       CompilerUnit.RecordCompilerInfo(ErrStr);
       ErrNum++;
       YYERROR;
   }
   else{
      int d = CompilerUnit.symboltable.GetVarDimen(pos);
      int t = CompilerUnit.symboltable.GetVarType(pos);
      (yyval.TNPtr) = CompilerUnit.NewTerminator(NT_VAR,d,t,pos,Identifier);
   }
}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 637 "parser.y"
    {
    if((yyvsp[(1) - (4)].TNPtr)->dimen <= 0){
        if((yyvsp[(1) - (4)].TNPtr)->baseType == BT_WSTRING && (yyvsp[(1) - (4)].TNPtr)->dimen==0){
            (yyvsp[(1) - (4)].TNPtr)->baseType = BT_WCHAR;
        }
        else{
            ErrStr = QString::fromLocal8Bit("第%1行第%2列：变量%3下标运算超出了维度范围！")
                     .arg((yylsp[(1) - (4)]).first_line).arg((yylsp[(1) - (4)]).first_column).arg(QString((yyvsp[(1) - (4)].TNPtr)->str));
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
        }
    }

    if((yyvsp[(3) - (4)].TNPtr)->dimen!=0 || (yyvsp[(3) - (4)].TNPtr)->baseType!=BT_INT){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：变量%3的[]中的数必须是基本整型！")
                 .arg((yylsp[(1) - (4)]).first_line).arg((yylsp[(1) - (4)]).first_column).arg(QString((yyvsp[(1) - (4)].TNPtr)->str));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    if(!ErrNum){
        if((yyvsp[(3) - (4)].TNPtr)->nodeType == NT_CONST)
            CompilerUnit.FormInstruct(OC_PSH,(yyvsp[(3) - (4)].TNPtr)->num,(yyvsp[(3) - (4)].TNPtr)->baseType,0,OT_STACK);
        if((yyvsp[(3) - (4)].TNPtr)->nodeType == NT_VAR)
            CompilerUnit.FormInstruct(OC_PSH,(yyvsp[(3) - (4)].TNPtr)->num,OT_VAR,0,OT_STACK);
    }

    (yyvsp[(1) - (4)].TNPtr)->dimen -= 1;
    (yyval.TNPtr) = (yyvsp[(1) - (4)].TNPtr);
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 671 "parser.y"
    {
    /*整型值直接放在节点里*/
    (yyval.TNPtr) = CompilerUnit.NewTerminator(NT_CONST,0,BT_INT,(yyvsp[(1) - (1)].number));
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 675 "parser.y"
    {
    /*字符串值保存在字符串常量区，节点只保留对应的索引位置*/
    WSCArea.append(wstringval);
    (yyval.TNPtr) = CompilerUnit.NewTerminator(NT_CONST,0,BT_WSTRING,(WSCArea.size()-1));
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 680 "parser.y"
    {
    /*字符值保存在字符常量区，节点只保留对应的索引位置*/
    WCCArea.append(wcharval);
    (yyval.TNPtr) = CompilerUnit.NewTerminator(NT_CONST,0,BT_WCHAR,(WCCArea.size()-1));
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 689 "parser.y"
    {
    /*在函数库中查找函数*/
    if(!FuncUnit.lookup(Identifier)){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：函数%3不在函数库中！")
                 .arg((yylsp[(1) - (1)]).first_line).arg((yylsp[(1) - (1)]).first_column).arg(QString(Identifier));
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 698 "parser.y"
    {
      /*检查参数的个数是否小于要求的个数*/
      if(FuncUnit.attrPtr[0][1] != (yyvsp[(3) - (3)].number)){
          ErrStr = QString::fromLocal8Bit("第%1行第%2列：参数个数小于函数要求！")
                 .arg((yylsp[(3) - (3)]).first_line).arg((yylsp[(3) - (3)]).first_column);
          CompilerUnit.RecordCompilerInfo(ErrStr);
          ErrNum++;
          YYERROR;
      }
    if(!ErrNum){
        CompilerUnit.FormInstruct(OC_FUN,FuncUnit.attrPtr[0][0],OT_INTC,(yyvsp[(3) - (3)].number),OT_INTC);
    }
}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 712 "parser.y"
    { (yyval.number) = 0; }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 713 "parser.y"
    { (yyval.number) = (yyvsp[(2) - (3)].number); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 715 "parser.y"
    {
    int flag = 0;
    /*检查参数类型是否符合类型要求*/
    if((yyvsp[(1) - (1)].TNPtr)->baseType != FuncUnit.attrPtr[1][1]){
        flag = 1;
        /*任何基本类型都符合类型要求*/
        if(FuncUnit.attrPtr[1][1] == BT_UNDEFINE) flag = 0;
    }
    /*检查参数的维度是否符合要求*/
    if((yyvsp[(1) - (1)].TNPtr)->dimen != FuncUnit.attrPtr[1][0]){ flag = 1; }
    if(flag){
            ErrStr = QString::fromLocal8Bit("第%1行第%2列：第%3个参数错误！")
                   .arg((yylsp[(1) - (1)]).first_line).arg((yylsp[(1) - (1)]).first_column).arg(1);
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
    }


    if(!ErrNum){
        if((yyvsp[(1) - (1)].TNPtr)->nodeType == NT_CONST)
            CompilerUnit.FormInstruct(OC_PSH,(yyvsp[(1) - (1)].TNPtr)->num,(yyvsp[(1) - (1)].TNPtr)->baseType,0,OT_STACK);
        if((yyvsp[(1) - (1)].TNPtr)->nodeType == NT_VAR)
            CompilerUnit.FormInstruct(OC_PSH,(yyvsp[(1) - (1)].TNPtr)->num,OT_VAR,0,OT_STACK);
    }
    (yyval.number) = 1;
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 742 "parser.y"
    {
    int flag = 0;
    int pos = (yyvsp[(1) - (3)].number)+1;
    /*检查参数是否大于要求的个数*/
    if(pos > FuncUnit.attrPtr[0][1]){
        ErrStr = QString::fromLocal8Bit("第%1行第%2列：参数个数大于函数需要的参数！")
               .arg((yylsp[(2) - (3)]).first_line).arg((yylsp[(2) - (3)]).first_column);
        CompilerUnit.RecordCompilerInfo(ErrStr);
        ErrNum++;
        YYERROR;
    }

    /*检查参数类型是否符号要求*/
    if((yyvsp[(3) - (3)].TNPtr)->baseType != FuncUnit.attrPtr[pos][1]){
        flag = 1;
        /*任何基本类型都符合类型要求*/
        if(FuncUnit.attrPtr[pos][1] == BT_UNDEFINE) flag = 0;
    }
    /*检查参数的维度是否符合要求*/
    if((yyvsp[(3) - (3)].TNPtr)->dimen != FuncUnit.attrPtr[pos][0]){ flag = 1; }
    if(flag){
            ErrStr = QString::fromLocal8Bit("第%1行第%2列：第%3个参数错误！")
                   .arg((yylsp[(3) - (3)]).first_line).arg((yylsp[(3) - (3)]).first_column).arg(pos);
            CompilerUnit.RecordCompilerInfo(ErrStr);
            ErrNum++;
            YYERROR;
    }


    if(!ErrNum){
      if((yyvsp[(3) - (3)].TNPtr)->nodeType == NT_CONST)
          CompilerUnit.FormInstruct(OC_PSH,(yyvsp[(3) - (3)].TNPtr)->num,(yyvsp[(3) - (3)].TNPtr)->baseType,0,OT_STACK);
      if((yyvsp[(3) - (3)].TNPtr)->nodeType == NT_VAR)
          CompilerUnit.FormInstruct(OC_PSH,(yyvsp[(3) - (3)].TNPtr)->num,OT_VAR,0,OT_STACK);
    }
    (yyval.number) = pos;
}
    break;


/* Line 1792 of yacc.c  */
#line 2610 "parser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 781 "parser.y"

void yyerror(const char *) { }


