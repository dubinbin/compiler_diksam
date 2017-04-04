/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_LITERAL = 258,
     DOUBLE_LITERAL = 259,
     STRING_LITERAL = 260,
     REGEXP_LITERAL = 261,
     IDENTIFIER = 262,
     IF = 263,
     ELSE = 264,
     ELSIF = 265,
     SWITCH = 266,
     CASE = 267,
     DEFAULT_T = 268,
     WHILE = 269,
     DO_T = 270,
     FOR = 271,
     FOREACH = 272,
     RETURN_T = 273,
     BREAK = 274,
     CONTINUE = 275,
     NULL_T = 276,
     LP = 277,
     RP = 278,
     LC = 279,
     RC = 280,
     LB = 281,
     RB = 282,
     SEMICOLON = 283,
     COLON = 284,
     COMMA = 285,
     ASSIGN_T = 286,
     LOGICAL_AND = 287,
     LOGICAL_OR = 288,
     EQ = 289,
     NE = 290,
     GT = 291,
     GE = 292,
     LT = 293,
     LE = 294,
     ADD = 295,
     SUB = 296,
     MUL = 297,
     DIV = 298,
     MOD = 299,
     BIT_AND = 300,
     BIT_OR = 301,
     BIT_XOR = 302,
     BIT_NOT = 303,
     TRUE_T = 304,
     FALSE_T = 305,
     EXCLAMATION = 306,
     DOT = 307,
     ADD_ASSIGN_T = 308,
     SUB_ASSIGN_T = 309,
     MUL_ASSIGN_T = 310,
     DIV_ASSIGN_T = 311,
     MOD_ASSIGN_T = 312,
     INCREMENT = 313,
     DECREMENT = 314,
     TRY = 315,
     CATCH = 316,
     FINALLY = 317,
     THROW = 318,
     THROWS = 319,
     VOID_T = 320,
     BOOLEAN_T = 321,
     INT_T = 322,
     DOUBLE_T = 323,
     STRING_T = 324,
     NATIVE_POINTER_T = 325,
     NEW = 326,
     REQUIRE = 327,
     RENAME = 328,
     CLASS_T = 329,
     INTERFACE_T = 330,
     PUBLIC_T = 331,
     PRIVATE_T = 332,
     VIRTUAL_T = 333,
     OVERRIDE_T = 334,
     ABSTRACT_T = 335,
     THIS_T = 336,
     SUPER_T = 337,
     CONSTRUCTOR = 338,
     INSTANCEOF = 339,
     DOWN_CAST_BEGIN = 340,
     DOWN_CAST_END = 341,
     DELEGATE = 342,
     FINAL = 343,
     ENUM = 344,
     CONST = 345
   };
#endif
/* Tokens.  */
#define INT_LITERAL 258
#define DOUBLE_LITERAL 259
#define STRING_LITERAL 260
#define REGEXP_LITERAL 261
#define IDENTIFIER 262
#define IF 263
#define ELSE 264
#define ELSIF 265
#define SWITCH 266
#define CASE 267
#define DEFAULT_T 268
#define WHILE 269
#define DO_T 270
#define FOR 271
#define FOREACH 272
#define RETURN_T 273
#define BREAK 274
#define CONTINUE 275
#define NULL_T 276
#define LP 277
#define RP 278
#define LC 279
#define RC 280
#define LB 281
#define RB 282
#define SEMICOLON 283
#define COLON 284
#define COMMA 285
#define ASSIGN_T 286
#define LOGICAL_AND 287
#define LOGICAL_OR 288
#define EQ 289
#define NE 290
#define GT 291
#define GE 292
#define LT 293
#define LE 294
#define ADD 295
#define SUB 296
#define MUL 297
#define DIV 298
#define MOD 299
#define BIT_AND 300
#define BIT_OR 301
#define BIT_XOR 302
#define BIT_NOT 303
#define TRUE_T 304
#define FALSE_T 305
#define EXCLAMATION 306
#define DOT 307
#define ADD_ASSIGN_T 308
#define SUB_ASSIGN_T 309
#define MUL_ASSIGN_T 310
#define DIV_ASSIGN_T 311
#define MOD_ASSIGN_T 312
#define INCREMENT 313
#define DECREMENT 314
#define TRY 315
#define CATCH 316
#define FINALLY 317
#define THROW 318
#define THROWS 319
#define VOID_T 320
#define BOOLEAN_T 321
#define INT_T 322
#define DOUBLE_T 323
#define STRING_T 324
#define NATIVE_POINTER_T 325
#define NEW 326
#define REQUIRE 327
#define RENAME 328
#define CLASS_T 329
#define INTERFACE_T 330
#define PUBLIC_T 331
#define PRIVATE_T 332
#define VIRTUAL_T 333
#define OVERRIDE_T 334
#define ABSTRACT_T 335
#define THIS_T 336
#define SUPER_T 337
#define CONSTRUCTOR 338
#define INSTANCEOF 339
#define DOWN_CAST_BEGIN 340
#define DOWN_CAST_END 341
#define DELEGATE 342
#define FINAL 343
#define ENUM 344
#define CONST 345




/* Copy the first part of user declarations.  */
#line 1 "diksam.y"

#include <stdio.h>
#include "diksamc.h"
#define YYDEBUG 1


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 6 "diksam.y"
{
    char                *identifier;
    PackageName         *package_name;
    RequireList         *require_list;
    RenameList          *rename_list;
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;
    Expression          *expression;
    ExpressionList      *expression_list;
    Statement           *statement;
    StatementList       *statement_list;
    Block               *block;
    Elsif               *elsif;
    CaseList            *case_list;
    CatchClause         *catch_clause;
    AssignmentOperator  assignment_operator;
    TypeSpecifier       *type_specifier;
    DVM_BasicType       basic_type_specifier;
    ArrayDimension      *array_dimension;
    ClassOrMemberModifierList class_or_member_modifier;
    DVM_ClassOrInterface class_or_interface;
    ExtendsList         *extends_list;
    MemberDeclaration   *member_declaration;
    FunctionDefinition  *function_definition;
    ExceptionList       *exception_list;
    Enumerator          *enumerator;
}
/* Line 193 of yacc.c.  */
#line 310 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 323 "y.tab.c"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   991

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  87
/* YYNRULES -- Number of rules.  */
#define YYNRULES  235
/* YYNRULES -- Number of states.  */
#define YYNSTATES  442

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   345

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    10,    13,    15,    17,    19,
      22,    26,    28,    32,    34,    37,    42,    44,    46,    48,
      50,    52,    54,    56,    58,    60,    62,    64,    66,    68,
      72,    76,    80,    82,    84,    86,    94,   101,   109,   116,
     119,   124,   126,   130,   132,   135,   137,   141,   143,   147,
     149,   151,   153,   155,   157,   159,   161,   165,   167,   171,
     173,   177,   181,   183,   187,   191,   195,   199,   201,   205,
     209,   211,   215,   219,   223,   227,   231,   235,   237,   240,
     243,   246,   248,   251,   254,   258,   260,   262,   264,   269,
     274,   278,   283,   287,   291,   296,   298,   300,   302,   304,
     306,   308,   310,   312,   314,   316,   321,   327,   334,   342,
     346,   351,   355,   360,   364,   369,   371,   374,   378,   381,
     385,   386,   388,   392,   395,   397,   399,   401,   403,   405,
     407,   409,   411,   413,   415,   417,   419,   425,   433,   440,
     449,   451,   454,   460,   461,   464,   471,   473,   476,   480,
     481,   484,   486,   490,   497,   508,   517,   526,   527,   529,
     533,   534,   536,   540,   544,   550,   555,   559,   561,   564,
     565,   573,   577,   580,   584,   590,   595,   602,   603,   608,
     611,   612,   620,   621,   630,   631,   638,   639,   647,   649,
     652,   654,   656,   658,   660,   662,   664,   665,   668,   670,
     674,   676,   679,   681,   683,   685,   688,   690,   693,   701,
     708,   716,   723,   724,   727,   729,   733,   741,   748,   756,
     763,   765,   767,   768,   771,   776,   782,   788,   795,   804,
     812,   818,   825,   827,   831,   837
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      92,     0,    -1,    93,    99,    -1,    92,    99,    -1,    -1,
      94,    97,    -1,    94,    -1,    97,    -1,    95,    -1,    94,
      95,    -1,    72,    96,    28,    -1,     7,    -1,    96,    52,
       7,    -1,    98,    -1,    97,    98,    -1,    73,    96,     7,
      28,    -1,   104,    -1,   154,    -1,   127,    -1,   174,    -1,
     175,    -1,   177,    -1,    65,    -1,    66,    -1,    67,    -1,
      68,    -1,    69,    -1,    70,    -1,     7,    -1,   100,    26,
      27,    -1,     7,    26,    27,    -1,   102,    26,    27,    -1,
     100,    -1,   102,    -1,   101,    -1,   103,     7,    22,   105,
      23,   168,   152,    -1,   103,     7,    22,    23,   168,   152,
      -1,   103,     7,    22,   105,    23,   168,    28,    -1,   103,
       7,    22,    23,   168,    28,    -1,   103,     7,    -1,   105,
      30,   103,     7,    -1,   109,    -1,   106,    30,   109,    -1,
     127,    -1,   107,   127,    -1,   109,    -1,   108,    30,   109,
      -1,   111,    -1,   119,   110,   109,    -1,    31,    -1,    53,
      -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,   112,
      -1,   111,    33,   112,    -1,   113,    -1,   112,    32,   113,
      -1,   114,    -1,   113,    34,   114,    -1,   113,    35,   114,
      -1,   115,    -1,   114,    36,   115,    -1,   114,    37,   115,
      -1,   114,    38,   115,    -1,   114,    39,   115,    -1,   116,
      -1,   115,    40,   116,    -1,   115,    41,   116,    -1,   117,
      -1,   116,    42,   117,    -1,   116,    43,   117,    -1,   116,
      44,   117,    -1,   116,    45,   117,    -1,   116,    46,   117,
      -1,   116,    47,   117,    -1,   118,    -1,    41,   117,    -1,
      51,   117,    -1,    48,   117,    -1,   119,    -1,   119,    58,
      -1,   119,    59,    -1,   119,    84,   103,    -1,   120,    -1,
     122,    -1,     7,    -1,   120,    26,   108,    27,    -1,     7,
      26,   108,    27,    -1,   119,    52,     7,    -1,   119,    22,
     106,    23,    -1,   119,    22,    23,    -1,    22,   108,    23,
      -1,   119,    85,   103,    86,    -1,     3,    -1,     4,    -1,
       5,    -1,     6,    -1,    49,    -1,    50,    -1,    21,    -1,
     121,    -1,    81,    -1,    82,    -1,    71,     7,    22,    23,
      -1,    71,     7,    22,   106,    23,    -1,    71,     7,    52,
       7,    22,    23,    -1,    71,     7,    52,     7,    22,   106,
      23,    -1,    24,   126,    25,    -1,    24,   126,    30,    25,
      -1,    71,   100,   123,    -1,    71,   100,   123,   125,    -1,
      71,   101,   123,    -1,    71,   101,   123,   125,    -1,   124,
      -1,   123,   124,    -1,    26,   108,    27,    -1,    26,    27,
      -1,   125,    26,    27,    -1,    -1,   109,    -1,   126,    30,
     109,    -1,   108,    28,    -1,   128,    -1,   132,    -1,   137,
      -1,   138,    -1,   139,    -1,   140,    -1,   142,    -1,   144,
      -1,   145,    -1,   146,    -1,   150,    -1,   151,    -1,     8,
      22,   108,    23,   152,    -1,     8,    22,   108,    23,   152,
       9,   152,    -1,     8,    22,   108,    23,   152,   129,    -1,
       8,    22,   108,    23,   152,   129,     9,   152,    -1,   130,
      -1,   129,   130,    -1,    10,    22,   108,    23,   152,    -1,
      -1,     7,    29,    -1,    11,    22,   108,    23,   133,   135,
      -1,   134,    -1,   133,   134,    -1,    12,   136,   152,    -1,
      -1,    13,   152,    -1,   109,    -1,   126,    30,   109,    -1,
     131,    14,    22,   108,    23,   152,    -1,   131,    16,    22,
     141,    28,   141,    28,   141,    23,   152,    -1,   131,    15,
     152,    14,    22,   108,    23,    28,    -1,   131,    17,    22,
       7,    29,   108,    23,   152,    -1,    -1,   108,    -1,    18,
     141,    28,    -1,    -1,     7,    -1,    19,   143,    28,    -1,
      20,   143,    28,    -1,    60,   152,   147,    62,   152,    -1,
      60,   152,    62,   152,    -1,    60,   152,   147,    -1,   148,
      -1,   147,   148,    -1,    -1,    61,   149,    22,   103,     7,
      23,   152,    -1,    63,   108,    28,    -1,    63,    28,    -1,
     103,     7,    28,    -1,   103,     7,    31,   108,    28,    -1,
      88,   103,     7,    28,    -1,    88,   103,     7,    31,   108,
      28,    -1,    -1,    24,   153,   107,    25,    -1,    24,    25,
      -1,    -1,   161,     7,   162,    24,   155,   164,    25,    -1,
      -1,   159,   161,     7,   162,    24,   156,   164,    25,    -1,
      -1,   161,     7,   162,    24,   157,    25,    -1,    -1,   159,
     161,     7,   162,    24,   158,    25,    -1,   160,    -1,   159,
     160,    -1,   171,    -1,    78,    -1,    79,    -1,    80,    -1,
      74,    -1,    75,    -1,    -1,    29,   163,    -1,     7,    -1,
     163,    30,     7,    -1,   165,    -1,   164,   165,    -1,   166,
      -1,   173,    -1,   167,    -1,   159,   167,    -1,   170,    -1,
     159,   170,    -1,   103,     7,    22,   105,    23,   168,   152,
      -1,   103,     7,    22,    23,   168,   152,    -1,   103,     7,
      22,   105,    23,   168,    28,    -1,   103,     7,    22,    23,
     168,    28,    -1,    -1,    64,   169,    -1,     7,    -1,   169,
      30,     7,    -1,    83,     7,    22,   105,    23,   168,   152,
      -1,    83,     7,    22,    23,   168,   152,    -1,    83,     7,
      22,   105,    23,   168,    28,    -1,    83,     7,    22,    23,
     168,    28,    -1,    76,    -1,    77,    -1,    -1,    31,   108,
      -1,   103,     7,   172,    28,    -1,   159,   103,     7,   172,
      28,    -1,    88,   103,     7,   172,    28,    -1,   159,    88,
     103,     7,   172,    28,    -1,    87,   103,     7,    22,   105,
      23,   168,    28,    -1,    87,   103,     7,    22,    23,   168,
      28,    -1,    89,     7,    24,   176,    25,    -1,    89,     7,
      24,   176,    30,    25,    -1,     7,    -1,   176,    30,     7,
      -1,    90,     7,    31,   108,    28,    -1,    90,   103,     7,
      28,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    92,    92,    93,    97,   100,   104,   108,   114,   115,
     121,   127,   131,   137,   138,   144,   150,   151,   152,   159,
     160,   161,   164,   168,   172,   176,   180,   184,   190,   196,
     202,   208,   214,   218,   219,   222,   226,   230,   235,   241,
     245,   251,   255,   261,   265,   271,   272,   278,   279,   285,
     289,   293,   297,   301,   305,   311,   312,   318,   319,   325,
     326,   330,   336,   337,   341,   345,   349,   355,   356,   360,
     366,   367,   371,   375,   379,   383,   387,   393,   394,   398,
     402,   408,   409,   413,   417,   423,   424,   425,   431,   435,
     440,   444,   448,   452,   456,   460,   461,   462,   463,   464,
     468,   472,   476,   477,   481,   485,   489,   493,   497,   503,
     507,   513,   517,   521,   525,   532,   533,   539,   545,   549,
     557,   560,   564,   570,   574,   575,   576,   577,   578,   579,
     580,   581,   582,   583,   584,   585,   588,   592,   596,   600,
     606,   607,   613,   620,   623,   629,   635,   636,   642,   649,
     652,   658,   662,   668,   674,   681,   687,   694,   697,   700,
     707,   710,   713,   719,   725,   729,   733,   739,   740,   747,
     746,   756,   760,   766,   770,   774,   778,   785,   784,   792,
     801,   799,   810,   808,   817,   816,   826,   824,   835,   836,
     842,   843,   847,   851,   857,   861,   868,   871,   877,   881,
     887,   888,   894,   895,   898,   902,   906,   910,   916,   920,
     924,   929,   936,   939,   945,   949,   955,   959,   963,   967,
     973,   977,   984,   987,   993,   997,  1002,  1006,  1013,  1018,
    1024,  1028,  1034,  1038,  1044,  1048
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_LITERAL", "DOUBLE_LITERAL",
  "STRING_LITERAL", "REGEXP_LITERAL", "IDENTIFIER", "IF", "ELSE", "ELSIF",
  "SWITCH", "CASE", "DEFAULT_T", "WHILE", "DO_T", "FOR", "FOREACH",
  "RETURN_T", "BREAK", "CONTINUE", "NULL_T", "LP", "RP", "LC", "RC", "LB",
  "RB", "SEMICOLON", "COLON", "COMMA", "ASSIGN_T", "LOGICAL_AND",
  "LOGICAL_OR", "EQ", "NE", "GT", "GE", "LT", "LE", "ADD", "SUB", "MUL",
  "DIV", "MOD", "BIT_AND", "BIT_OR", "BIT_XOR", "BIT_NOT", "TRUE_T",
  "FALSE_T", "EXCLAMATION", "DOT", "ADD_ASSIGN_T", "SUB_ASSIGN_T",
  "MUL_ASSIGN_T", "DIV_ASSIGN_T", "MOD_ASSIGN_T", "INCREMENT", "DECREMENT",
  "TRY", "CATCH", "FINALLY", "THROW", "THROWS", "VOID_T", "BOOLEAN_T",
  "INT_T", "DOUBLE_T", "STRING_T", "NATIVE_POINTER_T", "NEW", "REQUIRE",
  "RENAME", "CLASS_T", "INTERFACE_T", "PUBLIC_T", "PRIVATE_T", "VIRTUAL_T",
  "OVERRIDE_T", "ABSTRACT_T", "THIS_T", "SUPER_T", "CONSTRUCTOR",
  "INSTANCEOF", "DOWN_CAST_BEGIN", "DOWN_CAST_END", "DELEGATE", "FINAL",
  "ENUM", "CONST", "$accept", "translation_unit", "initial_declaration",
  "require_list", "require_declaration", "package_name", "rename_list",
  "rename_declaration", "definition_or_statement", "basic_type_specifier",
  "identifier_type_specifier", "array_type_specifier", "type_specifier",
  "function_definition", "parameter_list", "argument_list",
  "statement_list", "expression", "assignment_expression",
  "assignment_operator", "logical_or_expression", "logical_and_expression",
  "equality_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "postfix_expression",
  "primary_expression", "primary_no_new_array", "array_literal",
  "array_creation", "dimension_expression_list", "dimension_expression",
  "dimension_list", "expression_list", "statement", "if_statement",
  "elsif_list", "elsif", "label_opt", "switch_statement", "case_list",
  "one_case", "default_opt", "case_expression_list", "while_statement",
  "for_statement", "do_while_statement", "foreach_statement",
  "expression_opt", "return_statement", "identifier_opt",
  "break_statement", "continue_statement", "try_statement", "catch_list",
  "catch_clause", "@1", "throw_statement", "declaration_statement",
  "block", "@2", "class_definition", "@3", "@4", "@5", "@6",
  "class_or_member_modifier_list", "class_or_member_modifier",
  "class_or_interface", "extends", "extends_list",
  "member_declaration_list", "member_declaration", "method_member",
  "method_function_definition", "throws_clause", "exception_list",
  "constructor_definition", "access_modifier", "initializer_opt",
  "field_member", "delegate_definition", "enum_definition",
  "enumerator_list", "const_definition", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    93,    93,    93,    93,    94,    94,
      95,    96,    96,    97,    97,    98,    99,    99,    99,    99,
      99,    99,   100,   100,   100,   100,   100,   100,   101,   102,
     102,   102,   103,   103,   103,   104,   104,   104,   104,   105,
     105,   106,   106,   107,   107,   108,   108,   109,   109,   110,
     110,   110,   110,   110,   110,   111,   111,   112,   112,   113,
     113,   113,   114,   114,   114,   114,   114,   115,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   118,   118,   118,   118,   119,   119,   119,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   121,
     121,   122,   122,   122,   122,   123,   123,   124,   125,   125,
     126,   126,   126,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   128,   128,   128,   128,
     129,   129,   130,   131,   131,   132,   133,   133,   134,   135,
     135,   136,   136,   137,   138,   139,   140,   141,   141,   142,
     143,   143,   144,   145,   146,   146,   146,   147,   147,   149,
     148,   150,   150,   151,   151,   151,   151,   153,   152,   152,
     155,   154,   156,   154,   157,   154,   158,   154,   159,   159,
     160,   160,   160,   160,   161,   161,   162,   162,   163,   163,
     164,   164,   165,   165,   166,   166,   166,   166,   167,   167,
     167,   167,   168,   168,   169,   169,   170,   170,   170,   170,
     171,   171,   172,   172,   173,   173,   173,   173,   174,   174,
     175,   175,   176,   176,   177,   177
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     1,     1,     1,     2,
       3,     1,     3,     1,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     1,     1,     1,     7,     6,     7,     6,     2,
       4,     1,     3,     1,     2,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     1,     2,     2,
       2,     1,     2,     2,     3,     1,     1,     1,     4,     4,
       3,     4,     3,     3,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     5,     6,     7,     3,
       4,     3,     4,     3,     4,     1,     2,     3,     2,     3,
       0,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     7,     6,     8,
       1,     2,     5,     0,     2,     6,     1,     2,     3,     0,
       2,     1,     3,     6,    10,     8,     8,     0,     1,     3,
       0,     1,     3,     3,     5,     4,     3,     1,     2,     0,
       7,     3,     2,     3,     5,     4,     6,     0,     4,     2,
       0,     7,     0,     8,     0,     6,     0,     7,     1,     2,
       1,     1,     1,     1,     1,     1,     0,     2,     1,     3,
       1,     2,     1,     1,     1,     2,     1,     2,     7,     6,
       7,     6,     0,     2,     1,     3,     7,     6,     7,     6,
       1,     1,     0,     2,     4,     5,     5,     6,     8,     7,
       5,     6,     1,     3,     5,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,   143,   143,     6,     8,     7,    13,    11,
       0,     0,     1,    95,    96,    97,    98,    87,     0,     0,
     157,   160,   160,   101,     0,   120,     0,     0,    99,   100,
       0,     0,     0,    22,    23,    24,    25,    26,    27,     0,
     194,   195,   220,   221,   191,   192,   193,   103,   104,     0,
       0,     0,     0,     3,    32,    34,    33,     0,    16,     0,
      45,    47,    55,    57,    59,    62,    67,    70,    77,    81,
      85,   102,    86,    18,   124,     0,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,    17,     0,   188,
       0,   190,    19,    20,    21,     2,     9,     5,    14,    10,
       0,     0,     0,   144,     0,     0,    87,   158,     0,   161,
       0,     0,     0,   121,     0,    78,    81,    80,    79,   177,
       0,   172,     0,    28,     0,     0,    28,     0,     0,     0,
      28,     0,     0,     0,     0,   123,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,     0,    50,    51,    52,    53,
      54,    82,    83,     0,     0,     0,     0,     0,     0,     0,
       0,   189,     0,   196,    12,    15,    30,     0,     0,     0,
       0,   159,   162,   163,    93,   109,     0,   179,   143,   169,
       0,   166,   167,   171,     0,     0,     0,   111,   115,   113,
       0,     0,     0,     0,     0,     0,    29,    31,     0,   173,
       0,    46,    56,    58,    60,    61,    63,    64,    65,    66,
      68,    69,    71,    72,    73,    74,    75,    76,    92,     0,
      41,    90,    84,     0,    48,     0,     0,     0,   157,     0,
     196,     0,     0,    89,     0,     0,   110,   122,     0,   143,
      43,     0,   165,     0,   168,   105,     0,     0,     0,     0,
     116,   112,   114,     0,   175,     0,   232,     0,     0,   235,
     212,     0,     0,     0,    91,     0,    94,    88,     0,     0,
       0,     0,     0,   198,   197,   180,   136,   120,   149,   146,
       0,   178,    44,     0,   164,   106,     0,   117,   118,     0,
     212,     0,     0,   230,     0,   234,     0,     0,    39,   212,
       0,   174,    42,     0,     0,   157,     0,   182,     0,     0,
       0,     0,     0,   138,   140,   121,     0,     0,     0,   147,
     145,     0,   107,     0,   119,     0,   212,   176,   233,   231,
     214,   213,    38,    36,     0,     0,   153,     0,     0,     0,
       0,     0,   199,     0,     0,     0,     0,     0,   200,   202,
     204,   206,   203,   185,   137,     0,     0,   141,     0,   148,
     150,     0,   108,   229,     0,     0,    37,    35,    40,     0,
     157,     0,     0,   187,     0,     0,   222,     0,     0,   205,
     207,   181,   201,     0,   139,   122,     0,   228,   215,   155,
       0,   156,   183,     0,   222,     0,     0,     0,     0,   222,
       0,   170,     0,   212,     0,     0,   212,     0,   223,   224,
     222,     0,   142,   154,     0,   212,   226,     0,   212,     0,
     225,   219,   217,     0,   211,   209,     0,   227,   218,   216,
     210,   208
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    10,     7,     8,    53,    54,
      55,    56,   271,    58,   272,   229,   249,    59,    60,   165,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,   197,   198,   261,   114,    73,    74,   323,   324,
      75,    76,   288,   289,   330,   327,    77,    78,    79,    80,
     108,    81,   110,    82,    83,    84,   191,   192,   251,    85,
      86,   120,   188,    87,   319,   350,   320,   351,   356,    89,
      90,   242,   284,   357,   358,   359,   360,   307,   341,   361,
      91,   407,   362,    92,    93,   267,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -383
static const yytype_int16 yypact[] =
{
     -13,    18,    18,   370,   458,   -13,  -383,    -8,  -383,  -383,
      -9,     6,  -383,  -383,  -383,  -383,  -383,    25,    31,    70,
     909,   111,   111,  -383,   909,   909,   909,   909,  -383,  -383,
     909,   103,   717,  -383,  -383,  -383,  -383,  -383,  -383,   126,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,   201,
     201,   151,   214,  -383,   110,  -383,   161,   200,  -383,   129,
    -383,   186,   209,   107,   225,   159,   380,  -383,  -383,    15,
     222,  -383,  -383,  -383,  -383,   290,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,   287,  -383,
     244,  -383,  -383,  -383,  -383,  -383,  -383,    -8,  -383,  -383,
     248,   249,   756,  -383,   909,   909,   233,   255,   259,  -383,
     271,   300,    19,  -383,     1,  -383,   191,  -383,  -383,   309,
     228,  -383,   187,   -12,   312,   312,   313,   328,   333,   318,
      -3,   337,   320,   322,    -7,  -383,   909,   909,   909,   909,
     909,   909,   909,   909,   909,   909,   909,   909,   909,   909,
     909,   909,   909,   768,  -383,   343,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,   201,   201,   909,   909,   329,   103,   334,
     335,  -383,   351,   339,  -383,  -383,  -383,    64,    32,    33,
     909,  -383,  -383,  -383,  -383,  -383,   807,  -383,   618,  -383,
     103,   231,  -383,  -383,   819,   362,   909,   345,  -383,   345,
     352,   350,    77,   375,   909,   355,  -383,  -383,   100,  -383,
     909,  -383,   209,   107,   225,   225,   159,   159,   159,   159,
     380,   380,  -383,  -383,  -383,  -383,  -383,  -383,  -383,    34,
    -383,  -383,  -383,   298,  -383,   158,   909,   373,   909,   386,
     339,   400,   384,  -383,   103,   397,  -383,  -383,   403,   546,
    -383,   390,  -383,   103,  -383,  -383,    72,   391,   184,   858,
    -383,   388,   388,   112,  -383,   909,  -383,    11,   210,  -383,
     353,   408,    73,   216,  -383,   909,  -383,  -383,    74,   394,
     401,   399,   407,  -383,   402,   409,   164,   909,   285,  -383,
     181,  -383,  -383,   201,  -383,  -383,   870,  -383,  -383,   415,
     353,    83,   224,  -383,     9,  -383,   436,   102,  -383,   353,
     201,  -383,  -383,   103,   909,   909,   909,   428,   447,   625,
     430,   103,   434,   292,  -383,   443,   438,   103,   103,  -383,
    -383,   463,  -383,    86,  -383,   444,   353,  -383,  -383,  -383,
    -383,   441,  -383,  -383,   116,   466,  -383,    94,   446,    98,
     625,   450,  -383,   474,   201,   476,   649,    10,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,   909,   103,  -383,   909,  -383,
    -383,   461,  -383,  -383,   457,   479,  -383,  -383,  -383,   459,
     909,   103,   253,  -383,   467,   481,    30,   201,   483,  -383,
    -383,  -383,  -383,   109,  -383,   468,   103,  -383,  -383,  -383,
     470,  -383,  -383,   330,   460,   336,   909,   469,   487,    30,
     103,  -383,   103,   353,   115,   472,   353,   133,   255,  -383,
     460,   473,  -383,  -383,   147,   353,  -383,   174,   353,   475,
    -383,  -383,  -383,   177,  -383,  -383,   182,  -383,  -383,  -383,
    -383,  -383
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -383,  -383,  -383,  -383,   490,   494,   493,     4,   498,   465,
     471,  -383,    -2,  -383,  -256,  -186,  -383,   -20,   -22,  -383,
    -383,   368,   374,   171,   172,   179,     3,  -383,    85,  -383,
    -383,  -383,   389,    59,   314,   229,  -168,  -383,  -383,   188,
    -383,  -383,  -383,   227,  -383,  -383,  -383,  -383,  -383,  -383,
    -232,  -383,   495,  -383,  -383,  -383,  -383,   331,  -383,  -383,
    -383,  -124,  -383,  -383,  -383,  -383,  -383,  -383,   323,   -83,
     431,   280,  -383,   180,  -343,  -383,   175,  -291,  -383,   185,
    -383,  -382,  -383,  -383,  -383,  -383,  -383
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -187
static const yytype_int16 yytable[] =
{
     107,    57,    57,   113,   112,   171,   280,   301,   256,   335,
     194,    98,   122,   101,   392,   208,   338,   126,   344,    99,
     250,   209,   415,   200,   210,     9,   185,   421,   204,   115,
     117,   186,   -28,   118,   339,   391,   303,   153,   429,   392,
     195,   304,   184,   100,   237,   374,   154,   127,   128,   136,
     131,   102,   405,   104,   103,   244,   245,   274,   100,     1,
       2,   406,   136,   136,   275,     2,   252,   155,   156,   157,
     158,   159,   160,   161,   162,    33,    34,    35,    36,    37,
      38,   292,   177,   348,   178,   179,    42,    43,    44,    45,
      46,   243,   105,   353,   136,   295,   309,   313,   354,   163,
     164,    98,   275,   310,   136,   264,   336,   126,   265,   372,
     333,   116,   116,   310,   211,   116,   275,   379,   109,   126,
     286,   381,   424,   270,   136,   427,   119,   119,   136,   294,
     342,   230,   410,   123,   433,   300,   132,   436,   425,   136,
     119,   139,   140,   234,   376,   310,   235,   414,   400,   417,
     222,   223,   224,   225,   226,   227,   428,   135,   129,   136,
     177,   232,   233,   310,   247,    33,    34,    35,    36,    37,
      38,   119,   230,   321,   322,   431,   258,    33,    34,    35,
      36,    37,    38,   343,   268,   277,   248,   133,   136,   346,
     273,    33,    34,    35,    36,    37,    38,   364,   119,   145,
     146,   119,   434,   369,   370,   438,   119,   134,   126,   209,
     440,   297,   210,   153,   136,   193,   278,   136,   107,   137,
     377,   130,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   305,   258,
     136,   138,   394,   155,   311,   302,   136,   248,   166,   161,
     162,   173,   337,   312,   136,   174,   260,   401,   260,   180,
     126,   141,   142,   143,   144,   325,    33,    34,    35,    36,
      37,    38,   411,   171,   230,   163,   164,   175,   402,    33,
      34,    35,    36,    37,    38,   136,   422,   181,   423,   189,
     190,   331,   189,   253,   347,   107,   349,   287,   328,   182,
     432,   366,   322,   435,   167,   168,   169,   170,   345,   439,
     214,   215,   441,   216,   217,   218,   219,   355,    33,    34,
      35,    36,    37,    38,   220,   221,    88,    88,   183,    42,
      43,    44,    45,    46,   187,   201,   353,   126,   196,   200,
     202,   354,   203,   126,   205,   393,   395,   206,   355,   207,
     231,   236,   385,   413,   388,   355,   238,   239,   240,   416,
     107,    40,    41,    42,    43,    44,    45,    46,   241,   257,
      12,   259,   263,    13,    14,    15,    16,    17,    18,   176,
     355,    19,   266,   269,   276,   408,   418,   279,    20,    21,
      22,    23,    24,   281,    25,    33,    34,    35,    36,    37,
      38,    33,    34,    35,    36,    37,    38,   283,   285,   287,
     290,    26,   293,   296,   299,   308,   314,   306,    27,    28,
      29,    30,   147,   148,   149,   150,   151,   152,   316,   315,
      31,   317,   318,    32,  -184,    33,    34,    35,    36,    37,
      38,    39,   334,   340,    40,    41,    42,    43,    44,    45,
      46,    47,    48,  -186,   352,   363,   365,    49,    50,    51,
      52,    13,    14,    15,    16,    17,    18,  -151,   368,    19,
     371,   375,   373,   378,   380,   383,    20,    21,    22,    23,
      24,   384,    25,   386,   396,   397,   398,   399,   404,   403,
     409,   406,  -152,   412,   420,    96,    11,   419,    97,    26,
     426,   430,    95,   437,   124,   212,    27,    28,    29,    30,
     125,   367,   213,   262,   199,   329,   326,   111,    31,   172,
     282,    32,   254,    33,    34,    35,    36,    37,    38,    39,
     382,   389,    40,    41,    42,    43,    44,    45,    46,    47,
      48,   390,     0,     0,     0,    49,    50,    51,    52,    13,
      14,    15,    16,    17,    18,     0,     0,    19,     0,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,     0,
      25,   291,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,     0,     0,     0,    27,    28,    29,    30,     0,     0,
       0,     0,     0,     0,     0,     0,    31,     0,     0,    32,
       0,    33,    34,    35,    36,    37,    38,    39,     0,     0,
       0,    13,    14,    15,    16,    17,    18,    47,    48,    19,
       0,     0,   126,     0,    50,     0,    20,    21,    22,    23,
      24,     0,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   126,     0,     0,    26,
       0,     0,     0,     0,     0,     0,    27,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
       0,    32,     0,    33,    34,    35,    36,    37,    38,    39,
      33,    34,    35,    36,    37,    38,     0,     0,     0,    47,
      48,    42,    43,    44,    45,    46,    50,     0,   353,     0,
       0,     0,     0,   354,    33,    34,    35,    36,    37,    38,
      13,    14,    15,    16,   106,    42,    43,    44,    45,    46,
       0,     0,   353,     0,     0,     0,     0,   387,    23,    24,
       0,    25,     0,     0,     0,   121,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,    13,
      14,    15,    16,   106,     0,    27,    28,    29,    30,     0,
       0,    13,    14,    15,    16,   106,     0,    23,    24,     0,
      25,     0,     0,   176,     0,     0,     0,     0,    39,    23,
      24,   228,    25,     0,     0,     0,     0,    26,    47,    48,
       0,     0,     0,     0,    27,    28,    29,    30,     0,    26,
      13,    14,    15,    16,   106,     0,    27,    28,    29,    30,
       0,     0,    13,    14,    15,    16,   106,    39,    23,    24,
       0,    25,   246,     0,     0,     0,     0,    47,    48,    39,
      23,    24,   255,    25,     0,     0,     0,     0,    26,    47,
      48,     0,     0,     0,     0,    27,    28,    29,    30,     0,
      26,    13,    14,    15,    16,   106,     0,    27,    28,    29,
      30,     0,     0,    13,    14,    15,    16,   106,    39,    23,
      24,     0,    25,     0,     0,   298,     0,     0,    47,    48,
      39,    23,    24,   332,    25,     0,     0,     0,     0,    26,
      47,    48,     0,     0,     0,     0,    27,    28,    29,    30,
       0,    26,    13,    14,    15,    16,   106,     0,    27,    28,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    39,
      23,    24,     0,    25,     0,     0,     0,     0,     0,    47,
      48,    39,     0,     0,     0,     0,     0,     0,     0,     0,
      26,    47,    48,     0,     0,     0,     0,    27,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      39,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,    48
};

static const yytype_int16 yycheck[] =
{
      20,     3,     4,    25,    24,    88,   238,   263,   194,   300,
      22,     7,    32,     7,   357,    22,     7,     7,   309,    28,
     188,    28,   404,    26,    31,     7,    25,   409,    31,    26,
      27,    30,     7,    30,    25,    25,    25,    22,   420,   382,
      52,    30,    23,    52,   168,   336,    31,    49,    50,    30,
      52,    26,    22,    22,    29,    23,    23,    23,    52,    72,
      73,    31,    30,    30,    30,    73,   190,    52,    53,    54,
      55,    56,    57,    58,    59,    65,    66,    67,    68,    69,
      70,   249,   102,   315,   104,   105,    76,    77,    78,    79,
      80,    27,    22,    83,    30,    23,    23,    23,    88,    84,
      85,    97,    30,    30,    30,    28,    23,     7,    31,    23,
     296,    26,    27,    30,   136,    30,    30,    23,     7,     7,
     244,    23,   413,    23,    30,   416,    24,    24,    30,   253,
      28,   153,    23,     7,   425,    23,    26,   428,    23,    30,
      24,    34,    35,   165,    28,    30,   166,   403,   380,   405,
     147,   148,   149,   150,   151,   152,    23,    28,     7,    30,
     180,   163,   164,    30,   186,    65,    66,    67,    68,    69,
      70,    24,   194,     9,    10,    28,   196,    65,    66,    67,
      68,    69,    70,   307,   204,    27,   188,    26,    30,   313,
     210,    65,    66,    67,    68,    69,    70,   321,    24,    40,
      41,    24,    28,   327,   328,    28,    24,     7,     7,    28,
      28,    27,    31,    22,    30,    28,   236,    30,   238,    33,
     344,     7,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,    28,   259,
      30,    32,   366,    52,    28,   265,    30,   249,    26,    58,
      59,     7,    28,   275,    30,     7,   197,   381,   199,    26,
       7,    36,    37,    38,    39,   287,    65,    66,    67,    68,
      69,    70,   396,   356,   296,    84,    85,    28,    25,    65,
      66,    67,    68,    69,    70,    30,   410,    28,   412,    61,
      62,   293,    61,    62,   314,   315,   316,    12,    13,    28,
     424,     9,    10,   427,    14,    15,    16,    17,   310,   433,
     139,   140,   436,   141,   142,   143,   144,   319,    65,    66,
      67,    68,    69,    70,   145,   146,     3,     4,    28,    76,
      77,    78,    79,    80,    25,     7,    83,     7,    26,    26,
       7,    88,    24,     7,     7,   365,   368,    27,   350,    27,
       7,    22,   354,    23,   356,   357,    22,    22,     7,    23,
     380,    74,    75,    76,    77,    78,    79,    80,    29,     7,
       0,    26,    22,     3,     4,     5,     6,     7,     8,    27,
     382,    11,     7,    28,    86,   387,   406,    14,    18,    19,
      20,    21,    22,     7,    24,    65,    66,    67,    68,    69,
      70,    65,    66,    67,    68,    69,    70,     7,    24,    12,
       7,    41,    22,    22,    26,     7,    22,    64,    48,    49,
      50,    51,    42,    43,    44,    45,    46,    47,    29,    28,
      60,    24,    30,    63,    25,    65,    66,    67,    68,    69,
      70,    71,    27,     7,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    25,     7,    25,    22,    87,    88,    89,
      90,     3,     4,     5,     6,     7,     8,    24,    30,    11,
       7,    30,    28,     7,    28,    25,    18,    19,    20,    21,
      22,     7,    24,     7,    23,    28,     7,    28,     7,    22,
       7,    31,    24,    23,     7,     5,     2,    28,     5,    41,
      28,    28,     4,    28,    39,   137,    48,    49,    50,    51,
      39,   323,   138,   199,   125,   288,   287,    22,    60,    88,
     240,    63,   191,    65,    66,    67,    68,    69,    70,    71,
     350,   356,    74,    75,    76,    77,    78,    79,    80,    81,
      82,   356,    -1,    -1,    -1,    87,    88,    89,    90,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    18,    19,    20,    21,    22,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    63,
      -1,    65,    66,    67,    68,    69,    70,    71,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    81,    82,    11,
      -1,    -1,     7,    -1,    88,    -1,    18,    19,    20,    21,
      22,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    63,    -1,    65,    66,    67,    68,    69,    70,    71,
      65,    66,    67,    68,    69,    70,    -1,    -1,    -1,    81,
      82,    76,    77,    78,    79,    80,    88,    -1,    83,    -1,
      -1,    -1,    -1,    88,    65,    66,    67,    68,    69,    70,
       3,     4,     5,     6,     7,    76,    77,    78,    79,    80,
      -1,    -1,    83,    -1,    -1,    -1,    -1,    88,    21,    22,
      -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,     3,
       4,     5,     6,     7,    -1,    48,    49,    50,    51,    -1,
      -1,     3,     4,     5,     6,     7,    -1,    21,    22,    -1,
      24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    71,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    41,    81,    82,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    -1,    41,
       3,     4,     5,     6,     7,    -1,    48,    49,    50,    51,
      -1,    -1,     3,     4,     5,     6,     7,    71,    21,    22,
      -1,    24,    25,    -1,    -1,    -1,    -1,    81,    82,    71,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    41,    81,
      82,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    -1,
      41,     3,     4,     5,     6,     7,    -1,    48,    49,    50,
      51,    -1,    -1,     3,     4,     5,     6,     7,    71,    21,
      22,    -1,    24,    -1,    -1,    27,    -1,    -1,    81,    82,
      71,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    41,
      81,    82,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      -1,    41,     3,     4,     5,     6,     7,    -1,    48,    49,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      21,    22,    -1,    24,    -1,    -1,    -1,    -1,    -1,    81,
      82,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    81,    82,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    72,    73,    92,    93,    94,    95,    97,    98,     7,
      96,    96,     0,     3,     4,     5,     6,     7,     8,    11,
      18,    19,    20,    21,    22,    24,    41,    48,    49,    50,
      51,    60,    63,    65,    66,    67,    68,    69,    70,    71,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    87,
      88,    89,    90,    99,   100,   101,   102,   103,   104,   108,
     109,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   127,   128,   131,   132,   137,   138,   139,
     140,   142,   144,   145,   146,   150,   151,   154,   159,   160,
     161,   171,   174,   175,   177,    99,    95,    97,    98,    28,
      52,     7,    26,    29,    22,    22,     7,   108,   141,     7,
     143,   143,   108,   109,   126,   117,   119,   117,   117,    24,
     152,    28,   108,     7,   100,   101,     7,   103,   103,     7,
       7,   103,    26,    26,     7,    28,    30,    33,    32,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    22,    31,    52,    53,    54,    55,    56,
      57,    58,    59,    84,    85,   110,    26,    14,    15,    16,
      17,   160,   161,     7,     7,    28,    27,   108,   108,   108,
      26,    28,    28,    28,    23,    25,    30,    25,   153,    61,
      62,   147,   148,    28,    22,    52,    26,   123,   124,   123,
      26,     7,     7,    24,    31,     7,    27,    27,    22,    28,
      31,   109,   112,   113,   114,   114,   115,   115,   115,   115,
     116,   116,   117,   117,   117,   117,   117,   117,    23,   106,
     109,     7,   103,   103,   109,   108,    22,   152,    22,    22,
       7,    29,   162,    27,    23,    23,    25,   109,   103,   107,
     127,   149,   152,    62,   148,    23,   106,     7,   108,    26,
     124,   125,   125,    22,    28,    31,     7,   176,   108,    28,
      23,   103,   105,   108,    23,    30,    86,    27,   108,    14,
     141,     7,   162,     7,   163,    24,   152,    12,   133,   134,
       7,    25,   127,    22,   152,    23,    22,    27,    27,    26,
      23,   105,   108,    25,    30,    28,    64,   168,     7,    23,
      30,    28,   109,    23,    22,    28,    29,    24,    30,   155,
     157,     9,    10,   129,   130,   109,   126,   136,    13,   134,
     135,   103,    23,   106,    27,   168,    23,    28,     7,    25,
       7,   169,    28,   152,   168,   103,   152,   108,   141,   108,
     156,   158,     7,    83,    88,   103,   159,   164,   165,   166,
     167,   170,   173,    25,   152,    22,     9,   130,    30,   152,
     152,     7,    23,    28,   168,    30,    28,   152,     7,    23,
      28,    23,   164,    25,     7,   103,     7,    88,   103,   167,
     170,    25,   165,   108,   152,   109,    23,    28,     7,    28,
     141,   152,    25,    22,     7,    22,    31,   172,   103,     7,
      23,   152,    23,    23,   105,   172,    23,   105,   108,    28,
       7,   172,   152,   152,   168,    23,    28,   168,    23,   172,
      28,    28,   152,   168,    28,   152,   168,    28,    28,   152,
      28,   152
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 97 "diksam.y"
    {
            dkc_set_require_and_rename_list(NULL, NULL);
        }
    break;

  case 5:
#line 101 "diksam.y"
    {
            dkc_set_require_and_rename_list((yyvsp[(1) - (2)].require_list), (yyvsp[(2) - (2)].rename_list));
        }
    break;

  case 6:
#line 105 "diksam.y"
    {
            dkc_set_require_and_rename_list((yyvsp[(1) - (1)].require_list), NULL);
        }
    break;

  case 7:
#line 109 "diksam.y"
    {
            dkc_set_require_and_rename_list(NULL, (yyvsp[(1) - (1)].rename_list));
        }
    break;

  case 9:
#line 116 "diksam.y"
    {
            (yyval.require_list) = dkc_chain_require_list((yyvsp[(1) - (2)].require_list), (yyvsp[(2) - (2)].require_list));
        }
    break;

  case 10:
#line 122 "diksam.y"
    {
            (yyval.require_list) = dkc_create_require_list((yyvsp[(2) - (3)].package_name));
        }
    break;

  case 11:
#line 128 "diksam.y"
    {
            (yyval.package_name) = dkc_create_package_name((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 12:
#line 132 "diksam.y"
    {
            (yyval.package_name) = dkc_chain_package_name((yyvsp[(1) - (3)].package_name), (yyvsp[(3) - (3)].identifier));
        }
    break;

  case 14:
#line 139 "diksam.y"
    {
            (yyval.rename_list) = dkc_chain_rename_list((yyvsp[(1) - (2)].rename_list), (yyvsp[(2) - (2)].rename_list));
        }
    break;

  case 15:
#line 145 "diksam.y"
    {
            (yyval.rename_list) = dkc_create_rename_list((yyvsp[(2) - (4)].package_name), (yyvsp[(3) - (4)].identifier));
        }
    break;

  case 18:
#line 153 "diksam.y"
    {
            DKC_Compiler *compiler = dkc_get_current_compiler();

            compiler->statement_list
                = dkc_chain_statement_list(compiler->statement_list, (yyvsp[(1) - (1)].statement));
        }
    break;

  case 22:
#line 165 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_VOID_TYPE;
        }
    break;

  case 23:
#line 169 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_BOOLEAN_TYPE;
        }
    break;

  case 24:
#line 173 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_INT_TYPE;
        }
    break;

  case 25:
#line 177 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_DOUBLE_TYPE;
        }
    break;

  case 26:
#line 181 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_STRING_TYPE;
        }
    break;

  case 27:
#line 185 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_NATIVE_POINTER_TYPE;
        }
    break;

  case 28:
#line 191 "diksam.y"
    {
            (yyval.type_specifier) = dkc_create_identifier_type_specifier((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 29:
#line 197 "diksam.y"
    {
            TypeSpecifier *basic_type
                = dkc_create_type_specifier((yyvsp[(1) - (3)].basic_type_specifier));
            (yyval.type_specifier) = dkc_create_array_type_specifier(basic_type);
        }
    break;

  case 30:
#line 203 "diksam.y"
    {
            TypeSpecifier *identifier_type
                = dkc_create_identifier_type_specifier((yyvsp[(1) - (3)].identifier));
            (yyval.type_specifier) = dkc_create_array_type_specifier(identifier_type);
        }
    break;

  case 31:
#line 209 "diksam.y"
    {
            (yyval.type_specifier) = dkc_create_array_type_specifier((yyvsp[(1) - (3)].type_specifier));
        }
    break;

  case 32:
#line 215 "diksam.y"
    {
                    (yyval.type_specifier) = dkc_create_type_specifier((yyvsp[(1) - (1)].basic_type_specifier));
        }
    break;

  case 35:
#line 223 "diksam.y"
    {
            dkc_function_define((yyvsp[(1) - (7)].type_specifier), (yyvsp[(2) - (7)].identifier), (yyvsp[(4) - (7)].parameter_list), (yyvsp[(6) - (7)].exception_list), (yyvsp[(7) - (7)].block));
        }
    break;

  case 36:
#line 227 "diksam.y"
    {
            dkc_function_define((yyvsp[(1) - (6)].type_specifier), (yyvsp[(2) - (6)].identifier), NULL, (yyvsp[(5) - (6)].exception_list), (yyvsp[(6) - (6)].block));
        }
    break;

  case 37:
#line 232 "diksam.y"
    {
            dkc_function_define((yyvsp[(1) - (7)].type_specifier), (yyvsp[(2) - (7)].identifier), (yyvsp[(4) - (7)].parameter_list), (yyvsp[(6) - (7)].exception_list), NULL);
        }
    break;

  case 38:
#line 236 "diksam.y"
    {
            dkc_function_define((yyvsp[(1) - (6)].type_specifier), (yyvsp[(2) - (6)].identifier), NULL, (yyvsp[(5) - (6)].exception_list), NULL);
        }
    break;

  case 39:
#line 242 "diksam.y"
    {
            (yyval.parameter_list) = dkc_create_parameter((yyvsp[(1) - (2)].type_specifier), (yyvsp[(2) - (2)].identifier));
        }
    break;

  case 40:
#line 246 "diksam.y"
    {
            (yyval.parameter_list) = dkc_chain_parameter((yyvsp[(1) - (4)].parameter_list), (yyvsp[(3) - (4)].type_specifier), (yyvsp[(4) - (4)].identifier));
        }
    break;

  case 41:
#line 252 "diksam.y"
    {
            (yyval.argument_list) = dkc_create_argument_list((yyvsp[(1) - (1)].expression));
        }
    break;

  case 42:
#line 256 "diksam.y"
    {
            (yyval.argument_list) = dkc_chain_argument_list((yyvsp[(1) - (3)].argument_list), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 43:
#line 262 "diksam.y"
    {
            (yyval.statement_list) = dkc_create_statement_list((yyvsp[(1) - (1)].statement));
        }
    break;

  case 44:
#line 266 "diksam.y"
    {
            (yyval.statement_list) = dkc_chain_statement_list((yyvsp[(1) - (2)].statement_list), (yyvsp[(2) - (2)].statement));
        }
    break;

  case 46:
#line 273 "diksam.y"
    {
            (yyval.expression) = dkc_create_comma_expression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 48:
#line 280 "diksam.y"
    {
            (yyval.expression) = dkc_create_assign_expression((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].assignment_operator), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 49:
#line 286 "diksam.y"
    {
            (yyval.assignment_operator) = NORMAL_ASSIGN;
        }
    break;

  case 50:
#line 290 "diksam.y"
    {
            (yyval.assignment_operator) = ADD_ASSIGN;
        }
    break;

  case 51:
#line 294 "diksam.y"
    {
            (yyval.assignment_operator) = SUB_ASSIGN;
        }
    break;

  case 52:
#line 298 "diksam.y"
    {
            (yyval.assignment_operator) = MUL_ASSIGN;
        }
    break;

  case 53:
#line 302 "diksam.y"
    {
            (yyval.assignment_operator) = DIV_ASSIGN;
        }
    break;

  case 54:
#line 306 "diksam.y"
    {
            (yyval.assignment_operator) = MOD_ASSIGN;
        }
    break;

  case 56:
#line 313 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(LOGICAL_OR_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 58:
#line 320 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(LOGICAL_AND_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 60:
#line 327 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(EQ_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 61:
#line 331 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(NE_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 63:
#line 338 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(GT_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 64:
#line 342 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(GE_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 65:
#line 346 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(LT_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 66:
#line 350 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(LE_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 68:
#line 357 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(ADD_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 69:
#line 361 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(SUB_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 71:
#line 368 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(MUL_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 72:
#line 372 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(DIV_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 73:
#line 376 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(MOD_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 74:
#line 380 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(BIT_AND_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 75:
#line 384 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(BIT_OR_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 76:
#line 388 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(BIT_XOR_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 78:
#line 395 "diksam.y"
    {
            (yyval.expression) = dkc_create_minus_expression((yyvsp[(2) - (2)].expression));
        }
    break;

  case 79:
#line 399 "diksam.y"
    {
            (yyval.expression) = dkc_create_logical_not_expression((yyvsp[(2) - (2)].expression));
        }
    break;

  case 80:
#line 403 "diksam.y"
    {
            (yyval.expression) = dkc_create_bit_not_expression((yyvsp[(2) - (2)].expression));
        }
    break;

  case 82:
#line 410 "diksam.y"
    {
            (yyval.expression) = dkc_create_incdec_expression((yyvsp[(1) - (2)].expression), INCREMENT_EXPRESSION);
        }
    break;

  case 83:
#line 414 "diksam.y"
    {
            (yyval.expression) = dkc_create_incdec_expression((yyvsp[(1) - (2)].expression), DECREMENT_EXPRESSION);
        }
    break;

  case 84:
#line 418 "diksam.y"
    {
            (yyval.expression) = dkc_create_instanceof_expression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].type_specifier));
        }
    break;

  case 87:
#line 426 "diksam.y"
    {
            (yyval.expression) = dkc_create_identifier_expression((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 88:
#line 432 "diksam.y"
    {
            (yyval.expression) = dkc_create_index_expression((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression));
        }
    break;

  case 89:
#line 436 "diksam.y"
    {
            Expression *identifier = dkc_create_identifier_expression((yyvsp[(1) - (4)].identifier));
            (yyval.expression) = dkc_create_index_expression(identifier, (yyvsp[(3) - (4)].expression));
        }
    break;

  case 90:
#line 441 "diksam.y"
    {
            (yyval.expression) = dkc_create_member_expression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].identifier));
        }
    break;

  case 91:
#line 445 "diksam.y"
    {
            (yyval.expression) = dkc_create_function_call_expression((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].argument_list));
        }
    break;

  case 92:
#line 449 "diksam.y"
    {
            (yyval.expression) = dkc_create_function_call_expression((yyvsp[(1) - (3)].expression), NULL);
        }
    break;

  case 93:
#line 453 "diksam.y"
    {
            (yyval.expression) = (yyvsp[(2) - (3)].expression);
        }
    break;

  case 94:
#line 457 "diksam.y"
    {
            (yyval.expression) = dkc_create_down_cast_expression((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].type_specifier));
        }
    break;

  case 99:
#line 465 "diksam.y"
    {
            (yyval.expression) = dkc_create_boolean_expression(DVM_TRUE);
        }
    break;

  case 100:
#line 469 "diksam.y"
    {
            (yyval.expression) = dkc_create_boolean_expression(DVM_FALSE);
        }
    break;

  case 101:
#line 473 "diksam.y"
    {
            (yyval.expression) = dkc_create_null_expression();
        }
    break;

  case 103:
#line 478 "diksam.y"
    {
            (yyval.expression) = dkc_create_this_expression();
        }
    break;

  case 104:
#line 482 "diksam.y"
    {
            (yyval.expression) = dkc_create_super_expression();
        }
    break;

  case 105:
#line 486 "diksam.y"
    {
            (yyval.expression) = dkc_create_new_expression((yyvsp[(2) - (4)].identifier), NULL, NULL);
        }
    break;

  case 106:
#line 490 "diksam.y"
    {
            (yyval.expression) = dkc_create_new_expression((yyvsp[(2) - (5)].identifier), NULL, (yyvsp[(4) - (5)].argument_list));
        }
    break;

  case 107:
#line 494 "diksam.y"
    {
            (yyval.expression) = dkc_create_new_expression((yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].identifier), NULL);
        }
    break;

  case 108:
#line 498 "diksam.y"
    {
            (yyval.expression) = dkc_create_new_expression((yyvsp[(2) - (7)].identifier), (yyvsp[(4) - (7)].identifier), (yyvsp[(6) - (7)].argument_list));
        }
    break;

  case 109:
#line 504 "diksam.y"
    {
            (yyval.expression) = dkc_create_array_literal_expression((yyvsp[(2) - (3)].expression_list));
        }
    break;

  case 110:
#line 508 "diksam.y"
    {
            (yyval.expression) = dkc_create_array_literal_expression((yyvsp[(2) - (4)].expression_list));
        }
    break;

  case 111:
#line 514 "diksam.y"
    {
            (yyval.expression) = dkc_create_basic_array_creation((yyvsp[(2) - (3)].basic_type_specifier), (yyvsp[(3) - (3)].array_dimension), NULL);
        }
    break;

  case 112:
#line 518 "diksam.y"
    {
            (yyval.expression) = dkc_create_basic_array_creation((yyvsp[(2) - (4)].basic_type_specifier), (yyvsp[(3) - (4)].array_dimension), (yyvsp[(4) - (4)].array_dimension));
        }
    break;

  case 113:
#line 522 "diksam.y"
    {
            (yyval.expression) = dkc_create_class_array_creation((yyvsp[(2) - (3)].type_specifier), (yyvsp[(3) - (3)].array_dimension), NULL);
        }
    break;

  case 114:
#line 527 "diksam.y"
    {
            (yyval.expression) = dkc_create_class_array_creation((yyvsp[(2) - (4)].type_specifier), (yyvsp[(3) - (4)].array_dimension), (yyvsp[(4) - (4)].array_dimension));
        }
    break;

  case 116:
#line 534 "diksam.y"
    {
            (yyval.array_dimension) = dkc_chain_array_dimension((yyvsp[(1) - (2)].array_dimension), (yyvsp[(2) - (2)].array_dimension));
        }
    break;

  case 117:
#line 540 "diksam.y"
    {
            (yyval.array_dimension) = dkc_create_array_dimension((yyvsp[(2) - (3)].expression));
        }
    break;

  case 118:
#line 546 "diksam.y"
    {
            (yyval.array_dimension) = dkc_create_array_dimension(NULL);
        }
    break;

  case 119:
#line 550 "diksam.y"
    {
            (yyval.array_dimension) = dkc_chain_array_dimension((yyvsp[(1) - (3)].array_dimension),
                                           dkc_create_array_dimension(NULL));
        }
    break;

  case 120:
#line 557 "diksam.y"
    {
            (yyval.expression_list) = NULL;
        }
    break;

  case 121:
#line 561 "diksam.y"
    {
            (yyval.expression_list) = dkc_create_expression_list((yyvsp[(1) - (1)].expression));
        }
    break;

  case 122:
#line 565 "diksam.y"
    {
            (yyval.expression_list) = dkc_chain_expression_list((yyvsp[(1) - (3)].expression_list), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 123:
#line 571 "diksam.y"
    {
          (yyval.statement) = dkc_create_expression_statement((yyvsp[(1) - (2)].expression));
        }
    break;

  case 136:
#line 589 "diksam.y"
    {
            (yyval.statement) = dkc_create_if_statement((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].block), NULL, NULL);
        }
    break;

  case 137:
#line 593 "diksam.y"
    {
            (yyval.statement) = dkc_create_if_statement((yyvsp[(3) - (7)].expression), (yyvsp[(5) - (7)].block), NULL, (yyvsp[(7) - (7)].block));
        }
    break;

  case 138:
#line 597 "diksam.y"
    {
            (yyval.statement) = dkc_create_if_statement((yyvsp[(3) - (6)].expression), (yyvsp[(5) - (6)].block), (yyvsp[(6) - (6)].elsif), NULL);
        }
    break;

  case 139:
#line 601 "diksam.y"
    {
            (yyval.statement) = dkc_create_if_statement((yyvsp[(3) - (8)].expression), (yyvsp[(5) - (8)].block), (yyvsp[(6) - (8)].elsif), (yyvsp[(8) - (8)].block));
        }
    break;

  case 141:
#line 608 "diksam.y"
    {
            (yyval.elsif) = dkc_chain_elsif_list((yyvsp[(1) - (2)].elsif), (yyvsp[(2) - (2)].elsif));
        }
    break;

  case 142:
#line 614 "diksam.y"
    {
            (yyval.elsif) = dkc_create_elsif((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].block));
        }
    break;

  case 143:
#line 620 "diksam.y"
    {
            (yyval.identifier) = NULL;
        }
    break;

  case 144:
#line 624 "diksam.y"
    {
            (yyval.identifier) = (yyvsp[(1) - (2)].identifier);
        }
    break;

  case 145:
#line 630 "diksam.y"
    {
            (yyval.statement) = dkc_create_switch_statement((yyvsp[(3) - (6)].expression), (yyvsp[(5) - (6)].case_list), (yyvsp[(6) - (6)].block));
        }
    break;

  case 147:
#line 637 "diksam.y"
    {
            (yyval.case_list) = dkc_chain_case((yyvsp[(1) - (2)].case_list), (yyvsp[(2) - (2)].case_list));
        }
    break;

  case 148:
#line 643 "diksam.y"
    {
            (yyval.case_list) = dkc_create_one_case((yyvsp[(2) - (3)].expression_list), (yyvsp[(3) - (3)].block));
        }
    break;

  case 149:
#line 649 "diksam.y"
    {
            (yyval.block) = NULL;
        }
    break;

  case 150:
#line 653 "diksam.y"
    {
            (yyval.block) = (yyvsp[(2) - (2)].block);
        }
    break;

  case 151:
#line 659 "diksam.y"
    {
            (yyval.expression_list) = dkc_create_expression_list((yyvsp[(1) - (1)].expression));
        }
    break;

  case 152:
#line 663 "diksam.y"
    {
            (yyval.expression_list) = dkc_chain_expression_list((yyvsp[(1) - (3)].expression_list), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 153:
#line 669 "diksam.y"
    {
            (yyval.statement) = dkc_create_while_statement((yyvsp[(1) - (6)].identifier), (yyvsp[(4) - (6)].expression), (yyvsp[(6) - (6)].block));
        }
    break;

  case 154:
#line 676 "diksam.y"
    {
            (yyval.statement) = dkc_create_for_statement((yyvsp[(1) - (10)].identifier), (yyvsp[(4) - (10)].expression), (yyvsp[(6) - (10)].expression), (yyvsp[(8) - (10)].expression), (yyvsp[(10) - (10)].block));
        }
    break;

  case 155:
#line 682 "diksam.y"
    {
            (yyval.statement) = dkc_create_do_while_statement((yyvsp[(1) - (8)].identifier), (yyvsp[(3) - (8)].block), (yyvsp[(6) - (8)].expression));
        }
    break;

  case 156:
#line 688 "diksam.y"
    {
            (yyval.statement) = dkc_create_foreach_statement((yyvsp[(1) - (8)].identifier), (yyvsp[(4) - (8)].identifier), (yyvsp[(6) - (8)].expression), (yyvsp[(8) - (8)].block));
        }
    break;

  case 157:
#line 694 "diksam.y"
    {
            (yyval.expression) = NULL;
        }
    break;

  case 159:
#line 701 "diksam.y"
    {
            (yyval.statement) = dkc_create_return_statement((yyvsp[(2) - (3)].expression));
        }
    break;

  case 160:
#line 707 "diksam.y"
    {
            (yyval.identifier) = NULL;
        }
    break;

  case 162:
#line 714 "diksam.y"
    {
            (yyval.statement) = dkc_create_break_statement((yyvsp[(2) - (3)].identifier));
        }
    break;

  case 163:
#line 720 "diksam.y"
    {
            (yyval.statement) = dkc_create_continue_statement((yyvsp[(2) - (3)].identifier));
        }
    break;

  case 164:
#line 726 "diksam.y"
    {
            (yyval.statement) = dkc_create_try_statement((yyvsp[(2) - (5)].block), (yyvsp[(3) - (5)].catch_clause), (yyvsp[(5) - (5)].block));
        }
    break;

  case 165:
#line 730 "diksam.y"
    {
            (yyval.statement) = dkc_create_try_statement((yyvsp[(2) - (4)].block), NULL, (yyvsp[(4) - (4)].block));
        }
    break;

  case 166:
#line 734 "diksam.y"
    {
            (yyval.statement) = dkc_create_try_statement((yyvsp[(2) - (3)].block), (yyvsp[(3) - (3)].catch_clause), NULL);
        }
    break;

  case 168:
#line 741 "diksam.y"
    {
            (yyval.catch_clause) = dkc_chain_catch_list((yyvsp[(1) - (2)].catch_clause), (yyvsp[(2) - (2)].catch_clause));
        }
    break;

  case 169:
#line 747 "diksam.y"
    {
            (yyval.catch_clause) = dkc_start_catch_clause();
        }
    break;

  case 170:
#line 751 "diksam.y"
    {
            (yyval.catch_clause) = dkc_end_catch_clause((yyvsp[(2) - (7)].catch_clause), (yyvsp[(4) - (7)].type_specifier), (yyvsp[(5) - (7)].identifier), (yyvsp[(7) - (7)].block));
        }
    break;

  case 171:
#line 757 "diksam.y"
    {
            (yyval.statement) = dkc_create_throw_statement((yyvsp[(2) - (3)].expression));
        }
    break;

  case 172:
#line 761 "diksam.y"
    {
            (yyval.statement) = dkc_create_throw_statement(NULL);
        }
    break;

  case 173:
#line 767 "diksam.y"
    {
            (yyval.statement) = dkc_create_declaration_statement(DVM_FALSE, (yyvsp[(1) - (3)].type_specifier), (yyvsp[(2) - (3)].identifier), NULL);
        }
    break;

  case 174:
#line 771 "diksam.y"
    {
            (yyval.statement) = dkc_create_declaration_statement(DVM_FALSE, (yyvsp[(1) - (5)].type_specifier), (yyvsp[(2) - (5)].identifier), (yyvsp[(4) - (5)].expression));
        }
    break;

  case 175:
#line 775 "diksam.y"
    {
            (yyval.statement) = dkc_create_declaration_statement(DVM_TRUE, (yyvsp[(2) - (4)].type_specifier), (yyvsp[(3) - (4)].identifier), NULL);
        }
    break;

  case 176:
#line 779 "diksam.y"
    {
            (yyval.statement) = dkc_create_declaration_statement(DVM_TRUE, (yyvsp[(2) - (6)].type_specifier), (yyvsp[(3) - (6)].identifier), (yyvsp[(5) - (6)].expression));
        }
    break;

  case 177:
#line 785 "diksam.y"
    {
            (yyval.block) = dkc_open_block();
        }
    break;

  case 178:
#line 789 "diksam.y"
    {
            (yyval.block) = dkc_close_block((yyvsp[(2) - (4)].block), (yyvsp[(3) - (4)].statement_list));
        }
    break;

  case 179:
#line 793 "diksam.y"
    {
            Block *empty_block = dkc_open_block();
            (yyval.block) = dkc_close_block(empty_block, NULL);
        }
    break;

  case 180:
#line 801 "diksam.y"
    {
            dkc_start_class_definition(NULL, (yyvsp[(1) - (4)].class_or_interface), (yyvsp[(2) - (4)].identifier), (yyvsp[(3) - (4)].extends_list));
        }
    break;

  case 181:
#line 805 "diksam.y"
    {
            dkc_class_define((yyvsp[(6) - (7)].member_declaration));
        }
    break;

  case 182:
#line 810 "diksam.y"
    {
            dkc_start_class_definition(&(yyvsp[(1) - (5)].class_or_member_modifier), (yyvsp[(2) - (5)].class_or_interface), (yyvsp[(3) - (5)].identifier), (yyvsp[(4) - (5)].extends_list));
        }
    break;

  case 183:
#line 813 "diksam.y"
    {
            dkc_class_define((yyvsp[(7) - (8)].member_declaration));
        }
    break;

  case 184:
#line 817 "diksam.y"
    {
            dkc_start_class_definition(NULL, (yyvsp[(1) - (4)].class_or_interface), (yyvsp[(2) - (4)].identifier), (yyvsp[(3) - (4)].extends_list));
        }
    break;

  case 185:
#line 821 "diksam.y"
    {
            dkc_class_define(NULL);
        }
    break;

  case 186:
#line 826 "diksam.y"
    {
            dkc_start_class_definition(&(yyvsp[(1) - (5)].class_or_member_modifier), (yyvsp[(2) - (5)].class_or_interface), (yyvsp[(3) - (5)].identifier), (yyvsp[(4) - (5)].extends_list));
        }
    break;

  case 187:
#line 830 "diksam.y"
    {
            dkc_class_define(NULL);
        }
    break;

  case 189:
#line 837 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_chain_class_or_member_modifier((yyvsp[(1) - (2)].class_or_member_modifier), (yyvsp[(2) - (2)].class_or_member_modifier));
        }
    break;

  case 191:
#line 844 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_create_class_or_member_modifier(VIRTUAL_MODIFIER);
        }
    break;

  case 192:
#line 848 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_create_class_or_member_modifier(OVERRIDE_MODIFIER);
        }
    break;

  case 193:
#line 852 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_create_class_or_member_modifier(ABSTRACT_MODIFIER);
        }
    break;

  case 194:
#line 858 "diksam.y"
    {
            (yyval.class_or_interface) = DVM_CLASS_DEFINITION;
        }
    break;

  case 195:
#line 862 "diksam.y"
    {
            (yyval.class_or_interface) = DVM_INTERFACE_DEFINITION;
        }
    break;

  case 196:
#line 868 "diksam.y"
    {
            (yyval.extends_list) = NULL;
        }
    break;

  case 197:
#line 872 "diksam.y"
    {
            (yyval.extends_list) = (yyvsp[(2) - (2)].extends_list);
        }
    break;

  case 198:
#line 878 "diksam.y"
    {
            (yyval.extends_list) = dkc_create_extends_list((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 199:
#line 882 "diksam.y"
    {
            (yyval.extends_list) = dkc_chain_extends_list((yyvsp[(1) - (3)].extends_list), (yyvsp[(3) - (3)].identifier));
        }
    break;

  case 201:
#line 889 "diksam.y"
    {
            (yyval.member_declaration) = dkc_chain_member_declaration((yyvsp[(1) - (2)].member_declaration), (yyvsp[(2) - (2)].member_declaration));
        }
    break;

  case 204:
#line 899 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_method_member(NULL, (yyvsp[(1) - (1)].function_definition), DVM_FALSE);
        }
    break;

  case 205:
#line 903 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_method_member(&(yyvsp[(1) - (2)].class_or_member_modifier), (yyvsp[(2) - (2)].function_definition), DVM_FALSE);
        }
    break;

  case 206:
#line 907 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_method_member(NULL, (yyvsp[(1) - (1)].function_definition), DVM_TRUE);
        }
    break;

  case 207:
#line 911 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_method_member(&(yyvsp[(1) - (2)].class_or_member_modifier), (yyvsp[(2) - (2)].function_definition), DVM_TRUE);
        }
    break;

  case 208:
#line 917 "diksam.y"
    {
            (yyval.function_definition) = dkc_method_function_define((yyvsp[(1) - (7)].type_specifier), (yyvsp[(2) - (7)].identifier), (yyvsp[(4) - (7)].parameter_list), (yyvsp[(6) - (7)].exception_list), (yyvsp[(7) - (7)].block));
        }
    break;

  case 209:
#line 921 "diksam.y"
    {
            (yyval.function_definition) = dkc_method_function_define((yyvsp[(1) - (6)].type_specifier), (yyvsp[(2) - (6)].identifier), NULL, (yyvsp[(5) - (6)].exception_list), (yyvsp[(6) - (6)].block));
        }
    break;

  case 210:
#line 926 "diksam.y"
    {
            (yyval.function_definition) = dkc_method_function_define((yyvsp[(1) - (7)].type_specifier), (yyvsp[(2) - (7)].identifier), (yyvsp[(4) - (7)].parameter_list), (yyvsp[(6) - (7)].exception_list), NULL);
        }
    break;

  case 211:
#line 930 "diksam.y"
    {
            (yyval.function_definition) = dkc_method_function_define((yyvsp[(1) - (6)].type_specifier), (yyvsp[(2) - (6)].identifier), NULL, (yyvsp[(5) - (6)].exception_list), NULL);
        }
    break;

  case 212:
#line 936 "diksam.y"
    {
            (yyval.exception_list) = NULL;
        }
    break;

  case 213:
#line 940 "diksam.y"
    {
            (yyval.exception_list) = (yyvsp[(2) - (2)].exception_list);
        }
    break;

  case 214:
#line 946 "diksam.y"
    {
            (yyval.exception_list) = dkc_create_throws((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 215:
#line 950 "diksam.y"
    {
            (yyval.exception_list) = dkc_chain_exception_list((yyvsp[(1) - (3)].exception_list), (yyvsp[(3) - (3)].identifier));
        }
    break;

  case 216:
#line 956 "diksam.y"
    {
            (yyval.function_definition) = dkc_constructor_function_define((yyvsp[(2) - (7)].identifier), (yyvsp[(4) - (7)].parameter_list), (yyvsp[(6) - (7)].exception_list), (yyvsp[(7) - (7)].block));
        }
    break;

  case 217:
#line 960 "diksam.y"
    {
            (yyval.function_definition) = dkc_constructor_function_define((yyvsp[(2) - (6)].identifier), NULL, (yyvsp[(5) - (6)].exception_list), (yyvsp[(6) - (6)].block));
        }
    break;

  case 218:
#line 964 "diksam.y"
    {
            (yyval.function_definition) = dkc_constructor_function_define((yyvsp[(2) - (7)].identifier), (yyvsp[(4) - (7)].parameter_list), (yyvsp[(6) - (7)].exception_list), NULL);
        }
    break;

  case 219:
#line 968 "diksam.y"
    {
            (yyval.function_definition) = dkc_constructor_function_define((yyvsp[(2) - (6)].identifier), NULL, (yyvsp[(5) - (6)].exception_list), NULL);
        }
    break;

  case 220:
#line 974 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_create_class_or_member_modifier(PUBLIC_MODIFIER);
        }
    break;

  case 221:
#line 978 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_create_class_or_member_modifier(PRIVATE_MODIFIER);
        }
    break;

  case 222:
#line 984 "diksam.y"
    {
            (yyval.expression) = NULL;
        }
    break;

  case 223:
#line 988 "diksam.y"
    {
            (yyval.expression) = (yyvsp[(2) - (2)].expression);
        }
    break;

  case 224:
#line 994 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_field_member(NULL, DVM_FALSE, (yyvsp[(1) - (4)].type_specifier), (yyvsp[(2) - (4)].identifier), (yyvsp[(3) - (4)].expression));
        }
    break;

  case 225:
#line 999 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_field_member(&(yyvsp[(1) - (5)].class_or_member_modifier), DVM_FALSE, (yyvsp[(2) - (5)].type_specifier), (yyvsp[(3) - (5)].identifier), (yyvsp[(4) - (5)].expression));
        }
    break;

  case 226:
#line 1003 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_field_member(NULL, DVM_TRUE, (yyvsp[(2) - (5)].type_specifier), (yyvsp[(3) - (5)].identifier), (yyvsp[(4) - (5)].expression));
        }
    break;

  case 227:
#line 1008 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_field_member(&(yyvsp[(1) - (6)].class_or_member_modifier), DVM_TRUE, (yyvsp[(3) - (6)].type_specifier), (yyvsp[(4) - (6)].identifier), (yyvsp[(5) - (6)].expression));
        }
    break;

  case 228:
#line 1015 "diksam.y"
    {
            dkc_create_delegate_definition((yyvsp[(2) - (8)].type_specifier), (yyvsp[(3) - (8)].identifier), (yyvsp[(5) - (8)].parameter_list), (yyvsp[(7) - (8)].exception_list));
        }
    break;

  case 229:
#line 1019 "diksam.y"
    {
            dkc_create_delegate_definition((yyvsp[(2) - (7)].type_specifier), (yyvsp[(3) - (7)].identifier), NULL, (yyvsp[(6) - (7)].exception_list));
        }
    break;

  case 230:
#line 1025 "diksam.y"
    {
            dkc_create_enum_definition((yyvsp[(2) - (5)].identifier), (yyvsp[(4) - (5)].enumerator));
        }
    break;

  case 231:
#line 1029 "diksam.y"
    {
            dkc_create_enum_definition((yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].enumerator));
        }
    break;

  case 232:
#line 1035 "diksam.y"
    {
            (yyval.enumerator) = dkc_create_enumerator((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 233:
#line 1039 "diksam.y"
    {
            (yyval.enumerator) = dkc_chain_enumerator((yyvsp[(1) - (3)].enumerator), (yyvsp[(3) - (3)].identifier));
        }
    break;

  case 234:
#line 1045 "diksam.y"
    {
            dkc_create_const_definition(NULL, (yyvsp[(2) - (5)].identifier), (yyvsp[(4) - (5)].expression));
        }
    break;

  case 235:
#line 1049 "diksam.y"
    {
            dkc_create_const_definition((yyvsp[(2) - (4)].type_specifier), (yyvsp[(3) - (4)].identifier), NULL);
        }
    break;


/* Line 1267 of yacc.c.  */
#line 3371 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
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
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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


#line 1053 "diksam.y"


