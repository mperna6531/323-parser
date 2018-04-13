// Contains Token Class:
// Holds information for the literal, object type, and string lexeme.
#include <iostream>
#include <iomanip>
#include "token.hh"

Token::Token(TOKENS::TYPE tt, std::string lexeme, int line_num) : tt_(tt), lexeme_(lexeme), line_num_(line_num) {}

const std::string Token::getTokenType() const {

  switch (tt_) {
    case TOKENS::INTEGER:
      return "Integer";
    case TOKENS::IDENTIFIER:
      return "Identifier";
    case TOKENS::KEYWORD:
      return "Keyword";
    case TOKENS::OPERATOR:
      return "Operator";
    case TOKENS::REAL:
      return "Real";
    case TOKENS::SEPARATOR:
      return "Separator";
    case TOKENS::UNKNOWN:
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
