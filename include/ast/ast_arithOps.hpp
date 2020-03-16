#ifndef H_ARITHOPS
#define H_ARITHOPS

#include <string>
#include <iostream>
#include <math.h>

#include "ast_base.hpp"

class ArithOp : public Base
{
protected:
    BasePtr left;
    BasePtr right;

public:

    ArithOp(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}

    virtual ~ArithOp()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::string reg, std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class AddOperator
    : public ArithOp
{

public:
    AddOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
          std::string r1 = "$" + loopy();
          regFlag[loopy()] = 0;
          left -> printMIPS(r1, out);

          //ADDI RX 0, 5
          //ADDI RY 0, 5
          //ADDU RZ RY RX

          std::string r2 = "$" + loopy();
          regFlag[loopy()] = 0;
          right -> printMIPS(r2, out);
          out << "add " << reg << ", " << r1 << ", " << r2;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " + ";
        right -> printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " + ";
        right -> printPy(out);
    }
};

class SubOperator
    : public ArithOp
{
public:
    SubOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$" + loopy();
      left -> printMIPS(r1, out);
      std::string r2 = "$" + loopy();
      right -> printMIPS(r2, out);
      out << "sub " << reg << ", " << r1 << ", " << r2;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " - ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " - ";
        right -> printPy(out);
    }
};


class MulOperator
    : public ArithOp
{

public:
    MulOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$" + loopy();
      left -> printMIPS(r1, out);
      std::string r2 = "$" + loopy();
      right -> printMIPS(r2, out);
      out << "mul " << reg << ", " << r1 << ", " << r2;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left -> printC(out);
        out << " * ";
        right -> printC(out);
        out << " )";
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " * ";
        right -> printPy(out);
    }
};

class DivOperator
    : public ArithOp
{
public:
    DivOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      std::string r1 = "$" + loopy();
      left -> printMIPS(r1, out);
      std::string r2 = "$" + loopy();
      right -> printMIPS(r2, out);
      out << "div " << reg << ", " << r1 << ", " << r2;
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " / ";
        right -> printPy(out);
    }
};

class ModOperator
    : public ArithOp
{

public:
    ModOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$" + loopy();
      left -> printMIPS(r1, out);
      std::string r2 = "$" + loopy();
      right -> printMIPS(r2, out);
      out << "mod " << reg << ", " << r1 << ", " << r2;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " % ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " % ";
        right -> printPy(out);
};


#endif
