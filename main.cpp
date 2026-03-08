#include <iostream>
#include <cstring>
#include "sexpr.h"
#include "scanner.h"
#include "parser.h"
#include "interpreter.h"
#include "env.h"
#include <vector>
#include <fstream>

void run(char *line, Env *environment) {

  Scanner scanner(line);
  scanner.scanTokens();
  std::vector<Token>* tokens = scanner.getTokens();

  //Sexpr *mySexpr = createAtom(5);
  
  //env->set("print", mySexpr);

  //for(int i = 0; i < tokens->size(); i++){
  //  //  Token t = tokens->at(i);
  //  //  std::cout << t.type << std::endl;
  //
  //  //std::cout << t.lexeme;
  //}

  Parser parser(tokens);
  Sexpr *sexpr = parser.parse();
  while(!isNil(sexpr)){

    eval(sexpr, environment);
    sexpr = parser.parse();
  }
  

  //std::string s = sexprToString(eval(sexpr, environment));
  //std::cout << s << std::endl;
  
  printf("\n");
}

void runPrompt() {
  char line[1024];

  Env *env = new Env();
  while (1) {
    printf("<<\n");
    if (fgets(line, sizeof(line), stdin) == NULL) {
      break;
    }
    run(line, env);
  }
}

char* readYispFile(const std::string& filePath);

void runFile(const char *path) {
  Env *env = new Env();
  char * content = readYispFile(path);
  run(content, env);
}

int main(int argc, char *argv[]) {

  //const char *file = "program.txt";
  //runFile(file);
  
  if (argc > 2) {
    printf("Usage: lox [script]");
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPrompt();
  }
}

char* readYispFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate); //configure file. need std::ios::ate to close file
    if (!file) {
        std::cerr << "Error: Unable to open file " << filePath << "\n";
        return nullptr;
    }

    std::streamsize fileSize = file.tellg(); //get file size for buffer
    file.seekg(0, std::ios::beg); // go to start of the file

    char* buffer = new char[fileSize + 1]; // create buffer

    
    file.read(buffer, fileSize); // read input into the buffer
    buffer[fileSize] = '\0'; // add null terminator to string
    return buffer;
        
}