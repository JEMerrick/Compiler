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

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out, Py &myPy) const = 0;
};

class AddOperator
    : public ArithOp
{

public:
    AddOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(findreg());
        left->printMIPS(r1, out, help);
        //ADDI RX 0, 5
        std::string r2 = "$" + std::to_string(findreg());
        right->printMIPS(r2, out, help);
        //ADDI RY 0, 5
        out << "ADDU " << reg << ", " << r1 << ", " << r2;
        //ADDU RZ RY RX
        regFlag[std::stoi(r1.substr(1))] = 0;
        regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left->printC(out);
        out << " + ";
        right->printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        left->printPy(out);
        out << " + ";
        right->printPy(out);
    }
};

class SubOperator
    : public ArithOp
{
public:
    SubOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(findreg());
        left->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(findreg());
        right->printMIPS(r2, out, help);
        out << "SUBU " << reg << ", " << r1 << ", " << r2;
        regFlag[std::stoi(r1.substr(1))] = 0;
        regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left->printC(out);
        out << " - ";
        right->printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        left->printPy(out);
        out << " - ";
        right->printPy(out);
    }
};


class MulOperator
    : public ArithOp
{
public:
    MulOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(findreg());
        left->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(findreg());
        right->printMIPS(r2, out, help);
        out << "MUL " << reg << ", " << r1 << ", " << r2;
        regFlag[std::stoi(r1.substr(1))] = 0;
        regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left->printC(out);
        out << " * ";
        right->printC(out);
        out << " )";
      }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        left->printPy(out);
        out << " * ";
        right->printPy(out);
    }
};

class DivOperator
    : public ArithOp
{
public:
    DivOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(findreg());
        left->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(findreg());
        right->printMIPS(r2, out, help);
        out << "DIV " << r1 << ", " << r2;
        out << "MFLO " << reg << std::endl;
        regFlag[std::stoi(r1.substr(1))] = 0;
        regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left->printC(out);
        out << " / ";
        right->printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        left->printPy(out);
        out << " / ";
        right->printPy(out);
    }
};

class ModOperator
    : public ArithOp
{

public:
    ModOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(findreg());
        left->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(findreg());
        right->printMIPS(r2, out, help);
        out << "DIV " << r1 << ", " << r2;
        out << "MFHI " << reg << std::endl;
        regFlag[std::stoi(r1.substr(1))] = 0;
        regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "( ";
        left->printC(out);
        out << " % ";
        right->printC(out);
        out << " )";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        left->printPy(out);
        out << " % ";
        right->printPy(out);
    }
};


#endif
