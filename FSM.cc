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
  std::set<std::string>::iterator it = KEYWORDS.find(lexeme_.c_str());
  if (it != KEYWORDS.end())
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
  
  if (push_current())
    lexeme_.push_back(input);
}

bool FSM::push_current() const {
  bool not_comment = currentState_ != COMM_IN && previousState_ != COMM_IN;

    if (not_comment) {
      if (is_accepting()) {
        return (previousState_ == START);
      } else {
        return !is_accepting();
      }
    }

    return false;
}

bool FSM::is_accepting() const {
  bool accepting = false;
  // if machine has clicked over to starting state from an accepting state then return true -- machine has determined end of token
  if (currentState_ == START) {
    accepting = ((previousState_ == INT_ACC) || (previousState_ == REAL_ACC) || (previousState_ == ID_L) ||
      (previousState_ == ID_DS) || (previousState_ == OP_1A) || (previousState_ == OP_2A) ||
      (previousState_ == EQ_A) || (previousState_ == SEP_ACC));
  } else {
    // UNKNOWN is unknown token is accepting state for unknown token
    accepting = (currentState_ == UNKNOWN || currentState_ == INV_R);
  }
  return accepting;
}

bool FSM::backup() const {
  // special case if starting with illegal char - do not back up and re-process
  if (currentState_ == UNKNOWN) {
    if (previousState_ == START) {
      return false;
    } else {
      return STATE_TABLE[currentState_][BACKUP];
    }
  } else if (currentState_ == START && previousState_ != START) {
    // determine if machine is in starting state from accepting state and not initial char
    // if yes then return BACKUP value for last state
    return STATE_TABLE[previousState_][BACKUP];
  } else {
    return STATE_TABLE[currentState_][BACKUP];
  }
}

TOKENS::TYPE FSM::getTokenType() const {
  if (currentState_ == UNKNOWN) return TOKENS::UNKNOWN;

  if (is_accepting()) {
    switch (previousState_) {
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
      default:
        break;
    }
  }

  return TOKENS::UNKNOWN;
}

const std::string FSM::getLexeme() const {
  return lexeme_;
}

void FSM::reset() {
  currentState_ = START;
  previousState_ = START;
  lexeme_.clear();
}
