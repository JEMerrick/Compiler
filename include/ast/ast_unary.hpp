#ifndef H_UNARY
#define H_UNARY

#include <string>
#include <iostream>

#include "ast_base.hpp"

class Unary
    : public Base
{
protected:
    BasePtr expr;

    Unary(const BasePtr _expr)
        : expr(_expr)
    {}
public:
    virtual ~Unary()
    {
        delete expr;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out, Py &myPy) const = 0;
};


// -
class NegOperator
    : public Unary
{
public:
    NegOperator(const BasePtr _expr)
        : Unary(_expr)
    {}


    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{}
    virtual void printC (std::ostream &out) const override{
        out << "-" << expr->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "-" << expr->printPy(out, myPy);
    }
};


//! logical negation
class LogicNotOperator
    : public Unary
{
public:
    LogicNotOperator(const BasePtr _expr)
        : Unary(_expr)
    {}


    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{}
    virtual void printC (std::ostream &out) const override{
        out << "!" << expr->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "!" << expr->printPy(out, myPy);
    }
};

//~ bitwise negation
class BitNotOperator
    : public Unary
{
public:
    BitNotOperator(const BasePtr _expr)
        : Unary(_expr)
    {}


    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{}
    virtual void printC (std::ostream &out) const override{
        out << "~" << expr->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "~" << expr->printPy(out, myPy);
    }
};

#endif
