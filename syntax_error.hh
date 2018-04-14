#ifndef SYNTAX_ERROR_
#define SYNTAX_ERROR

#include<exception>
#include<string>

class syntax_error : public std::exception {
  private:
  std::string msg_;
  
  public:
  syntax_error(std::string &msg) : msg_(msg) {};
};

#endif