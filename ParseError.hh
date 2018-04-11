#include<exception>
#include<string>

class ParseError : public std::exception {
  private:
  std::string msg_;
  
  public:
  ParseError(std::string &msg) : msg_(msg) {};
};