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
    
    // Write to File and Display Tokens:
    std::cout << std::left << std::setw(20) << "Token" << std::left << std::setw(20) << "Lexeme" << std::endl << std::endl;
    outputFile << std::left << std::setw(20)<< "Token" << std::left << std::setw(20) << "Lexeme" << std::endl << std::endl;

    
    for (auto el : scan.getTokens()) {
      std::cout << std::left << std::setw(20) << el.getTokenType() <<
        std::left << std::setw(20) << el.getLexeme() << std::endl;

      outputFile << std::left << std::setw(20) << el.getTokenType() <<
        std::left << std::setw(20) << el.getLexeme() << std::endl;
    }
  
    // Begin syntax analysis
    std::cout << "\n\nBegin Syntax Analysis:\n";

    std::vector<Token> t(scan.getTokens());
    Parser p(t);
    
    p.parse();

    inputFile.close();
    outputFile.close();
  } else {
    std::cout << "No Input File Found\n";
    exit(1);
  }
  return 0;
}
