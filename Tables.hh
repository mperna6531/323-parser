#ifndef SYMBOL_TABLE_HH
#define SYMBOL_TABLE_HH

#include <map>
#include <stack>
#include "token.hh"

#define STARTING_ADDRESS 2000
#define STARTING_INSTRUCTION 1

struct Symbol {
  std::string identifier_;
  std::string type_;
  size_t address_;
  Symbol(std::string id, std::string &type, size_t address) :
    identifier_(id), type_(type), address_(address) {}
  Symbol() {}
};

struct Instruction {
  size_t address_;
  std::string op_;
  int operand_;
  Instruction(size_t address, std::string &op, int operand) :
    address_(address), op_(op), operand_(operand) {}
  Instruction() {}
};

class SymbolTable {
private:
  size_t address_; 
  std::map<int, Symbol> table_;
public:
  SymbolTable();
  void insert(std::string type, std::string id);
  int get_address(std::string &token);
  bool inSymTable(std::string &token);
  void print();
};

class InstructionTable {
private:
  size_t instruction_;
  std::stack<int> instruction_stack_;
  std::stack<int> jump_stack_;
  std::map<int, Instruction> table_;
public:
  InstructionTable();
  void gen_instr(std::string &op, int operand);
  void print();
};

#endif