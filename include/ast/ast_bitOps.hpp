#ifndef H_BITOPS
#define H_BITOPS

#include <iostream>

#include "ast_base.hpp"

class BitOp
    : public Base
{
protected:
    BasePtr left;
    BasePtr right;

    BitOp(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~BitOp()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::string reg, std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class BitAnd
    : public BitOp
{

public:
    BitAnd(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$" + loopy();
      left -> printMIPS(r1, out);
      std::string r2 = "$" + loopy();
      right -> printMIPS(r2, out);
      out << "and " << reg << ", " << r1 << ", " << r2;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " & ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        out << "( ";
        left -> printPy(out);
        out << " & ";
        right -> printPy(out);
        out << " )";
    }
};

class BitOr
    : public BitOp
{

public:
    BitOr(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$" + loopy();
      left -> printMIPS(r1, out);
      std::string r2 = "$" + loopy();
      right -> printMIPS(r2, out);
      out << "or " << reg << ", " << r1 << ", " << r2;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " | ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        out << "( ";
        left -> printPy(out);
        out << " | ";
        right -> printPy(out);
        out << " )";
    }
};

class ExorOperator
    : public BitOp
{

public:
    ExorOperator(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$" + loopy();
      left -> printMIPS(r1, out);
      std::string r2 = "$" + loopy();
      right -> printMIPS(r2, out);
      out << "xor " << reg << ", " << r1 << ", " << r2;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " ^ ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        out << "( ";
        left -> printPy(out);
        out << " ^ ";
        right -> printPy(out);
        out << " )";
    }
};

class LshiftOperator
    : public BitOp
{

public:
    LshiftOperator(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$" + loopy();
      left -> printMIPS(r1, out);
      std::string r2 = "$" + loopy();
      right -> printMIPS(r2, out);
      out << "sll " << reg << ", " << r1 << ", " << r2;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " << ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        out << "( ";
        left -> printPy(out);
        out << " << ";
        right -> printPy(out);
        out << " )";
    }
};

class RshiftOperator
    : public BitOp
{

public:
    RshiftOperator(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$" + loopy();
      left -> printMIPS(r1, out);
      std::string r2 = "$" + loopy();
      right -> printMIPS(r2, out);
      out << "slr " << reg << ", " << r1 << ", " << r2;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " >> ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        out << "( ";
        left -> printPy(out);
        out << " >> ";
        right -> printPy(out);
        out << " )";
    }
};

#endif
