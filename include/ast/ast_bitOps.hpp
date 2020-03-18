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

    virtual void printMIPS (std::string reg, std::ostream &out) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out) const = 0;
};

class BitAnd
    : public BitOp
{

public:
    BitAnd(BasePtr _left, BasePtr _right)
        : BitOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      right -> printMIPS(r2, out);
      out << "AND " << reg << ", " << r1 << ", " << r2;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " & ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " & ";
        right -> printPy(out);
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
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      right -> printMIPS(r2, out);
      out << "OR " << reg << ", " << r1 << ", " << r2;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " | ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " | ";
        right -> printPy(out);
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
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      right -> printMIPS(r2, out);
      out << "XOR " << reg << ", " << r1 << ", " << r2;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " ^ ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " ^ ";
        right -> printPy(out);
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
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      right -> printMIPS(r2, out);
      out << "SLLV " << reg << ", " << r1 << ", " << r2;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " << ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " << ";
        right -> printPy(out);
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
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      right -> printMIPS(r2, out);
      out << "SLRV " << reg << ", " << r1 << ", " << r2;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " >> ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " >> ";
        right -> printPy(out);
    }
};

#endif
