#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <vector>
#include "token.h"

class Scanner{
  private:
    char *source;
    int line;
    int start;
    int current;
    std::vector<Token>* tokens;

    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, LiteralVal literal);
    char peek();
    char peekNext();
    void string();
    void number();
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c); 
    void identifier();
  public:
    Scanner(char *source);
    void scanTokens();
    char *substring(const char *source, int start, int current);
    float *parseFloat(const char *source, int start, int current);
    std::vector<Token>* getTokens();
};

//public Scanner Scanner(char * source);

#endif