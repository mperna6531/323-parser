#include <iostream>
#include <fstream>
#include <iomanip>

#include "scanner.hh"
#include "token.hh"

Scanner::Scanner() {}

void Scanner::lexer(std::string &expression, int line_num) {
  // add whitespace to end of string to delineate tokens
  expression.push_back(' '); 
  
  for (size_t i = 0; i < expression.length(); ++i) {
    // pass input to machine to transition between states
    machine_.transition(expression[i]);

    // Determine if machine is in accepting state.  If machine has clicked over 
    // to starting state from accepting state and needs to backup and current 
    // char != whitespace, decrement i to re-process last char from starting state.
    if (machine_.is_accepting()) {
      if (machine_.backup()) {
        if (!isspace(expression[i])) {
          --i;  
        }
      }
       // create new Token obj and add to tokens_ vector
      std::string lexeme = machine_.getLexeme();
      TOKENS::TYPE tknType = machine_.getTokenType();
      Token newToken(tknType, lexeme, line_num);
      tokens_.push_back(newToken);
      
      machine_.reset();
    }
  }
}

std::vector<Token> Scanner::getTokens() const {
  return tokens_;
}

void Scanner::print_tokens(std::ofstream &out) const {
  // Write to File and Display Tokens:
  std::cout << std::left << std::setw(20) << "Token" << std::left << std::setw(20) << "Lexeme" << std::endl << std::endl;
  out << std::left << std::setw(20)<< "Token" << std::left << std::setw(20) << "Lexeme" << std::endl << std::endl;

  for (auto el : tokens_) {
   std::cout << std::left << std::setw(20) << el.getTokenType() <<
        std::left << std::setw(20) << el.getLexeme() << std::endl;

    out << std::left << std::setw(20) << el.getTokenType() <<
      std::left << std::setw(20) << el.getLexeme() << std::endl;  
  }
}

