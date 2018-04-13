// Contains Scanner Class
// This class parses through the text file and creates token objects.
#include "scanner.hh"
#include "token.hh"
#include <iostream>

Scanner::Scanner() {}

void Scanner::lexer(std::string &expression, int line_num) {
  std::string lexeme = "";
  TOKENS::TYPE tknType;

  // add whitespace to end of string to delineate tokens
  expression.push_back(' '); 
  
  for (size_t i = 0; i < expression.length(); ++i) {
    // pass input to machine to transition between states
    machine_.transition(expression[i]);

    // Determine if machine is in accepting state.  If machine has clicked over 
    // to starting state from accepting state and needs to backup and current 
    // space != whitespace, decrement i to re-process last char from starting state
    if (machine_.is_accepting()) {
      if (machine_.backup()) {
        if (!isspace(expression[i])) {
          --i;  
        }
      }
       // create new Token obj and add to tokens_ vector
      lexeme = machine_.getLexeme();
      tknType = machine_.getTokenType();
      Token newToken(tknType, lexeme, line_num);
      tokens_.push_back(newToken);
      // reset everything:
      machine_.reset();
    }
  }
}

std::vector<Token> Scanner::getTokens()  {
  return tokens_;
}


