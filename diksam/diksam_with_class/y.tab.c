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

#include "stdafx.h"

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
     WHILE = 266,
     DO_T = 267,
     FOR = 268,
     FOREACH = 269,
     RETURN_T = 270,
     BREAK = 271,
     CONTINUE = 272,
     NULL_T = 273,
     LP = 274,
     RP = 275,
     LC = 276,
     RC = 277,
     LB = 278,
     RB = 279,
     SEMICOLON = 280,
     COLON = 281,
     COMMA = 282,
     ASSIGN_T = 283,
     LOGICAL_AND = 284,
     LOGICAL_OR = 285,
     EQ = 286,
     NE = 287,
     GT = 288,
     GE = 289,
     LT = 290,
     LE = 291,
     ADD = 292,
     SUB = 293,
     MUL = 294,
     DIV = 295,
     MOD = 296,
     TRUE_T = 297,
     FALSE_T = 298,
     EXCLAMATION = 299,
     DOT = 300,
     ADD_ASSIGN_T = 301,
     SUB_ASSIGN_T = 302,
     MUL_ASSIGN_T = 303,
     DIV_ASSIGN_T = 304,
     MOD_ASSIGN_T = 305,
     INCREMENT = 306,
     DECREMENT = 307,
     VOID_T = 308,
     BOOLEAN_T = 309,
     INT_T = 310,
     DOUBLE_T = 311,
     STRING_T = 312,
     NEW = 313,
     REQUIRE = 314,
     RENAME = 315,
     CLASS_T = 316,
     INTERFACE_T = 317,
     PUBLIC_T = 318,
     PRIVATE_T = 319,
     VIRTUAL_T = 320,
     OVERRIDE_T = 321,
     ABSTRACT_T = 322,
     THIS_T = 323,
     SUPER_T = 324,
     CONSTRUCTOR = 325,
     INSTANCEOF = 326,
     DOWN_CAST_BEGIN = 327,
     DOWN_CAST_END = 328
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
#define WHILE 266
#define DO_T 267
#define FOR 268
#define FOREACH 269
#define RETURN_T 270
#define BREAK 271
#define CONTINUE 272
#define NULL_T 273
#define LP 274
#define RP 275
#define LC 276
#define RC 277
#define LB 278
#define RB 279
#define SEMICOLON 280
#define COLON 281
#define COMMA 282
#define ASSIGN_T 283
#define LOGICAL_AND 284
#define LOGICAL_OR 285
#define EQ 286
#define NE 287
#define GT 288
#define GE 289
#define LT 290
#define LE 291
#define ADD 292
#define SUB 293
#define MUL 294
#define DIV 295
#define MOD 296
#define TRUE_T 297
#define FALSE_T 298
#define EXCLAMATION 299
#define DOT 300
#define ADD_ASSIGN_T 301
#define SUB_ASSIGN_T 302
#define MUL_ASSIGN_T 303
#define DIV_ASSIGN_T 304
#define MOD_ASSIGN_T 305
#define INCREMENT 306
#define DECREMENT 307
#define VOID_T 308
#define BOOLEAN_T 309
#define INT_T 310
#define DOUBLE_T 311
#define STRING_T 312
#define NEW 313
#define REQUIRE 314
#define RENAME 315
#define CLASS_T 316
#define INTERFACE_T 317
#define PUBLIC_T 318
#define PRIVATE_T 319
#define VIRTUAL_T 320
#define OVERRIDE_T 321
#define ABSTRACT_T 322
#define THIS_T 323
#define SUPER_T 324
#define CONSTRUCTOR 325
#define INSTANCEOF 326
#define DOWN_CAST_BEGIN 327
#define DOWN_CAST_END 328




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
    AssignmentOperator  assignment_operator;
    TypeSpecifier       *type_specifier;
    DVM_BasicType       basic_type_specifier;
    ArrayDimension      *array_dimension;
    ClassOrMemberModifierList class_or_member_modifier;
    DVM_ClassOrInterface class_or_interface;
    ExtendsList         *extends_list;
    MemberDeclaration   *member_declaration;
    FunctionDefinition  *function_definition;
}
/* Line 193 of yacc.c.  */
#line 272 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 285 "y.tab.c"

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
#define YYLAST   659

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  189
/* YYNRULES -- Number of states.  */
#define YYNSTATES  330

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    10,    13,    15,    17,    19,
      22,    26,    28,    32,    34,    37,    42,    44,    46,    48,
      50,    52,    54,    56,    58,    60,    64,    68,    72,    74,
      76,    78,    85,    91,    98,   104,   107,   112,   114,   118,
     120,   123,   125,   129,   131,   135,   137,   139,   141,   143,
     145,   147,   149,   153,   155,   159,   161,   165,   169,   171,
     175,   179,   183,   187,   189,   193,   197,   199,   203,   207,
     211,   213,   216,   219,   221,   224,   227,   231,   233,   235,
     237,   242,   247,   251,   256,   260,   264,   269,   271,   273,
     275,   277,   279,   281,   283,   285,   287,   289,   294,   300,
     307,   315,   319,   324,   328,   333,   337,   342,   344,   347,
     351,   354,   358,   359,   361,   365,   368,   370,   372,   374,
     376,   378,   380,   382,   384,   386,   392,   400,   407,   416,
     418,   421,   427,   428,   431,   438,   449,   458,   467,   468,
     470,   474,   475,   477,   481,   485,   489,   495,   496,   501,
     504,   505,   513,   514,   523,   524,   531,   532,   540,   542,
     545,   547,   549,   551,   553,   555,   557,   558,   561,   563,
     567,   569,   572,   574,   576,   578,   581,   583,   586,   593,
     599,   606,   612,   619,   625,   632,   638,   640,   642,   646
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      75,     0,    -1,    76,    82,    -1,    75,    82,    -1,    -1,
      77,    80,    -1,    77,    -1,    80,    -1,    78,    -1,    77,
      78,    -1,    59,    79,    25,    -1,     7,    -1,    79,    45,
       7,    -1,    81,    -1,    80,    81,    -1,    60,    79,     7,
      25,    -1,    87,    -1,   127,    -1,   110,    -1,    53,    -1,
      54,    -1,    55,    -1,    56,    -1,    57,    -1,     7,    -1,
      83,    23,    24,    -1,     7,    23,    24,    -1,    85,    23,
      24,    -1,    83,    -1,    85,    -1,    84,    -1,    86,     7,
      19,    88,    20,   125,    -1,    86,     7,    19,    20,   125,
      -1,    86,     7,    19,    88,    20,    25,    -1,    86,     7,
      19,    20,    25,    -1,    86,     7,    -1,    88,    27,    86,
       7,    -1,    92,    -1,    89,    27,    92,    -1,   110,    -1,
      90,   110,    -1,    92,    -1,    91,    27,    92,    -1,    94,
      -1,   102,    93,    92,    -1,    28,    -1,    46,    -1,    47,
      -1,    48,    -1,    49,    -1,    50,    -1,    95,    -1,    94,
      30,    95,    -1,    96,    -1,    95,    29,    96,    -1,    97,
      -1,    96,    31,    97,    -1,    96,    32,    97,    -1,    98,
      -1,    97,    33,    98,    -1,    97,    34,    98,    -1,    97,
      35,    98,    -1,    97,    36,    98,    -1,    99,    -1,    98,
      37,    99,    -1,    98,    38,    99,    -1,   100,    -1,    99,
      39,   100,    -1,    99,    40,   100,    -1,    99,    41,   100,
      -1,   101,    -1,    38,   100,    -1,    44,   100,    -1,   102,
      -1,   102,    51,    -1,   102,    52,    -1,   102,    71,    86,
      -1,   103,    -1,   105,    -1,     7,    -1,   103,    23,    91,
      24,    -1,     7,    23,    91,    24,    -1,   102,    45,     7,
      -1,   102,    19,    89,    20,    -1,   102,    19,    20,    -1,
      19,    91,    20,    -1,   102,    72,    86,    73,    -1,     3,
      -1,     4,    -1,     5,    -1,     6,    -1,    42,    -1,    43,
      -1,    18,    -1,   104,    -1,    68,    -1,    69,    -1,    58,
       7,    19,    20,    -1,    58,     7,    19,    89,    20,    -1,
      58,     7,    45,     7,    19,    20,    -1,    58,     7,    45,
       7,    19,    89,    20,    -1,    21,   109,    22,    -1,    21,
     109,    27,    22,    -1,    58,    83,   106,    -1,    58,    83,
     106,   108,    -1,    58,    84,   106,    -1,    58,    84,   106,
     108,    -1,   107,    -1,   106,   107,    -1,    23,    91,    24,
      -1,    23,    24,    -1,   108,    23,    24,    -1,    -1,    92,
      -1,   109,    27,    92,    -1,    91,    25,    -1,   111,    -1,
     115,    -1,   116,    -1,   117,    -1,   118,    -1,   120,    -1,
     122,    -1,   123,    -1,   124,    -1,     8,    19,    91,    20,
     125,    -1,     8,    19,    91,    20,   125,     9,   125,    -1,
       8,    19,    91,    20,   125,   112,    -1,     8,    19,    91,
      20,   125,   112,     9,   125,    -1,   113,    -1,   112,   113,
      -1,    10,    19,    91,    20,   125,    -1,    -1,     7,    26,
      -1,   114,    11,    19,    91,    20,   125,    -1,   114,    13,
      19,   119,    25,   119,    25,   119,    20,   125,    -1,   114,
      12,   125,    11,    19,    91,    20,    25,    -1,   114,    14,
      19,     7,    26,    91,    20,   125,    -1,    -1,    91,    -1,
      15,   119,    25,    -1,    -1,     7,    -1,    16,   121,    25,
      -1,    17,   121,    25,    -1,    86,     7,    25,    -1,    86,
       7,    28,    91,    25,    -1,    -1,    21,   126,    90,    22,
      -1,    21,    22,    -1,    -1,   134,     7,   135,    21,   128,
     137,    22,    -1,    -1,   132,   134,     7,   135,    21,   129,
     137,    22,    -1,    -1,   134,     7,   135,    21,   130,    22,
      -1,    -1,   132,   134,     7,   135,    21,   131,    22,    -1,
     133,    -1,   132,   133,    -1,   142,    -1,    65,    -1,    66,
      -1,    67,    -1,    61,    -1,    62,    -1,    -1,    26,   136,
      -1,     7,    -1,   136,    27,     7,    -1,   138,    -1,   137,
     138,    -1,   139,    -1,   143,    -1,   140,    -1,   132,   140,
      -1,   141,    -1,   132,   141,    -1,    86,     7,    19,    88,
      20,   125,    -1,    86,     7,    19,    20,   125,    -1,    86,
       7,    19,    88,    20,    25,    -1,    86,     7,    19,    20,
      25,    -1,    70,     7,    19,    88,    20,   125,    -1,    70,
       7,    19,    20,   125,    -1,    70,     7,    19,    88,    20,
      25,    -1,    70,     7,    19,    20,    25,    -1,    63,    -1,
      64,    -1,    86,     7,    25,    -1,   132,    86,     7,    25,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    83,    83,    84,    88,    91,    95,    99,   105,   106,
     112,   118,   122,   128,   129,   135,   141,   142,   143,   152,
     156,   160,   164,   168,   174,   180,   186,   192,   198,   202,
     203,   206,   210,   214,   219,   225,   229,   235,   239,   245,
     249,   255,   256,   262,   263,   269,   273,   277,   281,   285,
     289,   295,   296,   302,   303,   309,   310,   314,   320,   321,
     325,   329,   333,   339,   340,   344,   350,   351,   355,   359,
     365,   366,   370,   376,   377,   381,   385,   391,   392,   393,
     399,   403,   408,   412,   416,   420,   424,   428,   429,   430,
     431,   432,   436,   440,   444,   445,   449,   453,   457,   461,
     465,   471,   475,   481,   485,   489,   493,   500,   501,   507,
     513,   517,   525,   528,   532,   538,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   553,   557,   561,   565,   571,
     572,   578,   585,   588,   594,   600,   607,   613,   620,   623,
     626,   633,   636,   639,   645,   651,   655,   662,   661,   669,
     678,   676,   687,   685,   694,   693,   703,   701,   712,   713,
     719,   720,   724,   728,   734,   738,   745,   748,   754,   758,
     764,   765,   771,   772,   775,   779,   783,   787,   793,   797,
     801,   806,   812,   816,   820,   824,   830,   834,   840,   844
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_LITERAL", "DOUBLE_LITERAL",
  "STRING_LITERAL", "REGEXP_LITERAL", "IDENTIFIER", "IF", "ELSE", "ELSIF",
  "WHILE", "DO_T", "FOR", "FOREACH", "RETURN_T", "BREAK", "CONTINUE",
  "NULL_T", "LP", "RP", "LC", "RC", "LB", "RB", "SEMICOLON", "COLON",
  "COMMA", "ASSIGN_T", "LOGICAL_AND", "LOGICAL_OR", "EQ", "NE", "GT", "GE",
  "LT", "LE", "ADD", "SUB", "MUL", "DIV", "MOD", "TRUE_T", "FALSE_T",
  "EXCLAMATION", "DOT", "ADD_ASSIGN_T", "SUB_ASSIGN_T", "MUL_ASSIGN_T",
  "DIV_ASSIGN_T", "MOD_ASSIGN_T", "INCREMENT", "DECREMENT", "VOID_T",
  "BOOLEAN_T", "INT_T", "DOUBLE_T", "STRING_T", "NEW", "REQUIRE", "RENAME",
  "CLASS_T", "INTERFACE_T", "PUBLIC_T", "PRIVATE_T", "VIRTUAL_T",
  "OVERRIDE_T", "ABSTRACT_T", "THIS_T", "SUPER_T", "CONSTRUCTOR",
  "INSTANCEOF", "DOWN_CAST_BEGIN", "DOWN_CAST_END", "$accept",
  "translation_unit", "initial_declaration", "require_list",
  "require_declaration", "package_name", "rename_list",
  "rename_declaration", "definition_or_statement", "basic_type_specifier",
  "class_type_specifier", "array_type_specifier", "type_specifier",
  "function_definition", "parameter_list", "argument_list",
  "statement_list", "expression", "assignment_expression",
  "assignment_operator", "logical_or_expression", "logical_and_expression",
  "equality_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "postfix_expression",
  "primary_expression", "primary_no_new_array", "array_literal",
  "array_creation", "dimension_expression_list", "dimension_expression",
  "dimension_list", "expression_list", "statement", "if_statement",
  "elsif_list", "elsif", "label_opt", "while_statement", "for_statement",
  "do_while_statement", "foreach_statement", "expression_opt",
  "return_statement", "identifier_opt", "break_statement",
  "continue_statement", "declaration_statement", "block", "@1",
  "class_definition", "@2", "@3", "@4", "@5",
  "class_or_member_modifier_list", "class_or_member_modifier",
  "class_or_interface", "extends", "extends_list",
  "member_declaration_list", "member_declaration", "method_member",
  "method_function_definition", "constructor_definition",
  "access_modifier", "field_member", 0
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
     325,   326,   327,   328
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    76,    76,    77,    77,
      78,    79,    79,    80,    80,    81,    82,    82,    82,    83,
      83,    83,    83,    83,    84,    85,    85,    85,    86,    86,
      86,    87,    87,    87,    87,    88,    88,    89,    89,    90,
      90,    91,    91,    92,    92,    93,    93,    93,    93,    93,
      93,    94,    94,    95,    95,    96,    96,    96,    97,    97,
      97,    97,    97,    98,    98,    98,    99,    99,    99,    99,
     100,   100,   100,   101,   101,   101,   101,   102,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   105,   105,   105,   105,   106,   106,   107,
     108,   108,   109,   109,   109,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   111,   111,   111,   111,   112,
     112,   113,   114,   114,   115,   116,   117,   118,   119,   119,
     120,   121,   121,   122,   123,   124,   124,   126,   125,   125,
     128,   127,   129,   127,   130,   127,   131,   127,   132,   132,
     133,   133,   133,   133,   134,   134,   135,   135,   136,   136,
     137,   137,   138,   138,   139,   139,   139,   139,   140,   140,
     140,   140,   141,   141,   141,   141,   142,   142,   143,   143
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     1,     1,     1,     2,
       3,     1,     3,     1,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     1,
       1,     6,     5,     6,     5,     2,     4,     1,     3,     1,
       2,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     2,     2,     1,     2,     2,     3,     1,     1,     1,
       4,     4,     3,     4,     3,     3,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     5,     6,
       7,     3,     4,     3,     4,     3,     4,     1,     2,     3,
       2,     3,     0,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     7,     6,     8,     1,
       2,     5,     0,     2,     6,    10,     8,     8,     0,     1,
       3,     0,     1,     3,     3,     3,     5,     0,     4,     2,
       0,     7,     0,     8,     0,     6,     0,     7,     1,     2,
       1,     1,     1,     1,     1,     1,     0,     2,     1,     3,
       1,     2,     1,     1,     1,     2,     1,     2,     6,     5,
       6,     5,     6,     5,     6,     5,     1,     1,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,   132,   132,     6,     8,     7,    13,    11,
       0,     0,     1,    87,    88,    89,    90,    79,     0,   138,
     141,   141,    93,     0,   112,     0,    91,    92,     0,    19,
      20,    21,    22,    23,     0,   164,   165,   186,   187,   161,
     162,   163,    95,    96,     3,    28,    30,    29,     0,    16,
       0,    41,    43,    51,    53,    55,    58,    63,    66,    70,
      73,    77,    94,    78,    18,   116,     0,   117,   118,   119,
     120,   121,   122,   123,   124,    17,     0,   158,     0,   160,
       2,     9,     5,    14,    10,     0,     0,     0,   133,     0,
      79,   139,     0,   142,     0,     0,     0,   113,     0,    71,
      73,    72,    24,     0,     0,     0,     0,     0,   115,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,    47,    48,    49,
      50,    74,    75,     0,     0,     0,     0,     0,     0,     0,
       0,   159,     0,   166,    12,    15,    26,     0,     0,     0,
     140,   143,   144,    85,   101,     0,     0,     0,     0,   103,
     107,   105,    25,    27,     0,   145,     0,    42,    52,    54,
      56,    57,    59,    60,    61,    62,    64,    65,    67,    68,
      69,    84,     0,    37,    82,    24,    76,     0,    44,     0,
       0,   147,     0,   138,     0,   166,     0,     0,    81,     0,
     102,   114,    97,     0,     0,     0,     0,   108,   104,   106,
       0,     0,     0,     0,    83,     0,     0,    86,    80,     0,
     149,   132,     0,     0,     0,     0,   168,   167,   150,   125,
      98,     0,   109,   110,     0,    34,    32,    35,     0,     0,
     146,    38,     0,     0,   132,    39,     0,   138,     0,   152,
       0,     0,     0,     0,     0,   127,   129,    99,     0,   111,
      33,    31,     0,   134,     0,   148,    40,     0,     0,     0,
       0,     0,   169,     0,     0,     0,     0,   170,   172,   174,
     176,   173,   155,   126,     0,     0,   130,   100,    36,     0,
     138,     0,     0,   157,     0,     0,     0,   175,   177,   151,
     171,     0,   128,   136,     0,   137,   153,     0,     0,   188,
       0,     0,     0,     0,     0,     0,     0,   189,   131,   135,
     185,   183,     0,   181,   179,     0,   184,   182,   180,   178
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    10,     7,     8,    44,    45,
      46,    47,   274,    49,   212,   182,   244,    50,    51,   135,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,   159,   160,   208,    98,    64,    65,   255,   256,
      66,    67,    68,    69,    70,    92,    71,    94,    72,    73,
      74,   192,   221,    75,   251,   270,   252,   271,   275,    77,
      78,   197,   227,   276,   277,   278,   279,   280,    79,   281
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -250
static const yytype_int16 yypact[] =
{
     205,    31,    31,   271,   338,   205,  -250,    -5,  -250,  -250,
     -15,     9,  -250,  -250,  -250,  -250,  -250,    18,    41,   561,
      62,    62,  -250,   561,   561,   561,  -250,  -250,   561,  -250,
    -250,  -250,  -250,  -250,   202,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,    66,  -250,    92,   161,  -250,
     177,  -250,   163,   149,   237,   227,   243,   107,  -250,  -250,
      46,   197,  -250,  -250,  -250,  -250,   349,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,   232,  -250,   178,  -250,
    -250,  -250,    -5,  -250,  -250,   220,   207,    15,  -250,   561,
     217,   239,   257,  -250,   266,   283,   101,  -250,     1,  -250,
      71,  -250,   -10,   277,   277,   288,   299,    85,  -250,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     561,   561,   561,    43,  -250,   345,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,   294,   294,   561,   561,   339,   347,   350,
     351,  -250,   364,   346,  -250,  -250,  -250,    13,   113,   561,
    -250,  -250,  -250,  -250,  -250,   148,   477,   366,   561,   352,
    -250,   352,  -250,  -250,    22,  -250,   561,  -250,   149,   237,
     227,   227,   243,   243,   243,   243,   107,   107,  -250,  -250,
    -250,  -250,   117,  -250,  -250,   354,  -250,   301,  -250,    44,
     561,   356,   368,   561,   376,   346,   377,   365,  -250,   347,
    -250,  -250,  -250,   118,   369,    76,   505,  -250,   362,   362,
      99,   380,   144,   180,  -250,   561,   373,  -250,  -250,   152,
    -250,   449,   370,   389,   372,   394,  -250,   363,   395,   275,
    -250,   533,  -250,  -250,   392,  -250,  -250,  -250,   137,   294,
    -250,  -250,   347,   411,   405,  -250,   561,   561,   561,   397,
     418,   589,   406,   347,   410,   293,  -250,  -250,   154,  -250,
    -250,  -250,   423,  -250,   131,  -250,  -250,   155,   407,   157,
     589,   409,  -250,   426,   427,   589,   158,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,   561,   347,  -250,  -250,  -250,   412,
     561,   347,   571,  -250,   416,     7,   429,  -250,  -250,  -250,
    -250,   168,  -250,  -250,   419,  -250,  -250,   143,   263,  -250,
      26,   347,   347,   162,   181,   212,   199,  -250,  -250,  -250,
    -250,  -250,   213,  -250,  -250,   214,  -250,  -250,  -250,  -250
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -250,  -250,  -250,  -250,   433,   438,   436,    -2,   440,   408,
     417,  -250,    -3,  -250,    -1,  -149,  -250,   -17,   -21,  -250,
    -250,   335,   358,   198,   250,   203,   -14,  -250,   132,  -250,
    -250,  -250,   342,  -144,   289,  -250,  -213,  -250,  -250,   216,
    -250,  -250,  -250,  -250,  -250,  -181,  -250,   451,  -250,  -250,
    -250,  -186,  -250,  -250,  -250,  -250,  -250,  -250,   327,   -72,
     399,   281,  -250,   208,  -249,  -250,   204,   210,  -250,  -250
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -157
static const yytype_int16 yytable[] =
{
      48,    48,    91,    97,   141,    83,    96,   203,   245,   156,
      84,    99,   223,   229,   101,   207,    86,   207,    13,    14,
      15,    16,    90,   154,   236,   -24,   308,   300,   155,   185,
      85,   266,   309,    22,    23,   157,    24,   198,     9,   146,
     109,    87,   210,   300,    88,   308,    13,    14,    15,    16,
      90,   317,   261,    25,    85,     2,   263,    26,    27,    28,
      89,    22,    23,   181,    24,   123,   268,   283,   218,    93,
     147,   109,   148,    34,   124,    29,    30,    31,    32,    33,
      83,    25,   258,    42,    43,    26,    27,    28,   167,   105,
     123,   125,   126,   127,   128,   129,   130,   131,   132,   302,
     232,    34,   183,   109,   164,   305,   178,   179,   180,   304,
     165,    42,    43,   166,   188,   106,   125,   133,   134,   189,
     191,   153,   131,   132,   235,   318,   319,   321,   109,   324,
     186,   187,   147,   199,   201,   183,   327,   214,   230,   329,
     109,   205,   133,   134,   215,   215,   120,   121,   122,   213,
     185,    13,    14,    15,    16,    90,   165,   100,   191,   166,
     100,   211,   260,   313,   238,   185,    22,    23,   107,    24,
     200,   239,   242,   219,   287,   289,    91,   291,   111,   109,
     299,   215,   109,   191,   109,   143,    25,   320,   311,   205,
      26,    27,    28,   110,   241,   109,    29,    30,    31,    32,
      33,   322,   108,   141,   109,   240,    34,   109,   239,   102,
     183,    29,    30,    31,    32,    33,    42,    43,   243,   325,
     136,    37,    38,    39,    40,    41,   239,   144,   273,   267,
      91,   269,   145,   191,   191,   191,   262,   323,   326,   328,
     149,   243,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,    29,    30,    31,    32,    33,
     114,   115,   116,   117,     1,     2,   109,   301,   112,   113,
     185,    12,   296,    91,    13,    14,    15,    16,    17,    18,
     118,   119,   150,   315,   253,   254,    19,    20,    21,    22,
      23,   151,    24,    35,    36,    37,    38,    39,    40,    41,
     158,   185,   285,   254,   211,   211,   314,   316,   152,    25,
     170,   171,   162,    26,    27,    28,    29,    30,    31,    32,
      33,   176,   177,   163,    29,    30,    31,    32,    33,    34,
      76,    76,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    13,    14,    15,    16,    17,    18,    29,    30,    31,
      32,    33,   184,    19,    20,    21,    22,    23,   190,    24,
     137,   138,   139,   140,   172,   173,   174,   175,   191,   193,
     194,   195,   196,   204,   217,   206,    25,   216,   220,   222,
      26,    27,    28,   224,   226,   234,   228,   237,   231,   246,
     250,    29,    30,    31,    32,    33,    34,   146,   248,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    13,    14,
      15,    16,    17,    18,   247,   249,   259,  -154,   264,  -156,
      19,    20,    21,    22,    23,   272,    24,   265,   282,   284,
     288,   293,   290,   294,   295,   307,   310,   303,    81,   312,
      11,    82,   103,    25,    80,   168,   161,    26,    27,    28,
     209,   104,    13,    14,    15,    16,    17,    18,    29,    30,
      31,    32,    33,    34,    19,    20,    21,    22,    23,   169,
      24,   286,    95,    42,    43,   142,   225,     0,   292,   297,
      13,    14,    15,    16,    90,   298,     0,    25,     0,     0,
       0,    26,    27,    28,     0,    22,    23,   202,    24,     0,
       0,     0,    29,    30,    31,    32,    33,    34,    13,    14,
      15,    16,    90,     0,     0,    25,     0,    42,    43,    26,
      27,    28,     0,    22,    23,     0,    24,     0,     0,   233,
       0,     0,     0,     0,     0,    34,    13,    14,    15,    16,
      90,     0,     0,    25,     0,    42,    43,    26,    27,    28,
       0,    22,    23,   257,    24,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    13,    14,    15,    16,    90,     0,
       0,    25,     0,    42,    43,    26,    27,    28,   185,    22,
      23,     0,    24,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,   306,     0,     0,   185,     0,     0,    25,
       0,    42,    43,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
       0,     0,     0,     0,    29,    30,    31,    32,    33,    42,
      43,     0,     0,     0,    37,    38,    39,    40,    41,     0,
       0,   273,    29,    30,    31,    32,    33,     0,     0,     0,
       0,     0,    37,    38,    39,    40,    41,     0,     0,   273
};

static const yytype_int16 yycheck[] =
{
       3,     4,    19,    24,    76,     7,    23,   156,   221,    19,
      25,    25,   193,   199,    28,   159,     7,   161,     3,     4,
       5,     6,     7,    22,   210,     7,    19,   276,    27,     7,
      45,   244,    25,    18,    19,    45,    21,    24,     7,    24,
      27,    23,    20,   292,    26,    19,     3,     4,     5,     6,
       7,    25,   238,    38,    45,    60,   242,    42,    43,    44,
      19,    18,    19,    20,    21,    19,   247,   253,    24,     7,
      87,    27,    89,    58,    28,    53,    54,    55,    56,    57,
      82,    38,   231,    68,    69,    42,    43,    44,   109,    23,
      19,    45,    46,    47,    48,    49,    50,    51,    52,   285,
      24,    58,   123,    27,    19,   291,   120,   121,   122,   290,
      25,    68,    69,    28,   135,    23,    45,    71,    72,   136,
      21,    20,    51,    52,    25,   311,   312,   313,    27,   315,
     133,   134,   149,    20,   155,   156,   322,    20,    20,   325,
      27,   158,    71,    72,    27,    27,    39,    40,    41,   166,
       7,     3,     4,     5,     6,     7,    25,    25,    21,    28,
      28,   164,    25,    20,    20,     7,    18,    19,     7,    21,
      22,    27,    20,   190,    20,    20,   193,    20,    29,    27,
      22,    27,    27,    21,    27,     7,    38,    25,    20,   206,
      42,    43,    44,    30,   215,    27,    53,    54,    55,    56,
      57,    20,    25,   275,    27,    25,    58,    27,    27,     7,
     231,    53,    54,    55,    56,    57,    68,    69,   221,    20,
      23,    63,    64,    65,    66,    67,    27,     7,    70,   246,
     247,   248,    25,    21,    21,    21,   239,    25,    25,    25,
      23,   244,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    53,    54,    55,    56,    57,
      33,    34,    35,    36,    59,    60,    27,   284,    31,    32,
       7,     0,   275,   290,     3,     4,     5,     6,     7,     8,
      37,    38,    25,    20,     9,    10,    15,    16,    17,    18,
      19,    25,    21,    61,    62,    63,    64,    65,    66,    67,
      23,     7,     9,    10,   307,   308,   307,   308,    25,    38,
     112,   113,    24,    42,    43,    44,    53,    54,    55,    56,
      57,   118,   119,    24,    53,    54,    55,    56,    57,    58,
       3,     4,    61,    62,    63,    64,    65,    66,    67,    68,
      69,     3,     4,     5,     6,     7,     8,    53,    54,    55,
      56,    57,     7,    15,    16,    17,    18,    19,    19,    21,
      11,    12,    13,    14,   114,   115,   116,   117,    21,    19,
      19,     7,    26,     7,    73,    23,    38,    23,    22,    11,
      42,    43,    44,     7,     7,    23,    21,     7,    19,    19,
      27,    53,    54,    55,    56,    57,    58,    24,    26,    61,
      62,    63,    64,    65,    66,    67,    68,    69,     3,     4,
       5,     6,     7,     8,    25,    21,    24,    22,     7,    22,
      15,    16,    17,    18,    19,     7,    21,    22,    22,    19,
       7,    22,    25,     7,     7,    19,     7,    25,     5,    20,
       2,     5,    34,    38,     4,   110,   104,    42,    43,    44,
     161,    34,     3,     4,     5,     6,     7,     8,    53,    54,
      55,    56,    57,    58,    15,    16,    17,    18,    19,   111,
      21,   255,    21,    68,    69,    76,   195,    -1,   270,   275,
       3,     4,     5,     6,     7,   275,    -1,    38,    -1,    -1,
      -1,    42,    43,    44,    -1,    18,    19,    20,    21,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,     3,     4,
       5,     6,     7,    -1,    -1,    38,    -1,    68,    69,    42,
      43,    44,    -1,    18,    19,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    58,     3,     4,     5,     6,
       7,    -1,    -1,    38,    -1,    68,    69,    42,    43,    44,
      -1,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,     3,     4,     5,     6,     7,    -1,
      -1,    38,    -1,    68,    69,    42,    43,    44,     7,    18,
      19,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    22,    -1,    -1,     7,    -1,    -1,    38,
      -1,    68,    69,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    68,
      69,    -1,    -1,    -1,    63,    64,    65,    66,    67,    -1,
      -1,    70,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    67,    -1,    -1,    70
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    59,    60,    75,    76,    77,    78,    80,    81,     7,
      79,    79,     0,     3,     4,     5,     6,     7,     8,    15,
      16,    17,    18,    19,    21,    38,    42,    43,    44,    53,
      54,    55,    56,    57,    58,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    82,    83,    84,    85,    86,    87,
      91,    92,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   110,   111,   114,   115,   116,   117,
     118,   120,   122,   123,   124,   127,   132,   133,   134,   142,
      82,    78,    80,    81,    25,    45,     7,    23,    26,    19,
       7,    91,   119,     7,   121,   121,    91,    92,   109,   100,
     102,   100,     7,    83,    84,    23,    23,     7,    25,    27,
      30,    29,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    19,    28,    45,    46,    47,    48,    49,
      50,    51,    52,    71,    72,    93,    23,    11,    12,    13,
      14,   133,   134,     7,     7,    25,    24,    91,    91,    23,
      25,    25,    25,    20,    22,    27,    19,    45,    23,   106,
     107,   106,    24,    24,    19,    25,    28,    92,    95,    96,
      97,    97,    98,    98,    98,    98,    99,    99,   100,   100,
     100,    20,    89,    92,     7,     7,    86,    86,    92,    91,
      19,    21,   125,    19,    19,     7,    26,   135,    24,    20,
      22,    92,    20,    89,     7,    91,    23,   107,   108,   108,
      20,    86,    88,    91,    20,    27,    23,    73,    24,    91,
      22,   126,    11,   119,     7,   135,     7,   136,    21,   125,
      20,    19,    24,    24,    23,    25,   125,     7,    20,    27,
      25,    92,    20,    86,    90,   110,    19,    25,    26,    21,
      27,   128,   130,     9,    10,   112,   113,    20,    89,    24,
      25,   125,    86,   125,     7,    22,   110,    91,   119,    91,
     129,   131,     7,    70,    86,   132,   137,   138,   139,   140,
     141,   143,    22,   125,    19,     9,   113,    20,     7,    20,
      25,    20,   137,    22,     7,     7,    86,   140,   141,    22,
     138,    91,   125,    25,   119,   125,    22,    19,    19,    25,
       7,    20,    20,    20,    88,    20,    88,    25,   125,   125,
      25,   125,    20,    25,   125,    20,    25,   125,    25,   125
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
#line 88 "diksam.y"
    {
            dkc_set_require_and_rename_list(NULL, NULL);
        }
    break;

  case 5:
#line 92 "diksam.y"
    {
            dkc_set_require_and_rename_list((yyvsp[(1) - (2)].require_list), (yyvsp[(2) - (2)].rename_list));
        }
    break;

  case 6:
#line 96 "diksam.y"
    {
            dkc_set_require_and_rename_list((yyvsp[(1) - (1)].require_list), NULL);
        }
    break;

  case 7:
#line 100 "diksam.y"
    {
            dkc_set_require_and_rename_list(NULL, (yyvsp[(1) - (1)].rename_list));
        }
    break;

  case 9:
#line 107 "diksam.y"
    {
            (yyval.require_list) = dkc_chain_require_list((yyvsp[(1) - (2)].require_list), (yyvsp[(2) - (2)].require_list));
        }
    break;

  case 10:
#line 113 "diksam.y"
    {
            (yyval.require_list) = dkc_create_require_list((yyvsp[(2) - (3)].package_name));
        }
    break;

  case 11:
#line 119 "diksam.y"
    {
            (yyval.package_name) = dkc_create_package_name((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 12:
#line 123 "diksam.y"
    {
            (yyval.package_name) = dkc_chain_package_name((yyvsp[(1) - (3)].package_name), (yyvsp[(3) - (3)].identifier));
        }
    break;

  case 14:
#line 130 "diksam.y"
    {
            (yyval.rename_list) = dkc_chain_rename_list((yyvsp[(1) - (2)].rename_list), (yyvsp[(2) - (2)].rename_list));
        }
    break;

  case 15:
#line 136 "diksam.y"
    {
            (yyval.rename_list) = dkc_create_rename_list((yyvsp[(2) - (4)].package_name), (yyvsp[(3) - (4)].identifier));
        }
    break;

  case 18:
#line 144 "diksam.y"
    {
            DKC_Compiler *compiler = dkc_get_current_compiler();

            compiler->statement_list
                = dkc_chain_statement_list(compiler->statement_list, (yyvsp[(1) - (1)].statement));
        }
    break;

  case 19:
#line 153 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_VOID_TYPE;
        }
    break;

  case 20:
#line 157 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_BOOLEAN_TYPE;
        }
    break;

  case 21:
#line 161 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_INT_TYPE;
        }
    break;

  case 22:
#line 165 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_DOUBLE_TYPE;
        }
    break;

  case 23:
#line 169 "diksam.y"
    {
            (yyval.basic_type_specifier) = DVM_STRING_TYPE;
        }
    break;

  case 24:
#line 175 "diksam.y"
    {
            (yyval.type_specifier) = dkc_create_class_type_specifier((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 25:
#line 181 "diksam.y"
    {
            TypeSpecifier *basic_type
                = dkc_create_type_specifier((yyvsp[(1) - (3)].basic_type_specifier));
            (yyval.type_specifier) = dkc_create_array_type_specifier(basic_type);
        }
    break;

  case 26:
#line 187 "diksam.y"
    {
            TypeSpecifier *class_type
                = dkc_create_class_type_specifier((yyvsp[(1) - (3)].identifier));
            (yyval.type_specifier) = dkc_create_array_type_specifier(class_type);
        }
    break;

  case 27:
#line 193 "diksam.y"
    {
            (yyval.type_specifier) = dkc_create_array_type_specifier((yyvsp[(1) - (3)].type_specifier));
        }
    break;

  case 28:
#line 199 "diksam.y"
    {
                    (yyval.type_specifier) = dkc_create_type_specifier((yyvsp[(1) - (1)].basic_type_specifier));
        }
    break;

  case 31:
#line 207 "diksam.y"
    {
            dkc_function_define((yyvsp[(1) - (6)].type_specifier), (yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].parameter_list), (yyvsp[(6) - (6)].block));
        }
    break;

  case 32:
#line 211 "diksam.y"
    {
            dkc_function_define((yyvsp[(1) - (5)].type_specifier), (yyvsp[(2) - (5)].identifier), NULL, (yyvsp[(5) - (5)].block));
        }
    break;

  case 33:
#line 216 "diksam.y"
    {
            dkc_function_define((yyvsp[(1) - (6)].type_specifier), (yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].parameter_list), NULL);
        }
    break;

  case 34:
#line 220 "diksam.y"
    {
            dkc_function_define((yyvsp[(1) - (5)].type_specifier), (yyvsp[(2) - (5)].identifier), NULL, NULL);
        }
    break;

  case 35:
#line 226 "diksam.y"
    {
            (yyval.parameter_list) = dkc_create_parameter((yyvsp[(1) - (2)].type_specifier), (yyvsp[(2) - (2)].identifier));
        }
    break;

  case 36:
#line 230 "diksam.y"
    {
            (yyval.parameter_list) = dkc_chain_parameter((yyvsp[(1) - (4)].parameter_list), (yyvsp[(3) - (4)].type_specifier), (yyvsp[(4) - (4)].identifier));
        }
    break;

  case 37:
#line 236 "diksam.y"
    {
            (yyval.argument_list) = dkc_create_argument_list((yyvsp[(1) - (1)].expression));
        }
    break;

  case 38:
#line 240 "diksam.y"
    {
            (yyval.argument_list) = dkc_chain_argument_list((yyvsp[(1) - (3)].argument_list), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 39:
#line 246 "diksam.y"
    {
            (yyval.statement_list) = dkc_create_statement_list((yyvsp[(1) - (1)].statement));
        }
    break;

  case 40:
#line 250 "diksam.y"
    {
            (yyval.statement_list) = dkc_chain_statement_list((yyvsp[(1) - (2)].statement_list), (yyvsp[(2) - (2)].statement));
        }
    break;

  case 42:
#line 257 "diksam.y"
    {
            (yyval.expression) = dkc_create_comma_expression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 44:
#line 264 "diksam.y"
    {
            (yyval.expression) = dkc_create_assign_expression((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].assignment_operator), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 45:
#line 270 "diksam.y"
    {
            (yyval.assignment_operator) = NORMAL_ASSIGN;
        }
    break;

  case 46:
#line 274 "diksam.y"
    {
            (yyval.assignment_operator) = ADD_ASSIGN;
        }
    break;

  case 47:
#line 278 "diksam.y"
    {
            (yyval.assignment_operator) = SUB_ASSIGN;
        }
    break;

  case 48:
#line 282 "diksam.y"
    {
            (yyval.assignment_operator) = MUL_ASSIGN;
        }
    break;

  case 49:
#line 286 "diksam.y"
    {
            (yyval.assignment_operator) = DIV_ASSIGN;
        }
    break;

  case 50:
#line 290 "diksam.y"
    {
            (yyval.assignment_operator) = MOD_ASSIGN;
        }
    break;

  case 52:
#line 297 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(LOGICAL_OR_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 54:
#line 304 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(LOGICAL_AND_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 56:
#line 311 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(EQ_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 57:
#line 315 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(NE_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 59:
#line 322 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(GT_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 60:
#line 326 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(GE_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 61:
#line 330 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(LT_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 62:
#line 334 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(LE_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 64:
#line 341 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(ADD_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 65:
#line 345 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(SUB_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 67:
#line 352 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(MUL_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 68:
#line 356 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(DIV_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 69:
#line 360 "diksam.y"
    {
            (yyval.expression) = dkc_create_binary_expression(MOD_EXPRESSION, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 71:
#line 367 "diksam.y"
    {
            (yyval.expression) = dkc_create_minus_expression((yyvsp[(2) - (2)].expression));
        }
    break;

  case 72:
#line 371 "diksam.y"
    {
            (yyval.expression) = dkc_create_logical_not_expression((yyvsp[(2) - (2)].expression));
        }
    break;

  case 74:
#line 378 "diksam.y"
    {
            (yyval.expression) = dkc_create_incdec_expression((yyvsp[(1) - (2)].expression), INCREMENT_EXPRESSION);
        }
    break;

  case 75:
#line 382 "diksam.y"
    {
            (yyval.expression) = dkc_create_incdec_expression((yyvsp[(1) - (2)].expression), DECREMENT_EXPRESSION);
        }
    break;

  case 76:
#line 386 "diksam.y"
    {
            (yyval.expression) = dkc_create_instanceof_expression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].type_specifier));
        }
    break;

  case 79:
#line 394 "diksam.y"
    {
            (yyval.expression) = dkc_create_identifier_expression((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 80:
#line 400 "diksam.y"
    {
            (yyval.expression) = dkc_create_index_expression((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression));
        }
    break;

  case 81:
#line 404 "diksam.y"
    {
            Expression *identifier = dkc_create_identifier_expression((yyvsp[(1) - (4)].identifier));
            (yyval.expression) = dkc_create_index_expression(identifier, (yyvsp[(3) - (4)].expression));
        }
    break;

  case 82:
#line 409 "diksam.y"
    {
            (yyval.expression) = dkc_create_member_expression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].identifier));
        }
    break;

  case 83:
#line 413 "diksam.y"
    {
            (yyval.expression) = dkc_create_function_call_expression((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].argument_list));
        }
    break;

  case 84:
#line 417 "diksam.y"
    {
            (yyval.expression) = dkc_create_function_call_expression((yyvsp[(1) - (3)].expression), NULL);
        }
    break;

  case 85:
#line 421 "diksam.y"
    {
            (yyval.expression) = (yyvsp[(2) - (3)].expression);
        }
    break;

  case 86:
#line 425 "diksam.y"
    {
            (yyval.expression) = dkc_create_down_cast_expression((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].type_specifier));
        }
    break;

  case 91:
#line 433 "diksam.y"
    {
            (yyval.expression) = dkc_create_boolean_expression(DVM_TRUE);
        }
    break;

  case 92:
#line 437 "diksam.y"
    {
            (yyval.expression) = dkc_create_boolean_expression(DVM_FALSE);
        }
    break;

  case 93:
#line 441 "diksam.y"
    {
            (yyval.expression) = dkc_create_null_expression();
        }
    break;

  case 95:
#line 446 "diksam.y"
    {
            (yyval.expression) = dkc_create_this_expression();
        }
    break;

  case 96:
#line 450 "diksam.y"
    {
            (yyval.expression) = dkc_create_super_expression();
        }
    break;

  case 97:
#line 454 "diksam.y"
    {
            (yyval.expression) = dkc_create_new_expression((yyvsp[(2) - (4)].identifier), NULL, NULL);
        }
    break;

  case 98:
#line 458 "diksam.y"
    {
            (yyval.expression) = dkc_create_new_expression((yyvsp[(2) - (5)].identifier), NULL, (yyvsp[(4) - (5)].argument_list));
        }
    break;

  case 99:
#line 462 "diksam.y"
    {
            (yyval.expression) = dkc_create_new_expression((yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].identifier), NULL);
        }
    break;

  case 100:
#line 466 "diksam.y"
    {
            (yyval.expression) = dkc_create_new_expression((yyvsp[(2) - (7)].identifier), (yyvsp[(4) - (7)].identifier), (yyvsp[(6) - (7)].argument_list));
        }
    break;

  case 101:
#line 472 "diksam.y"
    {
            (yyval.expression) = dkc_create_array_literal_expression((yyvsp[(2) - (3)].expression_list));
        }
    break;

  case 102:
#line 476 "diksam.y"
    {
            (yyval.expression) = dkc_create_array_literal_expression((yyvsp[(2) - (4)].expression_list));
        }
    break;

  case 103:
#line 482 "diksam.y"
    {
            (yyval.expression) = dkc_create_basic_array_creation((yyvsp[(2) - (3)].basic_type_specifier), (yyvsp[(3) - (3)].array_dimension), NULL);
        }
    break;

  case 104:
#line 486 "diksam.y"
    {
            (yyval.expression) = dkc_create_basic_array_creation((yyvsp[(2) - (4)].basic_type_specifier), (yyvsp[(3) - (4)].array_dimension), (yyvsp[(4) - (4)].array_dimension));
        }
    break;

  case 105:
#line 490 "diksam.y"
    {
            (yyval.expression) = dkc_create_class_array_creation((yyvsp[(2) - (3)].type_specifier), (yyvsp[(3) - (3)].array_dimension), NULL);
        }
    break;

  case 106:
#line 495 "diksam.y"
    {
            (yyval.expression) = dkc_create_class_array_creation((yyvsp[(2) - (4)].type_specifier), (yyvsp[(3) - (4)].array_dimension), (yyvsp[(4) - (4)].array_dimension));
        }
    break;

  case 108:
#line 502 "diksam.y"
    {
            (yyval.array_dimension) = dkc_chain_array_dimension((yyvsp[(1) - (2)].array_dimension), (yyvsp[(2) - (2)].array_dimension));
        }
    break;

  case 109:
#line 508 "diksam.y"
    {
            (yyval.array_dimension) = dkc_create_array_dimension((yyvsp[(2) - (3)].expression));
        }
    break;

  case 110:
#line 514 "diksam.y"
    {
            (yyval.array_dimension) = dkc_create_array_dimension(NULL);
        }
    break;

  case 111:
#line 518 "diksam.y"
    {
            (yyval.array_dimension) = dkc_chain_array_dimension((yyvsp[(1) - (3)].array_dimension),
                                           dkc_create_array_dimension(NULL));
        }
    break;

  case 112:
#line 525 "diksam.y"
    {
            (yyval.expression_list) = NULL;
        }
    break;

  case 113:
#line 529 "diksam.y"
    {
            (yyval.expression_list) = dkc_create_expression_list((yyvsp[(1) - (1)].expression));
        }
    break;

  case 114:
#line 533 "diksam.y"
    {
            (yyval.expression_list) = dkc_chain_expression_list((yyvsp[(1) - (3)].expression_list), (yyvsp[(3) - (3)].expression));
        }
    break;

  case 115:
#line 539 "diksam.y"
    {
          (yyval.statement) = dkc_create_expression_statement((yyvsp[(1) - (2)].expression));
        }
    break;

  case 125:
#line 554 "diksam.y"
    {
            (yyval.statement) = dkc_create_if_statement((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].block), NULL, NULL);
        }
    break;

  case 126:
#line 558 "diksam.y"
    {
            (yyval.statement) = dkc_create_if_statement((yyvsp[(3) - (7)].expression), (yyvsp[(5) - (7)].block), NULL, (yyvsp[(7) - (7)].block));
        }
    break;

  case 127:
#line 562 "diksam.y"
    {
            (yyval.statement) = dkc_create_if_statement((yyvsp[(3) - (6)].expression), (yyvsp[(5) - (6)].block), (yyvsp[(6) - (6)].elsif), NULL);
        }
    break;

  case 128:
#line 566 "diksam.y"
    {
            (yyval.statement) = dkc_create_if_statement((yyvsp[(3) - (8)].expression), (yyvsp[(5) - (8)].block), (yyvsp[(6) - (8)].elsif), (yyvsp[(8) - (8)].block));
        }
    break;

  case 130:
#line 573 "diksam.y"
    {
            (yyval.elsif) = dkc_chain_elsif_list((yyvsp[(1) - (2)].elsif), (yyvsp[(2) - (2)].elsif));
        }
    break;

  case 131:
#line 579 "diksam.y"
    {
            (yyval.elsif) = dkc_create_elsif((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].block));
        }
    break;

  case 132:
#line 585 "diksam.y"
    {
            (yyval.identifier) = NULL;
        }
    break;

  case 133:
#line 589 "diksam.y"
    {
            (yyval.identifier) = (yyvsp[(1) - (2)].identifier);
        }
    break;

  case 134:
#line 595 "diksam.y"
    {
            (yyval.statement) = dkc_create_while_statement((yyvsp[(1) - (6)].identifier), (yyvsp[(4) - (6)].expression), (yyvsp[(6) - (6)].block));
        }
    break;

  case 135:
#line 602 "diksam.y"
    {
            (yyval.statement) = dkc_create_for_statement((yyvsp[(1) - (10)].identifier), (yyvsp[(4) - (10)].expression), (yyvsp[(6) - (10)].expression), (yyvsp[(8) - (10)].expression), (yyvsp[(10) - (10)].block));
        }
    break;

  case 136:
#line 608 "diksam.y"
    {
            (yyval.statement) = dkc_create_do_while_statement((yyvsp[(1) - (8)].identifier), (yyvsp[(3) - (8)].block), (yyvsp[(6) - (8)].expression));
        }
    break;

  case 137:
#line 614 "diksam.y"
    {
            (yyval.statement) = dkc_create_foreach_statement((yyvsp[(1) - (8)].identifier), (yyvsp[(4) - (8)].identifier), (yyvsp[(6) - (8)].expression), (yyvsp[(8) - (8)].block));
        }
    break;

  case 138:
#line 620 "diksam.y"
    {
            (yyval.expression) = NULL;
        }
    break;

  case 140:
#line 627 "diksam.y"
    {
            (yyval.statement) = dkc_create_return_statement((yyvsp[(2) - (3)].expression));
        }
    break;

  case 141:
#line 633 "diksam.y"
    {
            (yyval.identifier) = NULL;
        }
    break;

  case 143:
#line 640 "diksam.y"
    {
            (yyval.statement) = dkc_create_break_statement((yyvsp[(2) - (3)].identifier));
        }
    break;

  case 144:
#line 646 "diksam.y"
    {
            (yyval.statement) = dkc_create_continue_statement((yyvsp[(2) - (3)].identifier));
        }
    break;

  case 145:
#line 652 "diksam.y"
    {
            (yyval.statement) = dkc_create_declaration_statement((yyvsp[(1) - (3)].type_specifier), (yyvsp[(2) - (3)].identifier), NULL);
        }
    break;

  case 146:
#line 656 "diksam.y"
    {
            (yyval.statement) = dkc_create_declaration_statement((yyvsp[(1) - (5)].type_specifier), (yyvsp[(2) - (5)].identifier), (yyvsp[(4) - (5)].expression));
        }
    break;

  case 147:
#line 662 "diksam.y"
    {
            (yyval.block) = dkc_open_block();
        }
    break;

  case 148:
#line 666 "diksam.y"
    {
            (yyval.block) = dkc_close_block((yyvsp[(2) - (4)].block), (yyvsp[(3) - (4)].statement_list));
        }
    break;

  case 149:
#line 670 "diksam.y"
    {
            Block *empty_block = dkc_open_block();
            (yyval.block) = dkc_close_block(empty_block, NULL);
        }
    break;

  case 150:
#line 678 "diksam.y"
    {
            dkc_start_class_definition(NULL, (yyvsp[(1) - (4)].class_or_interface), (yyvsp[(2) - (4)].identifier), (yyvsp[(3) - (4)].extends_list));
        }
    break;

  case 151:
#line 682 "diksam.y"
    {
            dkc_class_define((yyvsp[(6) - (7)].member_declaration));
        }
    break;

  case 152:
#line 687 "diksam.y"
    {
            dkc_start_class_definition(&(yyvsp[(1) - (5)].class_or_member_modifier), (yyvsp[(2) - (5)].class_or_interface), (yyvsp[(3) - (5)].identifier), (yyvsp[(4) - (5)].extends_list));
        }
    break;

  case 153:
#line 690 "diksam.y"
    {
            dkc_class_define((yyvsp[(7) - (8)].member_declaration));
        }
    break;

  case 154:
#line 694 "diksam.y"
    {
            dkc_start_class_definition(NULL, (yyvsp[(1) - (4)].class_or_interface), (yyvsp[(2) - (4)].identifier), (yyvsp[(3) - (4)].extends_list));
        }
    break;

  case 155:
#line 698 "diksam.y"
    {
            dkc_class_define(NULL);
        }
    break;

  case 156:
#line 703 "diksam.y"
    {
            dkc_start_class_definition(&(yyvsp[(1) - (5)].class_or_member_modifier), (yyvsp[(2) - (5)].class_or_interface), (yyvsp[(3) - (5)].identifier), (yyvsp[(4) - (5)].extends_list));
        }
    break;

  case 157:
#line 707 "diksam.y"
    {
            dkc_class_define(NULL);
        }
    break;

  case 159:
#line 714 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_chain_class_or_member_modifier((yyvsp[(1) - (2)].class_or_member_modifier), (yyvsp[(2) - (2)].class_or_member_modifier));
        }
    break;

  case 161:
#line 721 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_create_class_or_member_modifier(VIRTUAL_MODIFIER);
        }
    break;

  case 162:
#line 725 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_create_class_or_member_modifier(OVERRIDE_MODIFIER);
        }
    break;

  case 163:
#line 729 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_create_class_or_member_modifier(ABSTRACT_MODIFIER);
        }
    break;

  case 164:
#line 735 "diksam.y"
    {
            (yyval.class_or_interface) = DVM_CLASS_DEFINITION;
        }
    break;

  case 165:
#line 739 "diksam.y"
    {
            (yyval.class_or_interface) = DVM_INTERFACE_DEFINITION;
        }
    break;

  case 166:
#line 745 "diksam.y"
    {
            (yyval.extends_list) = NULL;
        }
    break;

  case 167:
#line 749 "diksam.y"
    {
            (yyval.extends_list) = (yyvsp[(2) - (2)].extends_list);
        }
    break;

  case 168:
#line 755 "diksam.y"
    {
            (yyval.extends_list) = dkc_create_extends_list((yyvsp[(1) - (1)].identifier));
        }
    break;

  case 169:
#line 759 "diksam.y"
    {
            (yyval.extends_list) = dkc_chain_extends_list((yyvsp[(1) - (3)].extends_list), (yyvsp[(3) - (3)].identifier));
        }
    break;

  case 171:
#line 766 "diksam.y"
    {
            (yyval.member_declaration) = dkc_chain_member_declaration((yyvsp[(1) - (2)].member_declaration), (yyvsp[(2) - (2)].member_declaration));
        }
    break;

  case 174:
#line 776 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_method_member(NULL, (yyvsp[(1) - (1)].function_definition), DVM_FALSE);
        }
    break;

  case 175:
#line 780 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_method_member(&(yyvsp[(1) - (2)].class_or_member_modifier), (yyvsp[(2) - (2)].function_definition), DVM_FALSE);
        }
    break;

  case 176:
#line 784 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_method_member(NULL, (yyvsp[(1) - (1)].function_definition), DVM_TRUE);
        }
    break;

  case 177:
#line 788 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_method_member(&(yyvsp[(1) - (2)].class_or_member_modifier), (yyvsp[(2) - (2)].function_definition), DVM_TRUE);
        }
    break;

  case 178:
#line 794 "diksam.y"
    {
            (yyval.function_definition) = dkc_method_function_define((yyvsp[(1) - (6)].type_specifier), (yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].parameter_list), (yyvsp[(6) - (6)].block));
        }
    break;

  case 179:
#line 798 "diksam.y"
    {
            (yyval.function_definition) = dkc_method_function_define((yyvsp[(1) - (5)].type_specifier), (yyvsp[(2) - (5)].identifier), NULL, (yyvsp[(5) - (5)].block));
        }
    break;

  case 180:
#line 803 "diksam.y"
    {
            (yyval.function_definition) = dkc_method_function_define((yyvsp[(1) - (6)].type_specifier), (yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].parameter_list), NULL);
        }
    break;

  case 181:
#line 807 "diksam.y"
    {
            (yyval.function_definition) = dkc_method_function_define((yyvsp[(1) - (5)].type_specifier), (yyvsp[(2) - (5)].identifier), NULL, NULL);
        }
    break;

  case 182:
#line 813 "diksam.y"
    {
            (yyval.function_definition) = dkc_constructor_function_define((yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].parameter_list), (yyvsp[(6) - (6)].block));
        }
    break;

  case 183:
#line 817 "diksam.y"
    {
            (yyval.function_definition) = dkc_constructor_function_define((yyvsp[(2) - (5)].identifier), NULL, (yyvsp[(5) - (5)].block));
        }
    break;

  case 184:
#line 821 "diksam.y"
    {
            (yyval.function_definition) = dkc_constructor_function_define((yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].parameter_list), NULL);
        }
    break;

  case 185:
#line 825 "diksam.y"
    {
            (yyval.function_definition) = dkc_constructor_function_define((yyvsp[(2) - (5)].identifier), NULL, NULL);
        }
    break;

  case 186:
#line 831 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_create_class_or_member_modifier(PUBLIC_MODIFIER);
        }
    break;

  case 187:
#line 835 "diksam.y"
    {
            (yyval.class_or_member_modifier) = dkc_create_class_or_member_modifier(PRIVATE_MODIFIER);
        }
    break;

  case 188:
#line 841 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_field_member(NULL, (yyvsp[(1) - (3)].type_specifier), (yyvsp[(2) - (3)].identifier));
        }
    break;

  case 189:
#line 846 "diksam.y"
    {
            (yyval.member_declaration) = dkc_create_field_member(&(yyvsp[(1) - (4)].class_or_member_modifier), (yyvsp[(2) - (4)].type_specifier), (yyvsp[(3) - (4)].identifier));
        }
    break;


/* Line 1267 of yacc.c.  */
#line 2910 "y.tab.c"
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


#line 850 "diksam.y"


