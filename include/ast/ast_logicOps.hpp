#ifndef H_LOGICOPS
#define H_LOGICOPS

#include <iostream>

#include "ast_base.hpp"

class LogicOp
    : public Base
{
protected:
    BasePtr left;
    BasePtr right;

    LogicOp(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~LogicOp()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::string reg, std::ostream &out) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out) const = 0;
};

class AndOperator
    : public LogicOp
{

public:
    AndOperator(BasePtr _left, BasePtr _right)
        : LogicOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{

    }
};

class OrOperator
    : public LogicOp
{

public:
    OrOperator(BasePtr _left, BasePtr _right)
        : LogicOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{

    }
};

#endif
