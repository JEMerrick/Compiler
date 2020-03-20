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
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      left -> printMIPS(r2, out);
      std::string label = makelabel();

      //out << "ADDI " << reg << ", $0, 0" << std::endl;
      out << "BNE " << r1 << ", " << r2 << ", " << label << std::endl;
      //out << "ADDI " << reg << ", $0, 1" << std::endl;
      out << label << ":" << std::endl;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;

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
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      left -> printMIPS(r2, out);
      std::string label = makelabel();

      //out << "ADDI " << reg << ", $0, 0" << std::endl;
      out << "BEQ " << r1 << ", " << r2 << ", " << label << std::endl;
      //out << "ADDI " << reg << ", $0, 1" << std::endl;
      out << label << ":" << std::endl;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " != ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " != ";
        right -> printPy(out);
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
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      left -> printMIPS(r2, out);

      out << "SLT " << reg << ", " << r1 << ", " << r2 << std::endl;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " < ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " < ";
        right -> printPy(out);
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
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      left -> printMIPS(r2, out);

      out << "SLT " << reg << ", " << r2 << ", " << r1 << std::endl;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " > ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " > ";
        right -> printPy(out);
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
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      left -> printMIPS(r2, out);
      std::string r3 = "$" + std::to_string(findreg());
      left -> printMIPS(r3, out);

      out << "SLT " << reg << ", " << r2 << ", " << r1 << std::endl;
      out << "ADDI " << r3 << " $0, 1" << std::endl;
      out << "SLT " << reg << ", " << reg << ", " << r3 << std::endl;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;
      regFlag[std::stoi(r3.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left -> printC(out);
        out << " <= ";
        right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
        left -> printPy(out);
        out << " <= ";
        right -> printPy(out);
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
      std::string r1 = "$" + std::to_string(findreg());
      left -> printMIPS(r1, out);
      std::string r2 = "$" + std::to_string(findreg());
      left -> printMIPS(r2, out);
      std::string r3 = "$" + std::to_string(findreg());
      left -> printMIPS(r3, out);

      out << "SLT " << reg << ", " << r1 << ", " << r2 << std::endl;
      out << "ADDI " << r3 << " $0, 1" << std::endl;
      out << "SLT " << reg << ", " << reg << ", " << r3 << std::endl;
      regFlag[std::stoi(r1.substr(1))] = 0;
      regFlag[std::stoi(r2.substr(1))] = 0;
      regFlag[std::stoi(r3.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
      left -> printC(out);
      out << " >= ";
      right -> printC(out);
    }
    virtual void printPy (std::ostream &out) const override{
      left -> printPy(out);
      out << " >= ";
      right -> printPy(out);
    }
};

#endif
