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
    virtual void printPy (std::ostream &out) const = 0;
};

class If
    : public Conditions
{

public:
    If(BasePtr _condition, BasePtr _branch)
        : Conditions(_condition, _branch)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(findreg());
        condition->printMIPS(r1, out, help);
        std::string label = makelabl();
        out << "BEQ " << r1 << ", $0, " << label << std::endl;
        branch->printMIPS(reg, out);
        out << label << ":" << std::endl;
        regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "if (";
        condition->printC(out);
        out << ") \n";
        out << "{";
        branch->printC(out);
        out << " }";
    }
    virtual void printPy (std::ostream &out) const override{
        for(int i = indent; i > 0; i--){
          out << "\t";
        }
        out << "if (";
        condition->printPy(out);
        out << ") :\n";
        indent++;
        for(int i = indent; i > 0; i--){
          out << "\t";
        }
        indent--;
        branch->printPy(out);
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
        std::string label1 = makelabl();
        std::string label2 = makelabl();

        out << "BEQ " << r1 << ", $0, " << label1 << std::endl;
        branch->printMIPS(reg, out);
        out << "J " << label2 << std::endl;
        out << label1 << std::endl;
        elseBranch->printMIPS(reg, out);
        out << label2 << ":" << std::endl;
        regFlag[std::stoi(r1.substr(1))] = 0;
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
        for(int i = indent; i > 0; i--){
          out << "\t";
        }
        out << "if (";
        condition->printPy(out);
        out << ") :\n";
        indent++;
        for(int i = indent; i > 0; i--){
          out << "\t";
        }
        indent--;
        branch->printPy(out);
        out << std::endl;
        out << "else :\n";
        indent++;
        for(int i = indent; i > 0; i--){
          out << "\t";
        }
        indent--;
        elseBranch->printPy(out);
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
    virtual void printPy (std::ostream &out) const override{
        for(int i = indent; i > 0; i--){
          out << "\t";
        }
        out << "switch (";
        condition->printPy(out);
        out << ") :\n";
        indent++;
        for(int i = indent; i > 0; i--){
          out << "\t";
        }
        indent--;
        branch->printPy(out);
    }
};
#endif
