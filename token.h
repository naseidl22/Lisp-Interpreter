#ifndef TOKEN_H
#define TOKEN_H

#include "sexpr.h"

typedef enum{
  LEFT_PAREN,
  RIGHT_PAREN,
  SYMBOL,
  STRING,
  NUMBER,
  SINGLE_QUOTE,
  DOUBLE_QUOTE,
  END_OF_FILE,
  SPACE,
  DOT,
  PLUS,
  MINUS,
  STAR,
  SLASH,
  EQUAL,
  LESS,
  GREATER,
  //Keywords
  EVAL,
  QUOTE,
  DEFINE,
  SET,
  CONS,
  COND,
  CAR,
  CDR,
  //Keyword conditionals and operators
  AND,
  OR,
  IS_NUMBER,
  IS_SYMBOL,
  IS_LIST,
  IS_NIL,
  IS_EQ,
} TokenType;

typedef struct {
  TokenType type;
  char *lexeme;
  LiteralVal literal;
  int line;
} Token;

#endif