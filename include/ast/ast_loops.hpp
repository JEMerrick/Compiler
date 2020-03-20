#ifndef H_LOOPS
#define H_LOOPS

#include <iostream>

#include "ast_base.hpp"


class For
    : public Base
{

protected:
    BasePtr condition;
    BasePtr branch;
    BasePtr initial;

public:
    For(BasePtr _condition, BasePtr _branch, BasePtr _initial)
        : condition (_condition), branch (_branch), initial(_initial)
    {}

    ~For(){
        delete condition;
        delete initial;
        delete branch;
    }

    virtual void printMIPS (std::string reg, std::ostream &out) const override{

    }
    virtual void printC (std::ostream &out) const override{
      out << "for(";
      initial->printC(out);
      out << "; ";
      condition->printC(out);
      out << "; ";
      // i++
      out << ") {" << std::endl;
      branch->printC(out);
      out << "}";
    }
    virtual void printPy (std::ostream &out) const override{
      for(int i = indent; i > 0; i--){
        out << "\t";
      }
      initial->printPy(out);
      out << std::endl;
      for(int i = indent; i > 0; i--){
        out << "\t";
      }
      out << "while ";
      condition->printPy(out);
      out << ":" << std::endl;
      indent++;
      for(int i = indent; i > 0; i--){
        out << "\t";
      }
      branch->printPy(out);
      indent--;
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

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      out << "while(";
      condition->printC(out);
      out << ") {";
      branch->printC(out);
      out << "}";
    }
    virtual void printPy (std::ostream &out) const override{
      for(int i = indent; i > 0; i--){
        out << "\t";
      }
      out << "while ";
      condition->printPy(out);
      out << ":" << std::endl;
      indent++;
      for(int i = indent; i > 0; i--){
        out << "\t";
      }
      branch->printPy(out);
      indent--;
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

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      out << "do {";
      branch->printC(out);
      out << "}";
      out << "while(";
      condition->printC(out);
      out << ")";
    }
    virtual void printPy (std::ostream &out) const override{

    }
};

class Break
    : public Base
{

public:
    BBreak()
    {}

    ~BBreak(){}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      out << "break\n";
    }
    virtual void printPy (std::ostream &out) const override{
      for(int i = indent; i > 0; i--){
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

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      out << "continue\n";
    }
    virtual void printPy (std::ostream &out) const override{
      for(int i = indent; i > 0; i--){
        out << "\t";
      }
      out << "continue\n";
    }
};

#endif
