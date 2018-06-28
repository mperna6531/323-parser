// Contains Token Class:
// Holds information for the literal, object type, and string lexeme.
#include <iostream>
#include <iomanip>
#include "token.hh"

using namespace TOKENS;

Token::Token(TYPE tt, std::string lexeme, int line_num) : tt_(tt), lexeme_(lexeme), line_num_(line_num) {}

const std::string Token::getTokenType() const {
  switch (tt_) {
    case INTEGER:
      return "Integer";
    case IDENTIFIER:
      return "Identifier";
    case KEYWORD:
      return "Keyword";
    case OPERATOR:
      return "Operator";
    case REAL:
      return "Real";
    case SEPARATOR:
      return "Separator";
    case UNKNOWN:
      return "Unknown";
    default:
      return "";
  }
}

const unsigned Token::get_line_num() const { 
  return line_num_; 
}

const std::string Token::getLexeme() const{
  return lexeme_;
}
