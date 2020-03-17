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

    virtual void printMIPS (std::string reg, std::ostream &out) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out) const = 0;
};

class If
    : public Conditions
{

public:
    If(BasePtr _condition, BasePtr _branch)
        : Conditions(_condition, _branch)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
      std::string r1 = "$1";
      condition->printMIPS(r1, out);
      out << "BEQ " << r1 << ", $0, " << "L" << std::endl;
      branch->printMIPS(reg, out);
      out << "L:" << std::endl;
    }
    virtual void printC (std::ostream &out) const override{
      out << "if (";
      condition -> printC(out);
      out << ") \n";
      out << "{";
      branch -> printC(out);
      out << " }";
    }
    virtual void printPy (std::ostream &out) const override{
      out << "if (";
      condition -> printPy(out);
      out << ") :\n";
      out << "  ";
      branch -> printC(out);
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

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      out << "if (";
      condition->printC(out);
      out << ") \n";
      out << "{";
      branch->printC(out);
      out << " } else {\n";
      elseBranch->printC(out);
      out << std::endl;
      out << "}";
    }
    virtual void printPy (std::ostream &out) const override{
      out << "if (";
      condition -> printPy(out);
      out << ") :\n";
      out << "  ";
      branch -> printPy(out);
      out << std::endl;
      out << "else :\n";
      elseBranch->printPy(out);
      out << std::endl;
    }
};
#endif
