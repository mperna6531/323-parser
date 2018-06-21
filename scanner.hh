#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include <fstream>

#include "token.hh"
#include "FSM.hh"

class Scanner {
private:
  std::vector<Token> tokens_;
  FSM machine_;
public:
  Scanner();
  void lexer(std::string &expression, int line_num);
  std::vector<Token> getTokens() const;
  void print_tokens(std::ofstream &out) const;
};

#endif
