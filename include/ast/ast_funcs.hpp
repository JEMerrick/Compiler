#ifndef H_FUNCS
#define H_FUNCS

#include <iostream>
#include <string>

#include "ast_base.hpp"


class DefFunc
    : public Base
{

protected:
    std::string type;
    std::string funcName;
    BasePtr varList;
    BasePtr branch;

public:
    DefFunc(std::string _type, std::string _funcName, BasePtr _varList, BasePtr _branch)
        : type(_type), funcName(_funcName), varList(_varList), branch(_branch)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << type << " " << funcName << "(";
        varList->printC(out);
        out << ") {" << std::endl;
        branch->printC(out);//return 1
        out << "}" << std::endl;

    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "def " << funcName << "(";
        varList->printPy(out, myPy);
        out << "):" << std::endl;
        myPy.indent++;
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        branch->printPy(out, myPy);//return 1
        myPy.indent--;
    }
};

class CallFunc
    : public Base
{
protected:
    std::string type;
    std::string funcName;
    BasePtr varList;

public:
    CallFunc(std::string _type, std::string _funcName, BasePtr _varList)
        : type(_type), funcName(_funcName), varList(_varList)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << type << " " << funcName << "(";
        varList->printC(out);
        out << ");" << std::endl;
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "def " << funcName << "(";
        varList->printPy(out, myPy);
        out << ")" << std::endl;
    }
};

class Arg
    : public Base
{
protected:
    std::string type;
    std::string id;
    BasePtr nextArg;

public:
    Arg(std::string _type, std::string _id, BasePtr _nextArg)
        : type(_type), id(_id), nextArg(_nextArg)
    {}

    ~Arg(){
        if(nextArg!=NULL){
            delete nextArg;
        }
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        if(nextArg != NULL){
            nextArg->printC(out);
            out << ", ";
        }
        out << type << " " << id;
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        if(nextArg!=NULL){
            nextArg->printPy(out, myPy);
            out << ", ";
        }
        out << id;
    }
};

class ArgList
    : public Base
{
protected:
    BasePtr arg;
    BasePtr nextArg;

public:
    ArgList(BasePtr _arg, BasePtr _nextArg)
        : arg(_arg), nextArg(_nextArg)
    {}

    ~ArgList(){
        if(nextArg!=NULL){
            delete nextArg;
        }
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        if(arg != NULL){
          if(nextArg != NULL){
              nextArg->printC(out);
              out << ", ";
          }
          arg->printC(out);
        }
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
      if(arg != NULL){
        if(nextArg != NULL){
            nextArg->printPy(out, myPy);
            out << ", ";
        }
        arg->printPy(out, myPy);
      }
    }
};

class VarList
    : public Base
{
protected:
    BasePtr var;
    BasePtr nextVar;

public:
    VarList(BasePtr _var, BasePtr _nextVar)
        : var(_var), nextVar(_nextVar)
    {}

    ~VarList(){
        if(nextVar!=NULL){
            delete nextVar;
        }
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        if(var != NULL){
          if(nextVar != NULL){
              nextVar->printC(out);
              out << ", ";
          }
          var->printC(out);
        }
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
      if(var != NULL){
        if(nextVar != NULL){
            nextVar->printPy(out, myPy);
            out << ", ";
        }
        var->printPy(out, myPy);
      }
    }
};

class Declare_Vars
    : public Base
{

public:
    Declare_Vars()
    {}

    ~Declare_Vars(){}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "declare _varList";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << "Declare_Var";
    }
};

class Declare_Var
    : public Base
{

public:
    Declare_Var()
    {}

    ~Declare_Var(){}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "declare _varList";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        for(int i = myPy.indent; i > 0; i--){
            out << "\t";
        }
        out << "Declare_Var";
    }
};

#endif
