#ifndef H_CONDITIONS
#define H_CONDITIONS

#include <iostream>

#include "ast_base.hpp"

class Conditions
    : public Base
{
protected:
    BasePtr condition;
    BasePtr branch;


public:
    Conditions(BasePtr _condition, BasePtr _branch)
        : condition(_condition)
        , branch(_branch)
    {}

    virtual ~Conditions()
    {
        delete condition;
        delete branch;
    }

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class If
    : public Conditions
{

public:
    If(BasePtr _condition, BasePtr _branch)
        : Conditions(_condition, _branch)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      out << "if (";
      left -> printC(condition);
      out << ") {";
      right -> printC(branch);
      out << " }";
    }
    virtual void printPy (std::ostream &out) const override{
    }
};

class IfElse
    : public Conditions
{
protected:
    BasePtr elseBranch;
public:
    IfElse(BasePtr _condition, BasePtr _branch, BasePtr _elseBranch)
        : Conditions(_condition, _branch), elseBranch(_elseBranch)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
    }
};
#endif
