#include "scanner.h"
#include <cstring>
#include <iostream>

Scanner::Scanner(char* source){
  this->source = source;
  this->line = 1;
  this->current = 0;
  this->start = 0;
  this->tokens = new std::vector<Token>();
}

void Scanner::scanTokens(){
  while (!isAtEnd()){
    start = current;
    scanToken();
  }
  
  Token eofToken;
  eofToken.type = END_OF_FILE;
  eofToken.line = line;
  tokens->push_back(eofToken);
}
 
bool Scanner::isAtEnd(){
  return this->current >= std::strlen(this->source);
}

void Scanner::scanToken(){
  char c = advance();

  switch(c){
    case '(': 
      addToken(LEFT_PAREN); 
      break;
    case ')': 
      addToken(RIGHT_PAREN); 
      break;
    case ' ' :
      addToken(SPACE);
      break;
    case '.' :
      addToken(DOT);
      break;
    case '"' :
      string();
      break;
    case '+' :
    case '*' :
    case '/' :
    case '=' :
    case '<' :
    case '>' :
    case '?' :
      identifier();//addToken(PLUS);
      break;
    case '-' :
      advance();
      number();
      break;
   // case '-' :
   // addToken(MINUS);
   // break;
   // case '*' :
   // addToken(STAR);
   // break;
   // case '/' :
   // addToken(SLASH);
   // break;
   // case '=' :
   // addToken(EQUAL);
   // break;
   // case '<' :
   // addToken(LESS);
   // break;
   // case '>' :
   // addToken(GREATER);
   // break;
    case '\r'://ignore
    case '\t'://ignore
      break;
    case '\n':
      this->line++;
      break;
    default:
      if (isDigit(c)){
        number();
      }else if(isAlpha(c)){
       identifier(); 
      }
      else{
        std::cout << "Unexpected character: " << c << std::endl;
      }
      break;
  }
}

char Scanner::advance(){
  return this->source[this->current++]; // get current char and advance parser
}

void Scanner::addToken(TokenType type){
  LiteralVal literal; // basically and empty literal. It's okay because we should never actually inspect the value inside of it
  addToken(type, literal);  
}

void Scanner::addToken(TokenType type, LiteralVal literal){
  char* text = substring(this->source, this->start, this->current);
  //construct token
  Token newToken;
  newToken.type = type;
  newToken.line = this->line;
  newToken.lexeme = text;
  newToken.literal = literal;
  //add token to vector
  tokens->push_back(newToken); 
}

char* Scanner::substring(const char *source, int start, int current) { //reused from LOX
  int length = current - start;
  char *text = (char *)malloc((length + 1) * sizeof(char)); // Allocate memory for return value (length + 1 for null terminator)
  strncpy(text, source + start, length);
  text[length] = '\0'; // Add null terminator
  return text;
}

char Scanner::peek(){
  if(isAtEnd()){
    return '\0';
  }
  return this->source[current];
}

void Scanner::string(){
  while(peek() != '"' && !isAtEnd()){
    if(peek() == '\n'){
      this->line++;
    }
    advance();
  }

  if(isAtEnd()){
    std::cout << "Unterminated string" << std::endl;
    return;
  }

  advance();

  char* value = substring(this->source, this->start + 1, this->current - 1);
  LiteralVal val;
  val.string = value;
  addToken(STRING, val);
}

bool Scanner::isDigit(char c){
  return c >= '0' && c <= '9';
}

void Scanner::number(){
  while(isDigit(peek())){
    advance();
  }

  if(peek() == '.' && isDigit(peekNext())){
    advance();
    
    while(isDigit(peek())){
      advance();
    }
  }

  LiteralVal val;
  val.number = *parseFloat(this->source, this->start, this->current);
  
  addToken(NUMBER, val);
}

char Scanner::peekNext(){
  if(current + 1 >= std::strlen(this->source)){
    return '\0';
  }
  return this->source[current + 1];
}

float* Scanner::parseFloat(const char *source, int start, int current) { // reused from LOX, can probably simplify a little
  char *text = substring(source, start, current); // Get sring with the value
  float value = strtod(text, NULL); // Get double value from string
  float *v = (float *)malloc(sizeof(float));
  *v = value; //make new float from double
  free(text);
  return v;
}

bool Scanner::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
          c == '_';
}



bool Scanner::isAlphaNumeric(char c) {
  return isAlpha(c) || isDigit(c) || c == '?';
}

void Scanner::identifier(){ // This should really be called sybmbol()
  while(isAlphaNumeric(peek())){
    advance();
  }

  char *text = substring(source, start, current);
  /**** Treat native functions like regular function calls ******/
  
  //if (strcmp(text, "EVAL") == 0)
  //  addToken(EVAL);
  //else if (strcmp(text, "QUOTE") == 0)
  //  addToken(QUOTE);
  //else if (strcmp(text, "DEFINE") == 0)
  //  addToken(DEFINE);
  //else if (strcmp(text, "SET") == 0)
  //  addToken(SET);
  //else if (strcmp(text, "CONS") == 0)
  //  addToken(CONS);
  //else if (strcmp(text, "COND") == 0)
  //  addToken(COND);
  //else if (strcmp(text, "CAR") == 0)
  //  addToken(CAR);
  //else if (strcmp(text, "CDR") == 0)
  //  addToken(CDR);
  //else if (strcmp(text, "AND?") == 0)
  //  addToken(AND);
  //else if (strcmp(text, "OR?") == 0)
  //  addToken(OR);
  //else if (strcmp(text, "NUMBER?") == 0)
  //  addToken(IS_NUMBER);
  //else if (strcmp(text, "SYMBOL?") == 0)
  //  addToken(IS_SYMBOL);
  //else if (strcmp(text, "LIST?") == 0)
  //  addToken(IS_LIST);
  //else if (strcmp(text, "NIL?") == 0)
  //  addToken(IS_NIL);
  //else if (strcmp(text, "EQ?") == 0)
  //  addToken(IS_EQ);
  //else{
  LiteralVal v;
  v.symbol = text;
  addToken(SYMBOL, v);
  //free(text);
  //return; // have to save the text if adding a symbol 
  //}
    
  
}

std::vector<Token>* Scanner::getTokens(){
  return tokens;
}