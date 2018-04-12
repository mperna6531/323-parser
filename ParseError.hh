#ifndef PARSE_ERROR_HH
#define PARSE_ERROR_HH

#include<exception>
#include<string>

class ParseError : public std::exception {
  private:
  std::string msg_;
  
  public:
  ParseError(std::string &msg) : msg_(msg) {};
};

#endif