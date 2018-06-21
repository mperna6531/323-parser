#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>

#include "scanner.hh"
#include "Parser.hh"

int main(int argc, char **argv) {
  std::string file_in_name, file_out_name;

  std::cout << "Input Name of File: ";
  std::getline(std::cin, file_in_name);

  std::cout << "Input Name of Output File: ";
  std::getline(std::cin, file_out_name);

  std::ifstream is(file_in_name);
  std::ofstream os(file_out_name);

  if (is.is_open() && os.is_open()) {
    Scanner scan;
    std::string expression;
    unsigned line_num = 0;

    while (getline(is, expression)) 
      scan.lexer(expression, ++line_num);
    
   
    scan.print_tokens(os);
  
    // Begin syntax analysis
    std::cout << "\n\nBegin Syntax Analysis:\n";

    std::vector<Token> t(scan.getTokens());
    Parser p(t, os);
    
    p.parse(os);

    is.close();
    os.close();
  } else {
    std::cout << "No Input File Found\n";
    exit(1);
  }
  return 0;
}
