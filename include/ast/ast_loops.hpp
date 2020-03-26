#ifndef H_LOOPS
#define H_LOOPS

#include <iostream>

#include "ast_base.hpp"

class Scope
    : public Base
{

protected:
BasePtr scop;

public:
    Scope(BasePtr _scop)
        : scop(_scop)
    {}

    ~Scope(){
      delete scop;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        scop->printMIPS(reg, out, help);
    }
    virtual void printC (std::ostream &out) const override{
        out << "{" << std::endl;
        scop->printC(out);
        out << "}";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        scop->printPy(out, myPy);
    }
};

class For
    : public Base
{

protected:
    BasePtr condition;
    BasePtr branch;
    BasePtr initial;
    BasePtr incrementordecrement;

public:
    For(BasePtr _condition, BasePtr _branch, BasePtr _initial)
        : condition (_condition), branch (_branch), initial(_initial)
    {}

    ~For(){
        delete condition;
        delete initial;
        delete branch;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
      out << "for(";
      initial->printC(out);
      out << "; ";
      condition->printC(out);
      out << "; ";
      incrementordecrement->printC(out);
      out << ") {" << std::endl;
      branch->printC(out);
      out << "}";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
      for(int i = myPy.indent; i > 0; i--){
        out << "\t";
      }
      initial->printPy(out, myPy);
      out << std::endl;
      for(int i = myPy.indent; i > 0; i--){
        out << "\t";
      }
      out << "while ";
      condition->printPy(out, myPy);
      out << ":" << std::endl;
      myPy.indent++;
      for(int i = myPy.indent; i > 0; i--){
        out << "\t";
      }
      branch->printPy(out, myPy);
      myPy.indent--;
      out << std::endl;
    }
};

class While
    : public Base
{

protected:
    BasePtr condition;
    BasePtr branch;

public:
    While(BasePtr _condition, BasePtr _branch)
        : condition (_condition), branch (_branch)
    {}

    ~While(){
        delete condition;
        delete branch;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "while(";
        condition->printC(out);
        out << ") {";
        branch->printC(out);
        out << "}";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << "while ";
        condition->printPy(out, myPy);
        out << ":" << std::endl;
        myPy.indent++;
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        branch->printPy(out, myPy);
        myPy.indent--;
        out << std::endl;
    }
};

class Do
    : public Base
{

protected:
    BasePtr condition;
    BasePtr branch;

public:
    Do(BasePtr _condition, BasePtr _branch)
        : condition (_condition), branch (_branch)
    {}

    ~Do(){
        delete condition;
        delete branch;
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "do {";
        branch->printC(out);
        out << "}";
        out << "while(";
        condition->printC(out);
        out << ")";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{

    }
};

class BBreak
    : public Base
{

public:
    BBreak()
    {}

    ~BBreak(){}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "break\n";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << "break\n";
    }
};

class CContinue
    : public Base
{

public:
    CContinue()
    {}

    ~CContinue(){}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "continue\n";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << "continue\n";
    }
};

#endif
