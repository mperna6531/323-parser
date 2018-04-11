#ifndef SCANNER_H
#define SCANNER_H
#include <vector>
#include "token.hh"
#include "FSM.hh"

class Scanner {
private:
  std::vector<Token> tokens_;
  FSM machine_;
public:
  Scanner();
  void lexer(std::string &expression, int line_num);
  std::vector<Token> getTokens();
};

#endif
