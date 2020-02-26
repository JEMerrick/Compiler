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

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};


// -
class NegOperator
    : public Unary
{
public:
    NegOperator(const BasePtr _expr)
        : Unary(_expr)
    {}


    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};


//! logical negation
class LogicNotOperator
    : public Unary
{
public:
    LogicNotOperator(const BasePtr _expr)
        : Unary(_expr)
    {}


    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

//~ bitwise negation
class BitNotOperator
    : public Unary
{
public:
    BitNotOperator(const BasePtr _expr)
        : Unary(_expr)
    {}


    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

#endif
