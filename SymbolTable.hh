#include <map>
#include "token.hh"

#define STARTING_ADDRESS 2000

struct Symbol {
  std::string identifier_;
  TOKENS::TYPE type_;
  size_t address_;
  Symbol(std::string id, TOKENS::TYPE type, size_t address) :
    identifier_(id),
    type_(type),
    address_(address) {}
};

class SymbolTable {
private:
  size_t address_; 
  std::map<int, Symbol> table_;

public:
  SymbolTable() : address_(STARTING_ADDRESS) {}
};