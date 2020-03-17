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

    virtual void printMIPS (std::string reg, std::ostream &out) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out) const = 0;
};

class EqualOperator
    : public CondOp
{

public:
    EqualOperator(BasePtr _left, BasePtr _right)
        : CondOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$1";
      left -> printMIPS(r1, out);
      std::string r2 = "$2";
      right -> printMIPS(r2, out);

      //out << "ADDI " << reg << ", $0, 0" << std::endl;
      out << "BNE " << r1 << ", " << r2 << ", " << "L" << std::endl;
      //out << "ADDI " << reg << ", $0, 1" << std::endl;
      out << "L:" << std::endl;

    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " == ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " == ";
        right -> printPy(out);
    }
};

class NotEqOperator
    : public CondOp
{

public:
    NotEqOperator(BasePtr _left, BasePtr _right)
        : CondOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
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

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
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

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
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
        left -> printPy(out);
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

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
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

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{

    }
};

#endif
