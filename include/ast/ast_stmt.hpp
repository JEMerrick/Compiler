//TODO: BREAK, CONTINUE, RETURN, EXPGRESSION STMT, DECLARE STMT,
#include <string>
#include <iostream>

#include "ast_base.hpp"

class Expression
    : public Base
{
protected:
    std::string id;
public:
    Expression(const std::string &_id)
        : id(_id)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const{
      // if(localVars[id] != NULL){
      //   std::string r1 = "$1";
      //   out << "lw " << reg << r1 << value;
      // }
      // else{
      //
      // }
      out << id;

    }
    virtual void printC (std::ostream &out) const{
        out << id;
    }
    virtual void printPy (std::ostream &out) const{
      out << id;
    }


};
