#include <iomanip>
#include <stdexcept>
#include "Parser.hh"

bool Parser::compare_token_type(const std::string &tkn) const {
  if (it_ != tokens_.end())
    return (it_->getTokenType().compare(tkn) == 0);
    
  return false;
}

bool Parser::compare_lexeme(const std::string &lex) const {
  if (it_ != tokens_.end())
    return (it_->getLexeme().compare(lex) == 0);
    
  return false;
}

void Parser::print_token() const {
  if (it_ != tokens_.end())
    std::cout << '\n' << std::left << std::setw(20) << "Token: " + it_-> getTokenType() << std::left << std::setw(20) << 
    "Lexeme: " + it_->getLexeme() << std::endl;
}

void Parser::next_token() {
  try {
    if (it_ != tokens_.end())
      ++it_;
    else
      throw std::out_of_range("iterator it_ out of range...exiting");
      
  } catch (const std::out_of_range &e) {
    std::cout << e.what() << std::endl;
    exit(1);   
  }

    print_token();
}

Parser::Parser(std::vector<Token> &tokens) : tokens_(tokens), it_(tokens_.begin()) {}

void Parser::parse() {
  // print starting token
  print_token();

    if (R18S()) {
      std::cout << "Successfull Parse of RAT18S Program." << std::endl;
    } else {
      std::cout << "Parse error." << std::endl;
    }
    
}

// Rule 1:
bool Parser::R18S() {
  if (TEST_PRINT) {
    std::cout << "<Rat 18S>  :=  <Opt Function Definitions>  %%  <Opt Declaration List>  <Statement List>"  << std::endl;
  }

  if (OFD()) {
    if (compare_lexeme("%%")) {
      next_token();
      if (ODL()) {
        return SL();
      }
    }
  }

  return false;
}  

// Rule 2:
bool Parser::OFD() {
  if (TEST_PRINT) {
    std::cout << "<Function>  :=  <Function Definitions>  |  <Empty>"  << std::endl;
  }

  if (compare_lexeme("%%")) 
    return EMP();

  return FD();
}

// Rule 3:
bool Parser::FD() {
  if (TEST_PRINT) {
    std::cout << "<Function Definitions>  :=  <Function>  <FD Prime>"  << std::endl;
  }

  if (F())
    return FD_PRIME();

  return false;
} 

// Rule 3-2:
bool Parser::FD_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<FD Prime>  :=  <Function Definitions>  |  <Empty>"  << std::endl;
  }

  if (compare_lexeme("function")) 
    return F();

  return EMP();
}


// Rule 4:
bool Parser::F() {
  if (TEST_PRINT) {
    std::cout << "<Function>  :=  function  <Identifier>  [ <Opt Parameter List> ]  <Opt Declaration List>  <Body>"  << std::endl;
  }

  if (compare_lexeme("function")) {
    next_token();
    if (compare_token_type("Identifier")) {
      next_token();
      if (compare_lexeme("[")) {
        next_token();
        if(OPL()) {
          if (compare_lexeme("]")) {
            next_token();
            if (ODL()) {
              return B();
            }
          }
        }
      }
    }
  }
  
  return false;
}

// Rule 5:
bool Parser::OPL() {
  if (TEST_PRINT) {
    std::cout << "<Opt Parameter List>  := <Parameter List>  |  <Empty>"  << std::endl;
  }

  if (compare_token_type("Identifier"))
    return PL();

  return EMP();
} 

// Rule 6:
bool Parser::PL() {
  if (TEST_PRINT) {
    std::cout << "<Parameter List>  :=  <Parameter>  <PL Prime>"  << std::endl;
  }

  if (P())
    return PL_PRIME();

  return false;
}

// Rule 6-2:
bool Parser::PL_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<PL Prime>  :=  ,  <Parameter List>  |  <Empty>"  << std::endl;
  }

  if (compare_lexeme(",")) {
    next_token();
    return PL();
  }

  return EMP();
} 

// Rule 7:
bool Parser::P() {
  if (TEST_PRINT) {
    std::cout << "<Parameter>  :=  <IDs>  :  <Qualifier>"  << std::endl;
  }

  if (IDS()) {
    if (compare_lexeme(":")) {
      next_token();
      return Q();
    }
  }

  return false;
} 

// Rule 8:
bool Parser::Q() {
  if (TEST_PRINT) {
    std::cout << "<Qualifier>  :=  int  |  bolean  |  real"  << std::endl;
  }

  if (compare_lexeme("int") || compare_lexeme("boolean") || compare_lexeme("real")) {
    next_token();
    return true;
  }

  return false;
}

// Rule 9:
bool Parser::B() {
  if (TEST_PRINT) {
    std::cout << "<Body>  :=  {  <Statement List>  }"  << std::endl;
  }

  if (compare_lexeme("{")) {
    next_token();
    if (SL()) {
      if (compare_lexeme("}")) {
        next_token();
        return true;
      }
    }
  }

  return false;
} 

// Rule 10:
bool Parser::ODL() {
  if (TEST_PRINT) {
    std::cout << "<Opt Declaration List>  :=  <Declaration List>  |  <Empty>"  << std::endl;
  }
  

  if (compare_lexeme("int") || compare_lexeme("boolean") || compare_lexeme("real"))
    return DL();

  return EMP();
  
}

// Rule 11
bool Parser::DL() {
  if (TEST_PRINT) {
    std::cout << "<Delcaration List>  :=  <Declaration>  ;  <DL Prime>"  << std::endl;
  }

  if (D()) {
    if (compare_lexeme(";")) {
      next_token();
      return DL_PRIME();
    }
  }

  return false;
}

// Rule 11-2:
bool Parser::DL_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<DL Prime>  :=  <Declaration List>  |  <Empty>"  << std::endl;
  }
  
  if (compare_lexeme("int") || compare_lexeme("boolean") || compare_lexeme("real"))
    return DL();

  return EMP();
}

// Rule 12
bool Parser::D() {
  if (TEST_PRINT) {
    std::cout << "<Delcaration>  :=  <Qualifier>  <IDs>"  << std::endl;
  }

  if (Q()) 
    return IDS();

  return false;
}

// Rule 13:
bool Parser::IDS() {
  if (TEST_PRINT) {
    std::cout << "<IDs>  := id <IDs Prime>" << std::endl;
  }
  
  if (compare_token_type("Identifier")) {
    next_token();
    return IDS_PRIME();
  }

  return false;
}

// Rule 13-2:
bool Parser::IDS_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<IDs Prime>  := , <IDs>  | <Empty>" << std::endl;
  }
  
  bool result = false;

  if (compare_lexeme(",")) {
    next_token();
    result = IDS(); 
  } else { // empty
    result = EMP();
  }
  return result;
}

// Rule 14:
bool Parser::SL() {
  if (TEST_PRINT) {
    std::cout << "<Statement List>  :=  <Statement>  <SL Prime>" << std::endl;
  }

  if (S())
    return SL_PRIME();

  return false;
}

// Rule 14-2:
bool Parser::SL_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<SL Prime>  :=  <Statement List>  |  <Empty>" << std::endl;
  }
  
  if (compare_lexeme("{") || compare_token_type("Identifier") || compare_token_type("Keyword"))
    return SL();

  return EMP();
}

// Rule 15:
bool Parser::S() {
  if (TEST_PRINT) {
    std::cout << "<Statement>  :=  <Compound>  |  <Assign>  |  <If>  |  <Return>  |  <Print>  |  <Scan>  |  <While>"  << std::endl;
  }
  
  if (compare_token_type("Identifier"))
    return A();

  if (compare_lexeme("{"))
    return CMP();

  if (compare_lexeme("if"))
    return I();

  if (compare_lexeme("return"))
    return R();

  if (compare_lexeme("put"))
    return PR();

  if (compare_lexeme("get"))
    return SC();

  if (compare_lexeme("while"))
    return W();

  return false;
}

// Rule 16:
bool Parser::CMP() {
  if (TEST_PRINT) {
    std::cout << "<Compound>  :=  {  <Statement List>  }" << std::endl;
  }

  if (compare_lexeme("{")) {
    next_token();
    if (SL()) {
      if (compare_lexeme("}")) {
        next_token();
        return true;
      }
    }
  }

  return false;
}  

// Rule 17:
bool Parser::A() {
  if (TEST_PRINT) {
    std::cout << "<Assign>  :=  <identifier>  =  <Expression>  ;" << std::endl;
  }

  bool result = false;

  if (compare_token_type("Identifier")) {
    next_token();
    if (compare_lexeme("=")) {
      next_token();
      if (E()) {
        if (compare_lexeme(";")) {
          next_token();
          result = true;
        }
      }
    } else {
      result = false;
    }
  }

  return result;
}

 // Rule 18:
bool Parser::I() {
  if (TEST_PRINT) {
    std::cout << "<If>  :=  if  (  <Condition>  )  <Statement>  <If Prime>" << std::endl;
  }

  if (compare_lexeme("if")) {
    next_token();
    if (compare_lexeme("(")) {
      next_token();
      if(CND()) {
        if (compare_lexeme(")")) {
          next_token();
          if (S()) {
            return I_PRIME();
          }
        }
      }
    }
  }

  return false;
}

// Rule 18-2:
bool Parser::I_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<If Prime>  :=  endif  |  else  <Statement>  endif" << std::endl;
  }

  bool result = false;

  if (compare_lexeme("endif")) {
    next_token();
    result = true;
  } else { // try else <Statement> endif
    if (compare_lexeme("else")) {
      next_token();
      if (S()) {
        if (compare_lexeme("endif")) {
          result = true;
        }
      }
    }
  }
  return result;
} 

// Rule 19:
bool Parser::R() {
  if (TEST_PRINT) {
    std::cout << "<Return> :=  return  <Return Prime>" << std::endl;
  }

  if (compare_lexeme("return")) {
    next_token();
    return R_PRIME();
  } 

  return false;
}

// Rule 19-2:
bool Parser::R_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<Return_Prime>  :=  ; |  <Expression>" << std::endl;
  }

  bool result = false;

  if (compare_lexeme(";")) {
    next_token();
    result = true;
  } else { // try <Expression> ;
    if (E()) {
      if (compare_lexeme(";")) {
        next_token();
        result = true;
      }
    }
  }

  return result;
}  

// Rule 20:
bool Parser::PR() {
  if (TEST_PRINT) {
    std::cout << "<Print>  :=  put  (  <Expression>  )  ;" << std::endl;
  }

  if (compare_lexeme("put")) {
    next_token();
    if (compare_lexeme("(")) {
      next_token();
      if (E()) {
        if (compare_lexeme(")")){
          next_token();
          if (compare_lexeme(";")) {
            next_token();
            return true;
          }
        }
      }
    }
  }

  return false;
}

// Rule 21:
bool Parser::SC() {
  if (TEST_PRINT) {
    std::cout << "<Scan>  := get  (  <IDs>  )  ;" << std::endl;
  }

  if (compare_lexeme("get")) {
    next_token();
    if (compare_lexeme("(")) {
      next_token();
      if (IDS()) {
        if (compare_lexeme(")")) {
          next_token();
          if  (compare_lexeme(";")) {
            next_token();
            return true;
          }
        }
      }
    }
  }
  
  return false;
}


// Rule 22:
bool Parser::W() {
  if (TEST_PRINT) {
    std::cout << "<While>  :=  while ( <Condition> ) <Statement>" << std::endl;
  }

  if (compare_lexeme("while")) {
    next_token();
    if (compare_lexeme("(")) {
      next_token();
      if (CND()) {
        if (compare_lexeme(")")){
          next_token();
          return S();
        }
      }
    }
  }

  return false;
}

// Rule 23:
bool Parser::CND() {
  if (TEST_PRINT) {
    std::cout << "<Condition>  :=  <Expression>  <Relop>  <Expression>" << std::endl;
  }

  if (E())
    if (RLP())
      return E();

  return false;
}

// Rule 24:
bool Parser::RLP() {
  if (TEST_PRINT) {
    std::cout << "<Relop> :=  ==  | ^=  |  >  | < | =>  | =<" << std::endl;
  }

  bool result = (compare_lexeme("==") || compare_lexeme("^=") || compare_lexeme(">") ||
    compare_lexeme("<") || compare_lexeme("=>") || compare_lexeme("=<"));  

  if (result)
    next_token();

  return result;
}

// Rule 25:
bool Parser::E() {
  if (TEST_PRINT) {
    std::cout << "<Expression>  :=  +  <Term>  <Expression Prime>" << std::endl;
  }
  
  if (T()) {
    return E_PRIME();
  }

  return false;
}

// Rule 25-2:
bool Parser::E_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<Expression Prime>  :=  +  <Term>  <Expression Prime>   |  -  <Term>  <Expression Prime>  |  <Empty> " << std::endl;
  }

  bool result = false;
  if (compare_lexeme("+") || compare_lexeme("-")) {
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
    std::cout << "<Term>  :=  <Factor>   <Term Prime>" << std::endl;
  }

  if(FA())
    return T_PRIME();
    
  return false;
}

// Rule 26-2:
bool Parser::T_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<Term Prime>  :=  *  <Factor>  <Term Prime>  |  /  <Factor>  <Term Prime>  |  <Empty> " << std::endl;
  }

  bool result = false;
  
  if (compare_lexeme("*") || compare_lexeme("/")) {
    next_token();
    if (FA()) {
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
    std::cout << "<Factor>  :=  -  <Primary>  |  <Primary>" << std::endl;
  }
  
  if (compare_lexeme("-")) {
    next_token();
  }

  return PMY();
}

// Rule 28:
bool Parser::PMY() {
  if (TEST_PRINT) {
		std::cout << "<Primary>  ::=  <Integer>  |   <Identifier>  <Primary Prime>  |   ( <Expression> )   |  <Real>  |   true   |  false " << std::endl;
	}

  bool result = false;

  if (compare_token_type("Integer") || compare_token_type("Real") ||
    compare_lexeme("true") || compare_lexeme("false")) {
    next_token();
    result = true;
  } else if (it_->getLexeme() == "(") {
    next_token();
    if (E()) { 
      if (it_->getLexeme() == ")") {
        next_token();
        result = true;
      }
    }
  } else if (compare_token_type("Identifier")) {
      next_token();
      if (compare_lexeme("(")) {
        next_token();
        if (IDS()) {
          if (compare_lexeme(")")) {
            next_token();
            result = true;
          }
        }
      }
      result = PMY_PRIME();
  }

  return result;
}


// Rule 28-2:
bool Parser::PMY_PRIME() {
  if (TEST_PRINT) {
    std::cout << "<Primary Prime>  :=  <IDs>  |  <EMPTY>" << std::endl;
  }

  bool result = false;
  if (compare_token_type("Identifier")) {
    next_token();
    if (compare_lexeme("(")) {
      next_token();
      if (IDS()) {
        next_token();
        if (compare_lexeme("))")) {
          next_token();
          result = true;
        }
      }
    }
  } else {  // else return empty
    result = EMP();
  }

  return result;
}

// Rule 29:
bool Parser::EMP() {
  if (TEST_PRINT) {
    std:: cout << "<Empty>" << std::endl;
  }

  return true;
}

