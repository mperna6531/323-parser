#include <iostream>
#include <vector>

#include "token.hh"
#include "scanner.hh"
#include "ParseError.hh"

class Parser {
private:
  std::vector<Token> tokens_;
  std::vector<Token>::iterator it_;

  // debugging mode
  static const bool TEST_PRINT = true;
  void print_token();

  void next_token();
public:
  Parser(std::vector<Token> &tokens);
  void parse();

  bool R18S();  // Rule 1
  bool OFD();  // Rule 2
  bool FD();  // Rule 3
  bool FD_PRIME();  // Rule 3-2
  bool F();   // Rule 4
  bool OPL();  // Rule 5
  bool PL();  // Rule 6
  bool PL_PRIME();  // Rule 6-2
  bool P();  // Rule 7
  bool Q();  // Rule 8
  bool B();  // Rule 9
  bool ODL();  // Rule 10
  bool DL();  // Rule 11
  bool DL_PRIME();  // Rule 11-2
  bool D();  // Rule 12
  bool IDS();  // Rule 13
  bool IDS_PRIME();  // Rule 13-2
  bool SL();  // Rule 14
  bool SL_PRIME();  // Rule 14-2
  bool S();  // Rule 15
  bool CMP();  // Rule 16
  bool A();  // Rule 17
  bool I();  // Rule 18
  bool I_PRIME();  // Rule 18-2
  bool R();  // Rule 19
  bool R_PRIME();  // Rule 19-2
  bool PR();  // Rule 20
  bool SC();  // Rule 21
  bool W();  // Rule 22
  bool CND();  // Rule 23
  bool RLP();  // Rule 24
  bool E();  // Rule 25
  bool E_PRIME();  // Rule 25-2
  bool T();  // Rule 26
  bool T_PRIME(); // Rule 26-2
  bool FA();  // Rule 27
  bool PMY();   // Rule 28
  bool PMY_PRIME();  // Rule 28-2
  bool EMP();  // Rule 29:
};