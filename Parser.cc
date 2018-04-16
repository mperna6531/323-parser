#include <iomanip>
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

std::string Parser::get_lexeme() const {
  if (it_ != tokens_.end())
    return it_->getLexeme();

  return "";
}

bool Parser::error(const std::string &msg, int line_num) const {
  std::cout << "Parse Error.  Expected " << msg << ", line: " << line_num << std::endl; 
  return false;
}

int Parser::get_line_num() const {
  if (it_ != tokens_.end())
    return it_->get_line_num();
  
  return (it_ - 1)->get_line_num();
}

void Parser::print_token() const {
  if (it_ != tokens_.end()) {
    std::cout << '\n' << std::left << std::setw(20) << "Token: " + it_-> getTokenType() << std::left << std::setw(20) << 
    "Lexeme: " + it_->getLexeme() << std::endl;

    if (it_->getTokenType().compare("UNKNOWN") == 0) {
      std::cout << "Invalid Token, line: " << get_line_num() << std::endl;
    }
  }
}

void Parser::next_token() {
    if (it_ != tokens_.end()) {
      ++it_;
    } else {
      std::cout << "End of tokens; illegal increment of iterator";
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
      std::cout << "...Exiting" << std::endl;
    }
    
}

// Rule 1:
bool Parser::R18S() {
  if (TEST_PRINT) {
    std::cout << "\t<Rat 18S> := <Opt Function Definitions> %% <Opt Declaration List> <Statement List>"  << std::endl;
  }

  if (OFD()) {
    if (compare_lexeme("%%")) {
      next_token();
      if (ODL()) {
        return SL();
      }
    } else {
      return error("%%", get_line_num());
    }
  }

  return false;
}  

// Rule 2:
bool Parser::OFD() {
  if (TEST_PRINT) {
    std::cout << "\t<Function> := <Function Definitions> | <Empty>"  << std::endl;
  }

  if (compare_lexeme("%%")) 
    return EMP();

  return FD();
}

// Rule 3:
bool Parser::FD() {
  if (TEST_PRINT) {
    std::cout << "\t<Function Definitions> := <Function> <FD Prime>"  << std::endl;
  }

  if (F())
    return FD_PRIME();

  return false;
} 

// Rule 3-2:
bool Parser::FD_PRIME() {
  if (TEST_PRINT) {
    std::cout << "\t<FD Prime> := <Function Definitions> | <Empty>"  << std::endl;
  }

  if (compare_lexeme("function")) 
    return F();

  return EMP();
}


// Rule 4:
bool Parser::F() {
  if (TEST_PRINT) {
    std::cout << "\t<Function> := function <Identifier> [ <Opt Parameter List> ] <Opt Declaration List> <Body>"  << std::endl;
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
          } return error("]", get_line_num());
        }
      } else {
        return error("[", get_line_num());
      }
    } else {
      return error("Identifier", get_line_num());
    }
  }
  
  return error("Keyword 'function'", get_line_num());
}

// Rule 5:
bool Parser::OPL() {
  if (TEST_PRINT) {
    std::cout << "\t<Opt Parameter List> := <Parameter List> | <Empty>"  << std::endl;
  }

  if (compare_lexeme("]"))
    return EMP();

  return PL();
} 

// Rule 6:
bool Parser::PL() {
  if (TEST_PRINT) {
    std::cout << "\t<Parameter List> := <Parameter> <PL Prime>"  << std::endl;
  }

  if (P())
    return PL_PRIME();

  return false;
}

// Rule 6-2:
bool Parser::PL_PRIME() {
  if (TEST_PRINT) {
    std::cout << "\t<PL Prime> := , <Parameter List> | <Empty>"  << std::endl;
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
    std::cout << "\t<Parameter> := <IDs> : <Qualifier>"  << std::endl;
  }

  if (IDS()) {
    if (compare_lexeme(":")) {
      next_token();
      return Q();
    } else return error(":", get_line_num());
  } 

  return error("Identifier(s)", get_line_num());
} 

// Rule 8:
bool Parser::Q() {
  if (TEST_PRINT) {
    std::cout << "\t<Qualifier> := int | bolean | real"  << std::endl;
  }

  if (compare_lexeme("int") || compare_lexeme("boolean") || compare_lexeme("real")) {
    next_token();
    return true;
  }

  return error("Qualifier", get_line_num());
}

// Rule 9:
bool Parser::B() {
  if (TEST_PRINT) {
    std::cout << "\t<Body> := { <Statement List> }"  << std::endl;
  }

  return CMP();
} 

// Rule 10:
bool Parser::ODL() {
  if (TEST_PRINT) {
    std::cout << "\t<Opt Declaration List> := <Declaration List> | <Empty>"  << std::endl;
  }

  if (compare_lexeme("int") || compare_lexeme("boolean") || compare_lexeme("real"))
    return DL();

  return EMP();
  
}

// Rule 11
bool Parser::DL() {
  if (TEST_PRINT) {
    std::cout << "\t<Delcaration List> := <Declaration> ; <DL Prime>"  << std::endl;
  }

  if (D()) {
    if (compare_lexeme(";")) {
      next_token();
      return DL_PRIME();
    } else {
      return error("';'", get_line_num());
    }
  }

  return error("Declaration List", get_line_num());
}

// Rule 11-2:
bool Parser::DL_PRIME() {
  if (TEST_PRINT) {
    std::cout << "\t<DL Prime> := <Declaration List> | <Empty>"  << std::endl;
  }
  
  if (compare_lexeme("int") || compare_lexeme("boolean") || compare_lexeme("real"))
    return DL();

  return EMP();
}

// Rule 12
bool Parser::D() {
  if (TEST_PRINT) {
    std::cout << "\t<Delcaration> := <Qualifier> <IDs>"  << std::endl;
  }

  if (Q()) 
    return IDS();

  return false;
}

// Rule 13:
bool Parser::IDS() {
  if (TEST_PRINT) {
    std::cout << "\t<IDs> := id <IDs Prime>" << std::endl;
  }
  
  if (compare_token_type("Identifier")) {
    next_token();
    return IDS_PRIME();
  } 

  return error("Identifier", get_line_num());
}

// Rule 13-2:
bool Parser::IDS_PRIME() {
  if (TEST_PRINT) {
    std::cout << "\t<IDs Prime> := , <IDs> | <Empty>" << std::endl;
  }
  
  if (compare_lexeme(",")) {
    next_token();
    return IDS(); 
  } 

  return EMP();
}


// Rule 14:
bool Parser::SL() {
  if (TEST_PRINT) {
    std::cout << "\t<Statement List> := <Statement> <SL Prime>" << std::endl;
  }

  if (S())
    return SL_PRIME();

  return false;
}

// Rule 14-2:
bool Parser::SL_PRIME() {
  if (TEST_PRINT) {
    std::cout << "\t<SL Prime> := <Statement List> | <Empty>" << std::endl;
  }
  
  if (compare_lexeme("{") || compare_token_type("Identifier") || compare_token_type("Keyword"))
    return SL();

  if (it_ == tokens_.end() || compare_lexeme("}"))
    return EMP();

  return false;
}

// Rule 15:
bool Parser::S() {
  if (TEST_PRINT) {
    std::cout << "\t<Statement> := <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>"  << std::endl;
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

  return error("Statement", get_line_num());
}

// Rule 16:
bool Parser::CMP() {
  if (TEST_PRINT) {
    std::cout << "\t<Compound> := { <Statement List> }" << std::endl;
  }

  if (compare_lexeme("{")) {
    next_token();
    if (SL()) {
      if (compare_lexeme("}")) {
        next_token();
        return true;
      } else {
        return error("}", get_line_num());
      }
    }
  } else {
    return error("'{'", get_line_num());
  }
  return false;
}  

// Rule 17:
bool Parser::A() {
  if (TEST_PRINT) {
    std::cout << "\t<Assign> := <identifier> = <Expression> ;" << std::endl;
  }

  if (compare_token_type("Identifier")) {
    next_token();
    if (compare_lexeme("=")) {
      next_token();
      if (E()) {
        if (compare_lexeme(";")) {
          next_token();
          return true;
        } else {
          return error("';'", get_line_num());
        }
      }
    } else {
      return error("'='", get_line_num());
    }
  } else {
    return error("Identifier", get_line_num());
  }

  return false;

}

 // Rule 18:
bool Parser::I() {
  if (TEST_PRINT) {
    std::cout << "\t<If> := if ( <Condition> ) <Statement> <If Prime>" << std::endl;
  }

  if (compare_lexeme("if")) {
    next_token();
    if (compare_lexeme("(")) {
      next_token();
      if (CND()) {
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
    std::cout << "\t<If Prime> := endif | else <Statement> endif" << std::endl;
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
    std::cout << "\t<Return> := return <Return Prime>" << std::endl;
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
    std::cout << "\t<Return_Prime> := ; | <Expression> ;" << std::endl;
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
      } else {
        return error("';'", get_line_num());
      }
    }
  }

  return result;
}  

// Rule 20:
bool Parser::PR() {
  if (TEST_PRINT) {
    std::cout << "<Print> := put ( <Expression> ) ;" << std::endl;
  }

  if (compare_lexeme("put")) {
    next_token();
    if (compare_lexeme("(")) {
      next_token();
      if (E()) {
        if (compare_lexeme(")")) {
          next_token();
          if (compare_lexeme(";")) {
            next_token();
            return true;
          } else {
            return error("';'", get_line_num());
          }
        } else {
          return error("')'", get_line_num());
        }
      }
    } else {
      return error("'('", get_line_num());
    }
  }

  return false;
}

// Rule 21:
bool Parser::SC() {
  if (TEST_PRINT) {
    std::cout << "\t<Scan> := get ( <IDs> ) ;" << std::endl;
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
          } else {
            return error("';'", get_line_num());
          }
        } else {
          return error("')'", get_line_num());
        }
      }
    } else {
      return error("'('", get_line_num());
    }
  }
  
  return false;
}


// Rule 22:
bool Parser::W() {
  if (TEST_PRINT) {
    std::cout << "\t<While> := while ( <Condition> ) <Statement>" << std::endl;
  }

  if (compare_lexeme("while")) {
    next_token();
    if (compare_lexeme("(")) {
      next_token();
      if (CND()) {
        if (compare_lexeme(")")){
          next_token();
          return S();
        } else {
          return error("')'", get_line_num());
        }
      }
    } else {
      return error("'('", get_line_num());
    }
  }

  return false;
}

// Rule 23:
bool Parser::CND() {
  if (TEST_PRINT) {
    std::cout << "\t<Condition> := <Expression> <Relop> <Expression>" << std::endl;
  }

  if (E()) {
    if (RLP()) {
      return E();
    } else {
      return error("Relational operator", get_line_num());
    }
  }

  return false;
}

// Rule 24:
bool Parser::RLP() {
  if (TEST_PRINT) {
    std::cout << "\t<Relop> := == | ^= | > | < | => | =<" << std::endl;
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
    std::cout << "\t<Expression> := <Term> <Expression Prime>" << std::endl;
  }
  
  if (T()) 
    return E_PRIME();

  return false;
}

// Rule 25-2:
bool Parser::E_PRIME() {
  if (TEST_PRINT) {
    std::cout << "\t<Expression Prime> := + <Term> <Expression Prime>  | -  <Term> <Expression Prime> | <Empty> " << std::endl;
  }

  bool result = false;
  if (compare_lexeme("+") || compare_lexeme("-")) {
    next_token();
    if(T()) {
      result = E_PRIME();
    } else {
      result = false;
    }
  } else if ((compare_lexeme(")") || compare_lexeme(";") || compare_token_type("Operator"))) { //empty
    result = EMP();
  }
  else {
  result = error("operator or end of expression", get_line_num());
  }
  return result;
}

// Rule 26:
bool Parser::T() {
  if (TEST_PRINT) {
    std::cout << "\t<Term> := <Factor>  <Term Prime>" << std::endl;
  }

  if(FA())
    return T_PRIME();
    
  return false;
}

// Rule 26-2:
bool Parser::T_PRIME() {
  if (TEST_PRINT) {
    std::cout << "\t<Term Prime> := * <Factor> <Term Prime> | / <Factor> <Term Prime> | <Empty>" << std::endl;
  }

  bool result = false;
  
  if (compare_lexeme("*") || compare_lexeme("/")) {
    next_token();
    if (FA()) {
      result = T_PRIME();  // *FAT
    } else {
      result = false;
    } 
  } else if (compare_lexeme(")") || compare_lexeme(";") || compare_token_type("Operator")) { 
    // empty if next lexeme = follow(T) == Follow(E)
    result = EMP();
  } else {
    result = error("operator or end of expression", get_line_num());
  }

  return result;
}

// Rule 27:
bool Parser::FA() {
  if (TEST_PRINT) {
    std::cout << "\t<Factor> := - <Primary> | <Primary>" << std::endl;
  }
  
  if (compare_lexeme("-")) {
    next_token();
  }

  return PMY();
}

// Rule 28:
bool Parser::PMY() {
  if (TEST_PRINT) {
		std::cout << "\t<Primary> ::= <Integer> |  <Identifier>  <Primary Prime> | ( <Expression> ) | <Real> | true | false " << std::endl;
	}

  if (compare_token_type("Integer") || compare_token_type("Real") ||
    compare_lexeme("true") || compare_lexeme("false")) {
    next_token();
    return true;
  } else if (compare_lexeme("(")) {
    next_token();
    if (E()) { 
      if (compare_lexeme(")")) {
        next_token();
        return true;
      }
    }
  } else if (compare_token_type("Identifier")) {
    next_token();
    return PMY_PRIME();
  }

  return error("Primary", get_line_num()); 
}

// Rule 28-2:
bool Parser::PMY_PRIME() {
  if (TEST_PRINT) {
    std::cout << "\t<Primary Prime> := ( <IDs> ) | <EMPTY>" << std::endl;
  }
  
  bool result = false;

  if (compare_lexeme("(")) {
      next_token();
      if (IDS()) {
        if (compare_lexeme(")")) {
          next_token();
          result = true;
        }
      } else {
        result = false;
      }
    } else {
      result = EMP();
    }

  return result;
}

// Rule 29:
bool Parser::EMP() {
  if (TEST_PRINT) {
    std:: cout << "\t<Empty>" << std::endl;
  }

  return true;
}

