#ifndef H_ASSIGNOPS
#define H_ASSIGNOPS

#include <iostream>

#include "ast_base.hpp"

class AssignOp
    : public Base
{
protected:
    BasePtr left;
    BasePtr right;

    AssignOp(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~AssignOp()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class AssignEqualOperator
    : public AssignOp
{

public:
    AssignEqualOperator(BasePtr _left, BasePtr _right)
        : AssignOp(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      out << "( " << (left -> printC(out)) << " = " << (right -> printC(out)) << " )";
    }
    virtual void printPy (std::ostream &out) const override{
      out << "( " << (left -> printC(out)) << " = " << (right -> printC(out)) << " )";
    }
};


//classes for +=, -=, ++ post/pre, -- post/pre here

#endif
