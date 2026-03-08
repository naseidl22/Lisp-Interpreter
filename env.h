#ifndef ENV_H
#define ENV_H

#include "sexpr.h"

class Env{
  private:
    Env* parent;
    Sexpr* names;
    Sexpr* values;
  public:
    Env();
    Env(Env* parent);
    Sexpr * get(const char * name);
    void set(const char * name, Sexpr *value);
};


#endif