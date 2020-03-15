#ifndef H_PRIMATIVES
#define H_PRIMATIVES

#include <string>
#include <iostream>

#include "ast_base.hpp"

class Variable
    : public Base
{
protected:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    virtual void printMIPS (std::ostream &out) const{

    }
    virtual void printC (std::ostream &out) const{
        out << id;
    }
    virtual void printPy (std::ostream &out) const{
      out << id;
    }


};

class Number
    : public Base
{
protected:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const{
      out << "addi " << reg << "$0, " << value;
    }
    virtual void printC (std::ostream &out) const{
        out << value;
    }
    virtual void printPy (std::ostream &out) const{

    }

};


#endif
