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

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out, Py &myPy) const = 0;
};

class If
    : public Conditions
{

public:
    If(BasePtr _condition, BasePtr _branch)
        : Conditions(_condition, _branch)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        condition->printMIPS(r1, out, help);
        std::string label = help.makelabl();
        out << "BEQ " << r1 << ", $0, " << label << std::endl;
        branch->printMIPS(reg, out, help);
        out << label << ":" << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "if (";
        condition->printC(out);
        out << ") \n";
        out << "{";
        branch->printC(out);
        out << " }";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        out << "if (";
        condition->printPy(out, myPy);
        out << ") :\n";
        myPy.indent++;
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        myPy.indent--;
        branch->printPy(out, myPy);
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

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$1";
        condition->printMIPS(r1, out, help);
        std::string label1 = help.makelabl();
        std::string label2 = help.makelabl();

        out << "BEQ " << r1 << ", $0, " << label1 << std::endl;
        branch->printMIPS(reg, out, help);
        out << "J " << label2 << std::endl;
        out << label1 << std::endl;
        elseBranch->printMIPS(reg, out, help);
        out << label2 << ":" << std::endl;
        help.regFlag[std::stoi(r1.substr(1))] = 0;
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
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        out << "if (";
        condition->printPy(out, myPy);
        out << ") :\n";
        myPy.indent++;
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        myPy.indent--;
        branch->printPy(out, myPy);
        out << std::endl;
        out << "else :\n";
        myPy.indent++;
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        myPy.indent--;
        elseBranch->printPy(out, myPy);
        out << std::endl;
    }
};

class Switch
    : public Conditions
{

public:
    Switch(BasePtr _condition, BasePtr _branch)
        : Conditions(_condition, _branch)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << "switch (";
        condition->printC(out);
        out << ") \n";
        out << "{";
        branch->printC(out);
        out << " }";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        out << "switch (";
        condition->printPy(out, myPy);
        out << ") :\n";
        myPy.indent++;
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        myPy.indent--;
        branch->printPy(out, myPy);
    }
};
#endif
