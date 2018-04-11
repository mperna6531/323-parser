#include <iomanip>
#include "Parser.hh"


void Parser::print_token() {
  if ( it_ != tokens_.end())
    std::cout << '\n' << std::left << std::setw(20) << "Token: " + it_->getTokenType() << std::left << std::setw(20) << 
    "Lexeme: " + it_->getLexeme() << std::endl;
}

void Parser::next_token() {
  ++it_;
}

Parser::Parser(std::vector<Token> &tokens) : tokens_(tokens), it_(tokens_.begin()) {}

void Parser::parse() {
  // print starting token
  print_token();
  while (it_ != tokens_.end()) {
    if (CND()) {
      std::cout << "End of successfull parse." << std::endl;
    } else {
      std::cout << "Parse error." << std::endl;
    }
  }
}

// TODO: FINISH
bool Parser::keyword() {
  if (it_->getTokenType().compare("Keyword") == 0) {
    if (it_->getLexeme().compare("function") == 0) {
      return F();
    }
  }
  return false;
}

//TODO::FINISH
// Rule 4 <Function> ::= function  <Identifier>  [ <Opt Parameter List> ]  <Opt Declaration List>  <Body>
bool Parser::F() {
  bool result = false;
  if (it_->getLexeme().compare("function") == 0) {
    
  }
  
  return result;
}

// Rule 13:
bool Parser::IDS() {
  if (TEST_PRINT) {
    std::cout << "<IDs> := id <IDs Prime>" << std::endl;
  }
  
  bool result = false;
  if (it_->getTokenType().compare("Identifier") == 0) {
    next_token();
    result = IDS_PRIME();
  }
  return result;
}

// Rule 13-2:
bool Parser::IDS_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<IDs Prime> := , <IDs>  | <Empty>" << std::endl;
  }
  
  bool result = false;

  if (it_->getLexeme().compare(",") == 0) {
    next_token();
    result = IDS(); 
  } else { // empty
    result = EMP();
  }
  return result;
}

// Rule 15:
bool Parser::S() {

}

// Rule 16:
bool CMP() {

}  

// Rule 17:
bool A() {

}

 // Rule 18:
bool I() {

}

// Rule 18-2:
bool I_PRIME() {

} 

// Rule 19:
bool R() {

}

// Rule 19-2:
bool R_PRIME(){

}  

// Rule 20:
bool PR() {

}

// Rule 21:
bool SC(){
  
}


// Rule 22:
bool Parser::W() {
  bool result = false;

  if (it_->getLexeme().compare("while") == 0) {
    next_token();
    if (it_->getLexeme().compare("(") == 0) {
      next_token();
      if (CND()) {
        if (it_->getLexeme().compare(")") == 0){
          next_token();
          result = S();
        }
      }
    }
  }
  return result;
}

// Rule 23:
bool Parser::CND() {
  if (E())
    if (RLP())
      return E();

  return false;
}

// Rule 24:
bool Parser::RLP() {
  std::string lex(it_->getLexeme());
  bool result = (lex.compare("==") == 0 || lex.compare("^=") == 0 || lex.compare(">") == 0 ||
    lex.compare("<") == 0 || lex.compare("=>") == 0 || lex.compare("=<") == 0);  

  if (result)
    next_token();

  return result;
}

// Rule 25:
bool Parser::E() {
  if (TEST_PRINT) {
    std::cout << "<E> := + <T> <E Prime>" << std::endl;
  }
  
  if (T()) {
    return E_PRIME();
  }
  return false;
}

// Rule 25-2:
bool Parser::E_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<E Prime> := + <T> <E> | - <T> <E> | <Empty> " << std::endl;
  }

  bool result = false;
  if (it_->getLexeme().compare("+") == 0 || it_->getLexeme().compare("-") == 0) {
    next_token();
    if(T()) {
      result = E_PRIME();
    } else {
      result = false;
    }
  } else { //empty
    result = EMP();
  }
  return result;
}

// Rule 26:
bool Parser::T() {
  if (TEST_PRINT) {
    std::cout << "<T> := <FA> <T Prime>" << std::endl;
  }

  if(FA())
    return T_PRIME();
    
  return false;
}

// Rule 26-2:
bool Parser::T_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<T Prime> := * <FA> <T Prime> | / <FA> <T Prime> | <Empty> " << std::endl;
  }

  bool result = false;
  
  if(it_->getLexeme().compare("*") == 0 || it_->getLexeme().compare("/") == 0){
    next_token();
    if(FA()) {
      result = T_PRIME();  // *FAT
    } else {
      result = false;
    } 
  } else { // empty
    result = EMP();
  }

  return result;
}

// Rule 27:
bool Parser::FA() {
  if (TEST_PRINT) {
    std::cout << "<Factor> := - <Primary> | <Primary>" << std::endl;
  }
  
  if (it_->getLexeme().compare("-") == 0) {
    next_token();
  }

  return PMY();
}

// Rule 28:
bool Parser::PMY() {
  if (TEST_PRINT) {
		std::cout << "<Primary> ::= <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |  <Real>  |   true   |  false " << std::endl;
	}

  bool result = false;
  if(it_->getTokenType().compare("Integer") == 0 || it_->getTokenType().compare("Real") == 0 ||
    it_->getLexeme().compare("true") == 0 || it_->getLexeme().compare("false") == 0) {
      //
      next_token();
      result = true;
  } else if (it_->getLexeme() == "(") {
    next_token();
    if(E()) { 
      result = (it_->getLexeme() == ")");
      if(result) { next_token(); }
    } else {
      result = false;
    }
  } else if (it_->getTokenType() == "Identifier") {
      next_token();
      result = PMY_PRIME();
  }

  return result;
}


// Rule 28-2:
bool Parser::PMY_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<Primary Prime> := <IDs>  | <EMPTY>" << std::endl;
  }

  bool result = false;
  if (it_->getLexeme().compare("(") == 0) {
    next_token();
    if (IDS()) {
      result =  !(it_->getLexeme().compare(")"));
      if (result) { next_token(); }
    }
  } else {
    result = EMP();
  }
  return result;
}

// Rule 29:
bool Parser::EMP() {
  if (TEST_PRINT) {
  }

  return true;
}

