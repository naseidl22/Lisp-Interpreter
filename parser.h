#ifndef PARSER_H  
#define PARSER_H

#include <vector>
#include "token.h"
#include "sexpr.h"

class Parser{
  private:
    std::vector<Token>* tokens;
    unsigned current;
    Sexpr* atom();
    Sexpr* list();
    bool isAtEndParser();
    void consumeWhitespace();
    Token getCurrentToken();
  public:
    Parser(std::vector<Token>* tokens);
    Sexpr* parse();
};

#endif