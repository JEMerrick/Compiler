#ifndef H_ASSIGNOPS
#define H_ASSIGNOPS

#include <iostream>
#include <string>
#include "ast_base.hpp"

class AssignOp
    : public Base
{
protected:
    std::string variable;

public:
    AssignOp(std::string _variable)
        : variable(_variable)
    {}

    virtual ~AssignOp()
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out) const = 0;
};

class AssignEqualOperator
    : public AssignOp
{
protected:
    BasePtr myExpr;
public:
    AssignEqualOperator(std::string _variable, BasePtr _expr)
        : AssignOp(_variable), myExpr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      if(){
        throw "Variable has not been declared. ";
      }
      out << "ADDU " << reg << ", " << "$0, " << r1 << std::endl; 
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << " = ";
        myExpr->printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        out << variable;
        out << " = ";
        myExpr->printPy(out);
    }
};


//classes for +=, -=, ++ post/pre, -- post/pre here

#endif
