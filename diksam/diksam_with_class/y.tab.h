/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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

#include "stdafx.h"

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
/* Line 1529 of yacc.c.  */
#line 219 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

