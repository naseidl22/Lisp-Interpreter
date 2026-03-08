#include "parser.h"
#include <stdio.h>
#include <iostream>

Parser::Parser(std::vector<Token>* tokens){
  this->tokens = tokens;
  this->current = 0;
}

Sexpr* Parser::parse(){
  consumeWhitespace();

  if(isAtEndParser()){
    return createNil();
  }
  
  if(tokens->at(current).type == LEFT_PAREN){
    return list();
  }
  
  Sexpr *val  = atom();
  current++;
  return val;//return atom();
}

bool Parser::isAtEndParser(){
  if(tokens->at(current).type == END_OF_FILE){
    return true;
  }
  return false;
}

Sexpr* Parser::atom(){
  Sexpr *sexpr = new Sexpr();
  sexpr->type = ATOM_SEXPR;
  Token t = tokens->at(current);
  switch(t.type){
    case NUMBER:
      sexpr->value.atom.type = NUMBER_ATOM;
      sexpr->value.atom.value.number = tokens->at(current).literal.number;
      break;
    case STRING:
      sexpr->value.atom.type = STRING_ATOM;
      sexpr->value.atom.value.string = tokens->at(current).literal.string;
      break;
    case SYMBOL:
      sexpr->value.atom.type = SYMBOL_ATOM;
      sexpr->value.atom.value.symbol = tokens->at(current).literal.symbol;
      break;
    default:
      ;
      //write an error message probably
      break;
  }
  return sexpr;
}

Sexpr* Parser::list(){
  
  current++;
  consumeWhitespace();
  Sexpr *sexpr = new Sexpr();
  sexpr->type = LIST_SEXPR;
  

  sexpr->value.list.consc = new Consc();
  Consc *currentConsc = sexpr->value.list.consc;
  unsigned i = 0; // detect nil lists
  while(getCurrentToken().type != RIGHT_PAREN){
    
    if(getCurrentToken().type == LEFT_PAREN){
      i++;
      currentConsc->car = list();
      currentConsc->cdr = new Consc();
      currentConsc = currentConsc->cdr;
      consumeWhitespace();
    }
    else{
      i++;
      currentConsc->car = atom();
      currentConsc->cdr = new Consc();
      currentConsc = currentConsc->cdr;
      current++;
      if(getCurrentToken().type == SPACE)
          consumeWhitespace();
    }
    
  }
  if(i == 0)
      sexpr = createNil(); // if list is empty, make it nil
  currentConsc->cdr = nullptr;
  current++;
  return sexpr;
}

void Parser::consumeWhitespace(){
  while(tokens->at(current).type == SPACE){
    current++;
  }
}

Token Parser::getCurrentToken(){
  return tokens->at(current);
}
