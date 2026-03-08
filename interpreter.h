#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "sexpr.h"
#include "env.h"

Sexpr *eval(Sexpr *arg, Env * env);
Sexpr *symbol(Sexpr *arg, Env * env);
Sexpr *list(Sexpr *arg, Env * env);
Sexpr *evalAdd(Sexpr *arg, Env * env);
Sexpr *evalSub(Sexpr *arg, Env * env);
Sexpr *evalMul(Sexpr *arg, Env * env);
Sexpr *evalDiv(Sexpr *arg, Env * env);
Sexpr *evalMod(Sexpr *arg, Env * env);
Sexpr *evalLt(Sexpr *arg, Env * env);
Sexpr *evalGt(Sexpr *arg, Env * env);
Sexpr *evalLte(Sexpr *arg, Env * env);
Sexpr *evalGte(Sexpr *arg, Env * env);
Sexpr *evalEq(Sexpr *arg, Env * env);
Sexpr *evalNot(Sexpr *arg, Env * env);
Sexpr *evalTruth(Sexpr *arg, Env * env);
Sexpr *evalQuote(Sexpr *arg, Env * env);
Sexpr *evalPrint(Sexpr *arg, Env * env);
Sexpr *evalSet(Sexpr *arg, Env * env);
Sexpr *evalAnd(Sexpr *arg, Env * env);
Sexpr *evalOr(Sexpr *arg, Env * env);
Sexpr *evalIf(Sexpr *arg, Env * env);
Sexpr *evalCond(Sexpr *arg, Env * env);
Sexpr *evalDefun(Sexpr *arg, Env * env);
Sexpr *evalFunction(Sexpr *arg, Env * env);
Sexpr *evalIsNumber(Sexpr *arg, Env * env);
Sexpr *evalIsSymbol(Sexpr *arg, Env * env);
Sexpr *evalIsList(Sexpr *arg, Env * env);
Sexpr *evalIsNil(Sexpr *arg, Env * env);
Sexpr *evalCar(Sexpr *arg, Env * env);
Sexpr *evalCdr(Sexpr *arg, Env * env);
Sexpr *evalCons(Sexpr *arg, Env * env);
Sexpr *evalEval(Sexpr *arg, Env * env);

#endif
