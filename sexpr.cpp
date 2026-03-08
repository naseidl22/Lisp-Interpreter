#include "sexpr.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

std::string sexprToString(Sexpr *sexpr) {
  std::string print_str = "";

  if (sexpr == nullptr) {
    return print_str;
  }

  if (sexpr->type == ATOM_SEXPR) { // if sexpr is an atom
    switch (sexpr->value.atom.type) {
    case NUMBER_ATOM:
      print_str = std::to_string(sexpr->value.atom.value.number);
      break;
    case STRING_ATOM:
      print_str = sexpr->value.atom.value.string;
      break;
    case SYMBOL_ATOM:
      char * c;
      c = (char *) malloc(sizeof(char) * (strlen(sexpr->value.atom.value.symbol)));
      strcpy(c, sexpr->value.atom.value.symbol);
      print_str = c;
      break;
    case NIL_ATOM:
      print_str = "()";
      break;
    }
  } else if (sexpr->type == LIST_SEXPR) { // if sexpr is a cons
    print_str = "( ";
    while (sexpr->value.list.consc != NULL) {
      print_str += sexprToString(sexpr->value.list.consc->car) + " ";
      sexpr->value.list.consc = sexpr->value.list.consc->cdr;
    }

    // print_str += sexprToString(sexpr->value.list.consc->cdr->car);
    print_str += " )";
  }
  else if (sexpr->type == NIL_SEXPR) { // if sexpr is a cons
    print_str = "()";
  }
  else if (sexpr->type == TRUTH_SEXPR) { // if sexpr is a cons
    print_str = "t";
  }

  return print_str;
}

bool isNil(Sexpr *sexpr) { return sexpr->type == NIL_SEXPR; }

bool isSymbol(Sexpr *sexpr) {
  return sexpr->type == ATOM_SEXPR && sexpr->value.atom.type == SYMBOL_ATOM;
}

bool isNumber(Sexpr *sexpr) {
  return sexpr->type == ATOM_SEXPR && sexpr->value.atom.type == NUMBER_ATOM;
}
bool isString(Sexpr *sexpr) {
  return sexpr->type == ATOM_SEXPR && sexpr->value.atom.type == STRING_ATOM;
}
bool isList(Sexpr *sexpr) { return sexpr->type == LIST_SEXPR; }
bool isAtom(Sexpr *sexpr) { return sexpr->type == ATOM_SEXPR; }

Sexpr *createAtom(float value){
  Sexpr *atom = new Sexpr;
  atom->type = ATOM_SEXPR;
  atom->value.atom.type = NUMBER_ATOM;
  atom->value.atom.value.number = value;
  return atom;
}
Sexpr *createAtom(AtomType type, const char * value){
  Sexpr *atom = new Sexpr;
  atom->type = ATOM_SEXPR;
  atom->value.atom.type = type;
  if(atom->value.atom.type == STRING_ATOM){
    atom->value.atom.value.string = value;
  }
  else if(atom->value.atom.type == SYMBOL_ATOM){
    atom->value.atom.value.symbol = value;
  }
  return atom;
}

Sexpr *createTruth(){
  Sexpr *sexpr = new Sexpr;
  sexpr->type = TRUTH_SEXPR;
  return sexpr;
}

Sexpr *createNil(){
  Sexpr *sexpr = new Sexpr;
  sexpr->type = NIL_SEXPR;
  return sexpr;
}

Sexpr *cons(Sexpr *car, Consc *cdr){
  Sexpr *cons = new Sexpr;
  cons->type = LIST_SEXPR;
  cons->value.list.consc = new Consc;
  cons->value.list.consc->car = car;
  //Consc *newCdr = new Consc;
  //newCdr = cdr;
  cons->value.list.consc->cdr = cdr;//newCdr;
  return cons;
}

Sexpr *add(Sexpr *a, Sexpr *b){
  return createAtom(a->value.atom.value.number + b->value.atom.value.number);
}
Sexpr *sub(Sexpr *a, Sexpr *b){
  return createAtom(a->value.atom.value.number - b->value.atom.value.number);
}
Sexpr *mul(Sexpr *a, Sexpr *b){
  return createAtom(a->value.atom.value.number * b->value.atom.value.number);
}
Sexpr *div(Sexpr *a, Sexpr *b){
  return createAtom(a->value.atom.value.number / b->value.atom.value.number);
}
Sexpr *mod(Sexpr *a, Sexpr *b){
  float val = fmod(a->value.atom.value.number, b->value.atom.value.number);
  return createAtom(val);
}

bool lt(Sexpr *a, Sexpr *b){
  return a->value.atom.value.number < b->value.atom.value.number;
}

bool gt(Sexpr *a, Sexpr *b){
  return a->value.atom.value.number > b->value.atom.value.number;
}
bool lte(Sexpr *a, Sexpr *b){
  return a->value.atom.value.number <= b->value.atom.value.number;
}
bool gte(Sexpr *a, Sexpr *b){
  return a->value.atom.value.number >= b->value.atom.value.number;
}
bool eq(Sexpr *a, Sexpr *b){
  if(a->value.atom.type == NUMBER_ATOM && b->value.atom.type == NUMBER_ATOM)
    return a->value.atom.value.number == b->value.atom.value.number;
  if(a->value.atom.type == STRING_ATOM && b->value.atom.type == STRING_ATOM)
    return strcmp(a->value.atom.value.string, b->value.atom.value.string) == 0;
  return false;
}

Sexpr *createList(){
  Sexpr *list = new Sexpr;
  list->type = LIST_SEXPR;
  list->value.list.consc = new Consc;
  return list;
}