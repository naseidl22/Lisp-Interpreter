#include "env.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Env::Env(){
  this->parent = nullptr;
  this->names = createList();
  this->values = createList();
}

Env::Env(Env* parent){
  this->parent = parent;
  this->names = createList();
  this->values = createList();
}

void Env::set(const char * name, Sexpr *value){
  Sexpr *currentName = names;
  Sexpr *currentValue = values;
  if(currentName->value.list.consc->car != nullptr){
    /*
    while(currentName->value.list.consc->cdr != nullptr){
      currentName = currentName->value.list.consc->cdr->car;
      currentValue = currentName->value.list.consc->cdr->car;
    }
    currentName->value.list.consc->cdr = new Consc();
    currentValue->value.list.consc->cdr = new Consc();
    currentName = currentName->value.list.consc->cdr->car;
    currentValue = currentValue->value.list.consc->cdr->car;
    */
    names = cons(createAtom(SYMBOL_ATOM, name), names->value.list.consc);
    if(isString(value)){
      //values = cons(values, createAtom(SYMBOL_ATOM, name));
      values = cons(createAtom(STRING_ATOM, value->value.atom.value.string), values->value.list.consc);
    }
    else if(isNumber(value)){
      //values = cons(values, createAtom(value->value.atom.value.number));
      values = cons(createAtom(value->value.atom.value.number), values->value.list.consc);
    }
    else if(isSymbol(value)){
        //values = cons(values, createAtom(value->value.atom.value.number));
      values = cons(createAtom(SYMBOL_ATOM, name), values->value.list.consc);//cons(createAtom(value->value.atom.value.number), values->value.list.consc);
    }
    else{
      Sexpr * list = createList();
      list->value.list.consc = value->value.list.consc;
      values = cons(list, values->value.list.consc);
    }
    
  }
  else{
    currentName->value.list.consc->car = createAtom(SYMBOL_ATOM, name);
    if(isString(value)){
      currentValue->value.list.consc->car = createAtom(STRING_ATOM, value->value.atom.value.string);
    }
    else if(isNumber(value)){
      currentValue->value.list.consc->car = createAtom(value->value.atom.value.number);
    }
    else{
      currentValue->value.list.consc->car = value;
      //currentValue->value.list.consc->car = createAtom(value->value.atom.value.number);
    }
  }
  
}

Sexpr * Env::get(const char * name){
  Consc *currentName = names->value.list.consc;
  Consc *currentValue = values->value.list.consc;
  while(currentName != nullptr && currentName->car != nullptr){
    if(strcmp(name, currentName->car->value.atom.value.symbol) == 0){
      return currentValue->car;
    }
    currentName = currentName->cdr;
    currentValue = currentValue->cdr;
  }
  if(this->parent != nullptr){
    return this->parent->get(name);
  }
  std::cout << "ERROR: " << name << " is not defined" << std::endl;
  return createNil();
}
