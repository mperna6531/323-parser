#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>

#include "scanner.hh"
#include "Parser.hh"

int main(int argc, char **argv) {
  std::string fileInputName, fileOutputName;

  std::cout << "Input Name of File: ";
  std::getline(std::cin, fileInputName);

  std::cout << "Input Name of Output File: ";
  std::getline(std::cin, fileOutputName);

  std::ifstream inputFile(fileInputName);
  std::ofstream outputFile(fileOutputName);

  if (inputFile.is_open() && outputFile.is_open()) {
    Scanner scan;
    std::string expression;
    unsigned line_num = 0;

    while (getline(inputFile, expression)) 
      scan.lexer(expression, ++line_num);
    
   
    scan.print_tokens(outputFile);
  
    // Begin syntax analysis
    std::cout << "\n\nBegin Syntax Analysis:\n";

    std::vector<Token> t(scan.getTokens());
    Parser p(t);
    
    p.parse(outputFile);

    inputFile.close();
    outputFile.close();
  } else {
    std::cout << "No Input File Found\n";
    exit(1);
  }
  return 0;
}
