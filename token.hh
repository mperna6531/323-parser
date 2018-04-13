#ifndef TOKEN_HH_
#define TOKEN_HH_

#include<string>

namespace TOKENS {
enum TYPE { INTEGER = 0, REAL, IDENTIFIER, KEYWORD, SEPARATOR, OPERATOR, UNKNOWN };
}

class Token {
private:
  TOKENS::TYPE tt_;
  std::string lexeme_;
  unsigned line_num_;
public:
  Token(TOKENS::TYPE tt, std::string lexeme, int line_num);
  const std::string getTokenType() const;
  const std::string getLexeme() const;
  const unsigned get_line_num() const;
};

#endif
