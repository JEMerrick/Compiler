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

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        std::cout << "printMIPSVariablePrimitives" << '\n';
    }
    virtual void printC (std::ostream &out) const{
        out << id;
        std::cout << "printCVariablePrimitives" << '\n';
    }
    virtual void printPy (std::ostream &out, Py &myPy) const{
        out << id;
        std::cout << "printPyVariablePrimitives" << '\n';
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

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        out << "addi " << reg << "$0, " << value;
        std::cout << "printMIPSNumberPrimitives" << '\n';
    }
    virtual void printC (std::ostream &out) const{
        out << value;
        std::cout << "printCNumberPrimitives" << '\n';
    }
    virtual void printPy (std::ostream &out, Py &myPy) const{
        out << value;
        std::cout << "printPyNumberPrimitives" << '\n';
    }

};


#endif
