#ifndef H_CONDOPS
#define H_CONDOPS

#include <iostream>

#include "ast_base.hpp"

class CondOp
    : public Base
{
protected:
    BasePtr left;
    BasePtr right;

    CondOp(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~CondOp()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class EqualOperator
    : public CondOp
{

public:
    EqualOperator(BasePtr _left, BasePtr _right)
        : CondOp(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " == ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        out << "( ";
        left -> printPy(out);
        out << " == ";
        right -> printPy(out);
        out << " )";
    }
};

class NotEqOperator
    : public CondOp
{

public:
    NotEqOperator(BasePtr _left, BasePtr _right)
        : CondOp(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " != ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        out << "( ";
        left -> printPy(out);
        out << " != ";
        right -> printPy(out);
        out << " )";
    }
};

class LessOperator
    : public CondOp
{

public:
    LessOperator(BasePtr _left, BasePtr _right)
        : CondOp(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " < ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        out << "( ";
        left -> printPy(out);
        out << " < ";
        right -> printPy(out);
        out << " )";
    }
};

class GreaterOperator
    : public CondOp
{

public:
    GreaterOperator(BasePtr _left, BasePtr _right)
        : CondOp(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " > ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        out << "( ";
        left -> printPY(out);
        out << " > ";
        right -> printPy(out);
        out << " )";
    }
};

class LeqOperator
    : public CondOp
{

public:
    LeqOperator(BasePtr _left, BasePtr _right)
        : CondOp(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " <= ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        out << "( ";
        left -> printPy(out);
        out << " <= ";
        right -> printPy(out);
        out << " )";
    }
};

class GeqOperator
    : public CondOp
{

public:
    GeqOperator(BasePtr _left, BasePtr _right)
        : CondOp(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{

    }
};

#endif
