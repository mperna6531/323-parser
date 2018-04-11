#include<locale>
#include"token.hh"
#include"FSM.hh"

FSM::FSM() : currentState_(FSM::START), previousState_(FSM::START), lexeme_("")  {}


FSM::INPUT FSM::getInputType(char input) const {
  if (isdigit(input)) return DIGIT;
  if (isalpha(input)) return LETTER;
  if (input == '.') return DECIMAL_PT;
  if (isspace(input)) return WHITE_SPACE;
  if (input == '!') return COMMENT;
  if (input == '$') return DOLLAR_SIGN;

  if (ispunct(input)) {
    switch (input) {
      case '+':
      case '-':
      case '*':
      case '/':
        return OP_1;
      case '<':
      case '>':
        return LT_GT;
      case '=':
        return EQUAL;
      case '^':
        return CARROT;
      case '%':
        return PERCENT;
      case ';':
      case ':':
      case '!':
      case ',':
      case '{':
      case '}':
      case '(':
      case ')':
      case '[':
      case ']':
        return SEPARATOR;
    }
  }
  return OTHER;
}

bool FSM::is_key() const {
  std::set<std::string>::iterator it = keywords_.find(lexeme_.c_str());
  if (it != keywords_.end())
    return true;
  return false;
}

void FSM::transition(char input) {
  FSM::INPUT in = getInputType(input);
  if ((currentState_ == START) && (in == WHITE_SPACE))
    return;  // ignore white space in starting state *special case

  if (in == WHITE_SPACE)
   in = OTHER;

  previousState_ = currentState_;
  currentState_ = static_cast<STATE>(STATE_TABLE[currentState_][in]);

  if((!is_accepting() && !is_in_comment() && previousState_!= FSM::COMM_IN ) || currentState_ == UNKNOWN)
    lexeme_.push_back(input);
}

bool FSM::is_accepting() const {
  bool accepting = false;
  // if machine has clicked over to starting state from an accepting state then return true -- machine has determined end of token
  if (currentState_ == START)
    accepting = ((previousState_ == INT_ACC) || (previousState_ == REAL_ACC) || (previousState_ == ID_L) ||
      (previousState_ == ID_DS) || (previousState_ == OP_1A) || (previousState_ == OP_2A) ||
      (previousState_ == EQ_A) || (previousState_ == SEP_ACC));
  else
    accepting = (currentState_ == UNKNOWN);
    
  return accepting;
}

bool FSM::backup() const {
  // special case if starting with illegal char
  if(currentState_ == UNKNOWN) {
    if(previousState_ == START) {
        return false;
    } else { // currentState == UNKNOWN && previousState_ != START
      return STATE_TABLE[currentState_][BACKUP];
    }
  } else { // currentState == START
    return STATE_TABLE[previousState_][BACKUP];
  }
}

TOKENS::TYPE FSM::getTokenType() const {
  if(is_accepting()) {
    switch(previousState_) {
      case OP_1A:
      case OP_2A:
      case EQ_A:
        return TOKENS::OPERATOR;
      case ID_L:
        if (is_key()) return TOKENS::KEYWORD;
        return TOKENS::IDENTIFIER;
      case ID_DS:
        return TOKENS::IDENTIFIER;
      case INT_ACC:
        return TOKENS::INTEGER;
      case REAL_ACC:
        return TOKENS::REAL;
      case SEP_ACC:
        return TOKENS::SEPARATOR;
      case UNKNOWN:
        return TOKENS::UNKNOWN;
      default:
        return TOKENS::UNKNOWN;
    }
  }

  return TOKENS::UNKNOWN;
}

bool FSM::is_in_comment() const {
  return (currentState_ == COMM_IN);
}

bool FSM::is_starting() const {
  return (currentState_ == START && previousState_ == START);
}

const std::string FSM::getLexeme() const {
  return lexeme_;
}


void FSM::reset() {
  currentState_ = START;
  previousState_ = START;
  lexeme_.clear();
}
