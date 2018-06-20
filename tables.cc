#include "SymbolTable.hh"
#include <iostream>

SymbolTable::SymbolTable() : address_(STARTING_ADDRESS) {}

void SymbolTable::insert(std::string type, std::string id) {
  Symbol newRow(type, id, address_++);
  table_[newRow.address_] = newRow;
}

int SymbolTable::get_address(std::string &token) {
  for (auto &i : table_) {
    if (i.second.identifier_ == token) {
      return i.first;
    }
  }
  return -1;
}

bool SymbolTable::inSymTable(std::string &token) {
  for (auto &i : table_) {
    if (i.second.identifier_ == token) {
      return true;
    }
  }
  return false;
}

void SymbolTable::print() {
  for (auto &i : table_) {
    std::cout << "Identifer: "<< i.second.identifier_ << std::endl;
    std::cout << "Type: "<< i.second.type_ << std::endl;
  }
}

InstructionTable::InstructionTable() : instruction_(STARTING_INSTRUCTION) {}

void InstructionTable::gen_instr(std::string &op, int operand) {
  Instruction newRow(instruction_++, op, operand);
  table_[newRow.address_] = newRow;
}

void InstructionTable::print() {
  for (auto &i : table_) {
    std::cout << "Address: " << i.second.address_ << std::endl;
    std::cout << " Operation: "<< i.second.op_ << std::endl;
    std::cout << " Operand: "<< i.second.operand_ << std::endl;
  }
}