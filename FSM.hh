#ifndef FSM_H_INCLUDED
#define FSM_H_INCLUDED

#include"token.hh"
#include<set>

class FSM {
private:
  enum INPUT { CURRENT_STATE = 0, OP_1, EQUAL, CARROT, LT_GT, COMMENT, SEPARATOR, PERCENT, LETTER, DIGIT,
    DOLLAR_SIGN, DECIMAL_PT, OTHER, BACKUP, WHITE_SPACE };
  enum STATE { START = 1, OP_1A, EQ_A, OP_2A, SEP_ACC, COMM_IN, CAR_CHECK, PER_CHECK, ID_L, ID_INV,
    ID_DS, INT_ACC, REAL_IN, REAL_ACC, UNKNOWN };

// DFSM for RAT18s
// all accepting states including unknown routed to START with ensuing input
//
const int STATE_TABLE[16][14] =
 {{ CURRENT_STATE,OP_1,  EQUAL,  CARROT,    LT_GT,   COMMENT,  SEPARATOR, PERCENT,  LETTER, DIGIT, DOLLAR_SIGN,DECIMAL_PT,OTHER,  BACKUP},
  { START,        OP_1A, EQ_A,   CAR_CHECK, OP_1A,   COMM_IN,  SEP_ACC,   PER_CHECK,ID_L,   INT_ACC,UNKNOWN,   UNKNOWN,   UNKNOWN,0  },
  { OP_1A,        START, START,  START,     START,   START,    START,     START,    START,  START, START,      START,     START,  1  },
  { EQ_A,         START, OP_2A,  START,     OP_2A,   START,    START,     START,    START,  START, START,      START,     START,  1  },
  { OP_2A,        START, START,  START,     START,   START,    START,     START,    START,  START, START,      START,     START,  1  },
  { SEP_ACC,      START, START,  START,     START,   START,    START,     START,    START,  START, START,      START,     START,  1  },
  { COMM_IN,      COMM_IN,COMM_IN,COMM_IN,  COMM_IN, START,    COMM_IN,   COMM_IN,  COMM_IN,COMM_IN,COMM_IN,   COMM_IN,   COMM_IN,0  },
  { CAR_CHECK,    UNKNOWN,OP_2A, UNKNOWN,   UNKNOWN, UNKNOWN,  UNKNOWN,   UNKNOWN,  UNKNOWN,UNKNOWN,UNKNOWN,   UNKNOWN,   UNKNOWN,1  },
  { PER_CHECK,    UNKNOWN,UNKNOWN,UNKNOWN,  UNKNOWN, UNKNOWN,  UNKNOWN,   OP_2A,    UNKNOWN,UNKNOWN,UNKNOWN,   UNKNOWN,   UNKNOWN,0  },
  { ID_L,         START, START,  START,     START,   START,    START,     START,    ID_L,   ID_INV, ID_DS,     START,     START,  1  },
  { ID_INV,       UNKNOWN,UNKNOWN,UNKNOWN,  UNKNOWN, UNKNOWN,  UNKNOWN,   UNKNOWN,  ID_L,   ID_INV, ID_DS,     UNKNOWN,   UNKNOWN,0  },
  { ID_DS,        START, START,  START,     START,   START,    START,     START,    START,  START,  START,     START,     START,  1  },
  { INT_ACC,      START, START,  START,     START,   START,    START,     START,    START,  INT_ACC,START,     REAL_IN,   START,  1  },
  { REAL_IN,      START, START,  START,     START,   START,    START,     START,    START,  REAL_ACC,UNKNOWN,  UNKNOWN,   UNKNOWN,0  },
  { REAL_ACC,     START, START,  START,     START,   START,    START,     START,    START,  REAL_ACC,START,    START,     START,  1  },
  { UNKNOWN,      START, START,  START,     START,   START,    START,     START,    START,  START,  START,     START,     START,  1  }};

  STATE currentState_;
  STATE previousState_;
  INPUT getInputType(char input) const;
  const std::set<std::string> keywords_ = { "int", "boolean", "real", "if", "endif",
    "else", "return", "put", "get", "while", "true", "false", "function" };
  bool is_key() const;
  std::string lexeme_;
public:
  FSM();
  void transition(char input);
  bool is_in_comment() const;
  bool is_accepting() const;
  bool backup() const;
  void reset();
  const std::string getLexeme() const;
  TOKENS::TYPE getTokenType() const;
};

#endif // FSM_H_INCLUDED
