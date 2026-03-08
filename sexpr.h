#ifndef SEXPR_H
#define SEXPR_H
#include <stdio.h>
#include <string>

/*
Sexpr => Atom | List

List> => '(' Concs ')'

Cdr => Concs | NIL

Concs => Sexpr  Cdr

Atom => Number | Symbol | String | NIL

NIL => epsilon
*/

struct Sexpr;
struct Consc;

typedef union {
  float number;
  const char* string; //using const char* so I can avoid using classes
  const char* symbol; // technically don't need both of these, but it's more clear to keep them separate
} LiteralVal;

typedef enum {
  NUMBER_ATOM,
  STRING_ATOM,
  SYMBOL_ATOM,
  NIL_ATOM,
} AtomType;

typedef enum {
  LIST_SEXPR,
  ATOM_SEXPR,
  TRUTH_SEXPR,
  NIL_SEXPR,
} SexprType;

typedef struct {
  AtomType type;
  LiteralVal value;
} Atom;

typedef struct Consc {
  Sexpr *car;
  Consc *cdr;
} Consc; // cons cell

typedef struct {
  Consc *consc;
} List;

typedef union {
  Atom atom;
  List list;
} SexprValue;

typedef struct Sexpr {
  SexprType type;
  SexprValue value;
} Sexpr;

std::string sexprToString(Sexpr* sexpr);
bool isNil(Sexpr* sexpr);
bool isSymbol(Sexpr* sexpr);
bool isNumber(Sexpr* sexpr);
bool isString(Sexpr* sexpr);
bool isList(Sexpr* sexpr);
bool isAtom(Sexpr* sexpr);

Sexpr *createAtom(float value);
Sexpr *createAtom(AtomType type, const char * value);
Sexpr *createList();
Sexpr *cons(Sexpr *car, Consc *cdr);
Sexpr *createTruth();
Sexpr *createNil();


Sexpr *add(Sexpr *a, Sexpr *b);
Sexpr *sub(Sexpr *a, Sexpr *b);
Sexpr *mul(Sexpr *a, Sexpr *b);
Sexpr *div(Sexpr *a, Sexpr *b);
Sexpr *mod(Sexpr *a, Sexpr *b);
bool lt(Sexpr *a, Sexpr *b);
bool gt(Sexpr *a, Sexpr *b);
bool lte(Sexpr *a, Sexpr *b);
bool gte(Sexpr *a, Sexpr *b);
bool eq(Sexpr *a, Sexpr *b);

#endif