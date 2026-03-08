#include "interpreter.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "env.h"


Sexpr *eval(Sexpr *arg, Env * env){
  if(!isList(arg)){
    if(isSymbol(arg)){
      return env->get(arg->value.atom.value.symbol);
    }
    return arg;
  }
  
  return list(arg, env);
}

Sexpr *symbol(Sexpr *arg, Env * env){
  const char *name = arg->value.list.consc->car->value.atom.value.symbol;
  
  if(strcmp(name, "add") == 0){
    //printf("ADD FUNCTION CALL\n");
    return evalAdd(arg, env);
  } else if (strcmp(name, "mul") == 0){
    return evalMul(arg, env);
  } else if (strcmp(name, "sub") == 0){
    return evalSub(arg, env);
  }
  else if (strcmp(name, "div") == 0){
    return evalDiv(arg, env);
  }
  else if (strcmp(name, "mod") == 0){
    return evalMod(arg, env);
  }
  else if (strcmp(name, "lt") == 0){
    return evalLt(arg, env);
  }
  else if (strcmp(name, "lte") == 0){
    return evalLte(arg, env);
  }
  else if (strcmp(name, "gt") == 0){
    return evalGt(arg, env);
  }
  else if (strcmp(name, "gte") == 0){
    return evalGte(arg, env);
  }
  else if (strcmp(name, "eq") == 0){
    return evalEq(arg, env);
  }
  else if (strcmp(name, "not") == 0){
    return evalNot(arg, env);
  }
  else if (strcmp(name, "isTruth") == 0){
    return evalTruth(arg, env);
  }
  else if (strcmp(name, "quote") == 0){
    return evalQuote(arg, env);
  }
  else if (strcmp(name, "print") == 0){
    return evalPrint(arg, env);
  }
  else if (strcmp(name, "set") == 0){
    return evalSet(arg, env);
  }
  else if (strcmp(name, "and") == 0){
    return evalAnd(arg, env);
  }
  else if (strcmp(name, "or") == 0){
    return evalOr(arg, env);
  }
  else if (strcmp(name, "if") == 0){
    return evalIf(arg, env);
  }
  else if (strcmp(name, "cond") == 0){
    return evalCond(arg, env);
  }
  else if (strcmp(name, "defun") == 0){
    return evalDefun(arg, env);
  }
  else if (strcmp(name, "NUMBER?") == 0){
    return evalIsNumber(arg, env);
  }
  else if (strcmp(name, "SYMBOL?") == 0){
    return evalIsSymbol(arg, env);
  }
  else if (strcmp(name, "LIST?") == 0){
    return evalIsList(arg, env);
  }
  else if (strcmp(name, "NIL?") == 0){
    return evalIsNil(arg, env);
  }
  else if (strcmp(name, "car") == 0){
    return evalCar(arg, env);
  }
  else if (strcmp(name, "cdr") == 0){
    return evalCdr(arg, env);
  }
  else if (strcmp(name, "cons") == 0){
    return evalCons(arg, env);
  }
  else if (strcmp(name, "eval") == 0){
    return evalEval(arg, env);
  }
  
  Sexpr *call = env->get(name);
  if(isList(call)){ //make sure this is a saved function
    //&& isList(call->value.list.consc->car) 
    //&& isSymbol(call->value.list.consc->car->value.list.consc->car)){

    //printf("CALLING FUNCTION\n");
    Env *functionEnv = new Env(env);
    Consc *current = arg->value.list.consc->cdr;
    Consc *currentArg = call->value.list.consc->car->value.list.consc;
    while(current->car != nullptr){
      functionEnv->set(currentArg->car->value.atom.value.symbol, eval(current->car, env));
      current = current->cdr;
      currentArg = currentArg->cdr;
    }
    //std::cout << sexprToString(call->value.list.consc->cdr->car) << std::endl;
    return eval(call->value.list.consc->cdr->car, functionEnv);
  }

  return env->get(name);
  return arg;
}

Sexpr *list(Sexpr *arg, Env * env){
  //if(isSymbol(arg->value.list.consc->car)){
  //  return symbol(arg, env);
  //}
  
  return symbol(arg, env); // assume first item in list is a symbol unless quoted
  
  return arg;
}

Sexpr *evalAdd(Sexpr *arg, Env * env){
  Sexpr *result = nullptr;
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, add requires at least 2 arguments" << std::endl;
    return createNil();
  }

  result = add(eval(current->car, env), eval(current->cdr->car, env));
  current = current->cdr->cdr;

  while(current->car != nullptr){ 
    Sexpr *currentArg = current->car;
    currentArg = eval(currentArg, env);
    result = add(result, currentArg);
    current = current->cdr;
  }
  return result;
}

Sexpr *evalSub(Sexpr *arg, Env * env){
  Sexpr *result = nullptr;
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, mul requires at least 2 arguments" << std::endl;
    return createNil();
  }

  result = sub(eval(current->car, env), eval(current->cdr->car, env));
  current = current->cdr->cdr;

  while(current->car != nullptr){ 
    Sexpr *currentArg = current->car;
    currentArg = eval(currentArg, env);
    result = sub(result, currentArg);
    current = current->cdr;
  }
  return result;
}

Sexpr *evalMul(Sexpr *arg, Env * env){
  Sexpr *result = nullptr;
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, mul requires at least 2 arguments" << std::endl;
    return createNil();
  }

  result = mul(eval(current->car, env), eval(current->cdr->car, env));
  current = current->cdr->cdr;
  
  while(current->car != nullptr){ 
    Sexpr *currentArg = current->car;
    currentArg = eval(currentArg, env);
    result = mul(result, currentArg);
    current = current->cdr;
  }
  return result;
}

Sexpr *evalDiv(Sexpr *arg, Env * env){
  Sexpr *result = nullptr;
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, mul requires at least 2 arguments" << std::endl;
    return createNil();
  }

  result = div(eval(current->car, env), eval(current->cdr->car, env));
  current = current->cdr->cdr;

  while(current->car != nullptr){ 
    Sexpr *currentArg = current->car;
    currentArg = eval(currentArg, env);
    result = div(result, currentArg);
    current = current->cdr;
  }
  return result;
}

Sexpr *evalMod(Sexpr *arg, Env * env){
  Sexpr *result = nullptr;
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, mul requires at least 2 arguments" << std::endl;
    return createNil();
  }

  result = mod(eval(current->car, env), eval(current->cdr->car, env));
  current = current->cdr->cdr;

  while(current->car != nullptr){ 
    Sexpr *currentArg = current->car;
    currentArg = eval(currentArg, env);
    result = mod(result, currentArg);
    current = current->cdr;
  }
  return result;
}

Sexpr *evalLt(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, lt requires 2 arguments" << std::endl;
    return createNil();
  }
  bool value = lt(eval(current->car, env), eval(current->cdr->car, env));
  if(value){
    return createTruth();
  }
  return createNil();
  //return createAtom(value);
}

Sexpr *evalGt(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, gt requires 2 arguments" << std::endl;
    return createNil();
  }
  bool value = gt(eval(current->car, env), eval(current->cdr->car, env));
  if(value){
    return createTruth();
  }
  return createNil();
  //return createAtom(value);
}

Sexpr *evalLte(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, lte requires 2 arguments" << std::endl;
    return createNil();
  }
  bool value = lte(eval(current->car, env), eval(current->cdr->car, env));
  if(value){
    return createTruth();
  }
  return createNil();
  //return createAtom(value);
}

Sexpr *evalGte(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, gte requires 2 arguments" << std::endl;
    return createNil();
  }
  bool value = gte(eval(current->car, env), eval(current->cdr->car, env));
  if(value){
    return createTruth();
  }
  return createNil();
  //return createAtom(value);
}

Sexpr *evalEq(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, eq requires 2 arguments" << std::endl;
    return createNil();
  }
  bool value = eq(eval(current->car, env), eval(current->cdr->car, env));
  if(value){
    return createTruth();
  }
  return createNil();
  //return createAtom(value);
}

Sexpr *evalNot(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, not requires 1 argument" << std::endl;
    return createNil();
  }
  Sexpr *val = eval(current->car, env);
  if(isNil(val)){
    return createTruth();
  }
  return createNil();
}

Sexpr *evalTruth(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, nil requires 1 argument" << std::endl;
    return createNil();
  }
  Sexpr *val = eval(current->car, env);
  if(!isNil(val)){
    return createTruth();
  }
  return createNil();
}

Sexpr *evalQuote(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, quote requires 1 argument" << std::endl;
    return createNil();
  }

  if(current->car->value.atom.type == SYMBOL_ATOM && strcmp(current->car->value.atom.value.symbol, "t") == 0){
    return createTruth();
  }
  
  return current->car;
}

Sexpr *evalPrint(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, print requires 1 argument" << std::endl;
    return createNil();
  }

  std::cout << sexprToString(eval(current->car, env)) << std::endl;
  
  return createTruth();
}

Sexpr *evalSet(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, set requires 2 arguments" << std::endl;
    return createNil();
  }
  const char *name = current->car->value.atom.value.symbol;
  Sexpr *value = eval(current->cdr->car, env);

  env->set(name, value);
  return createTruth();
}

Sexpr *evalAnd(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, and requires 2 arguments" << std::endl;
    return createNil();
  }

  if(isNil(eval(current->car,env))){
    return createNil();
  }
  if(isNil(eval(current->cdr->car,env))){
    return createNil();
  }
  return createTruth();
}

Sexpr *evalOr(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, or requires 2 arguments" << std::endl;
    return createNil();
  }

  if(!isNil(eval(current->car,env))){
    return createTruth();
  }
  if(!isNil(eval(current->cdr->car,env))){
    return createTruth();
  }
  return createNil();
}

Sexpr *evalIf(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, if requires at least 2 arguments" << std::endl;
    return createNil();
  }

  if(!isNil(eval(current->car,env))){
    return eval(current->cdr->car, env);
  }
  else if(current->cdr->cdr->car != nullptr){
    return eval(current->cdr->cdr->car, env);
  }
  return createNil();
}


/*
(cond   (cond1    action1)
 (cond2    action2))
 ...
*/
Sexpr *evalCond(Sexpr *arg, Env * env){

  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, cond requires at least 1 S-expression argument" << std::endl;
    return createNil();
  }

  while(current->car != nullptr){ // traverse arguments
    //std::cout << sexprToString(current->car) << std::endl;
    //std::cout << sexprToString(current->car->value.list.consc->car) << std::endl;
    //current = current->cdr->car;
    bool val = !isNil(eval(current->car->value.list.consc->car, env));
    if(val){
      return eval(current->car->value.list.consc->cdr->car, env);
    }
    current = current->cdr;
  }
  
  return createNil();
}

Sexpr *evalDefun(Sexpr *arg, Env * env){
  Sexpr *functionDef = createList(); //create list to house function

  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, defun requires arguments" << std::endl;
    return createNil();
  }
  
  const char *name = current->car->value.atom.value.symbol;
  //printf("%s\n", name);

  Sexpr *argumentList = current->cdr->car;
  //std::cout << "argumentList: " << sexprToString(argumentList) << std::endl;

  Sexpr *body = current->cdr->cdr->car;

  //std::cout << "body: " << sexprToString(body) << std::endl;

  functionDef->value.list.consc->car = argumentList;
  functionDef->value.list.consc->cdr = new Consc;//->car = body;
  functionDef->value.list.consc->cdr->car = body;

  //std::cout << "funcitondef: " << sexprToString(functionDef) << std::endl;

  env->set(name, functionDef);
  
  return createTruth();
}

Sexpr *evalFunction(Sexpr *arg, Env * env){
  return createNil();
}

Sexpr *evalIsNumber(Sexpr *arg, Env * env){
  
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, Number? requires 1 argument" << std::endl;
    return createNil();
  }
  
  if(isNumber(eval(current->car, env))){
    return createTruth();
  }
  return createNil();
}

Sexpr *evalIsSymbol(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, Symbol? requires 1 argument" << std::endl;
    return createNil();
  }

  if(isSymbol(eval(current->car, env))){
    return createTruth();
  }
  return createNil();
}
Sexpr *evalIsList(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, List? requires 1 argument" << std::endl;
    return createNil();
  }

  if(isList(eval(current->car, env))){
    return createTruth();
  }
  return createNil();
}

Sexpr *evalIsNil(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, List? requires 1 argument" << std::endl;
    return createNil();
  }

  if(isNil(eval(current->car, env))){
    return createTruth();
  }
  return createNil();
}

Sexpr *evalCar(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, car requires 1 argument" << std::endl;
    return createNil();
  }

  return eval(current->car, env)->value.list.consc->car;

  //return createNil();
}

Sexpr *evalCdr(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, cdr requires 1 argument" << std::endl;
    return createNil();
  }

  Sexpr *value = eval(current->car, env);
  if(!isList(value) || value->value.list.consc->car == nullptr){
    return createNil();
  }
  Sexpr *returnVal = createList();
  returnVal->value.list.consc = value->value.list.consc->cdr;
  return returnVal;

}

Sexpr *evalCons(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr || current->cdr->car == nullptr){
    std::cout << "ERROR, cons requires 2 arguments" << std::endl;
    return createNil();
  }

  Sexpr *result = createList();
  result->value.list.consc->car = eval(current->car, env);
  result->value.list.consc->cdr = eval(current->cdr->car, env)->value.list.consc;

  return result;

  return createNil();
}

Sexpr *evalEval(Sexpr *arg, Env * env){
  Consc *current = arg->value.list.consc->cdr;
  if(current->car == nullptr){
    std::cout << "ERROR, eval requires 1 argument" << std::endl;
    return createNil();
  }

  Env *functionEnv = new Env(env);
  Sexpr *val = eval(current->car, env);
  return eval(val, functionEnv); // okay

  return createTruth();
}