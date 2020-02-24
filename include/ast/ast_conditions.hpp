#ifndef H_CONDITIONS
#define H_CONDITIONS

#include <iostream>

#include "ast_base.hpp"

class Conditions
    : public Base
{
protected:
    BasePtr left;
    BasePtr right;

    Conditions(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Conditions()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class If
    : public Conditions
{

public:
    If(BasePtr _left, BasePtr _right)
        : Conditions(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
    }
};

class IfElse
    : public Conditions
{

public:
    IfElse(BasePtr _left, BasePtr _right)
        : Conditions(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
    }
};
#endif
