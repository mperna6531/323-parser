#ifndef TOKEN_H
#define TOKEN_H
#include<string>

namespace TOKENS {
enum TYPE { INTEGER = 0, REAL, IDENTIFIER, KEYWORD, SEPARATOR, OPERATOR, UNKNOWN };
}

class Token {
private:
  TOKENS::TYPE tt_;
  std::string lexeme_;
  int line_num_;
public:
  // TODO: Figure out how to get string into the correct object type:
  // static const auto literal;
  Token(TOKENS::TYPE tt, std::string lexeme, int line_num);
  const std::string getTokenType() const;
  const std::string getLexeme() const;
  const int get_line_num() const;
};

#endif
