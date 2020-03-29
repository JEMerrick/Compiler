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
        help.newfunc();
        out << ".text" << std::endl;
        out << ".align 2" << std::endl;
        out << ".globl" << std::endl;
        out << ".ent" << std::endl;
        out << funcName << ":" << std::endl;
        out << "SW $fp, 0($sp)" << std::endl;
        out << "SW $31, -4($sp)" << std::endl;
        out << "MOVE $fp, $sp" << std::endl;
        if(varList == NULL){
            help.parameters=0;
            varList->printMips(reg, out, help);
        }
        if(branch != NULL){
            std::string newdreg = "$" + std::to_string(help.findreg());
            branch->printMips(newdreg, out, help);
            help.regFlag[std::stoi(r1.substr(1))] = 0;
        }
        out << "LW $31, -4($fp)" << std::endl;
        out << "LW $fp, 0($fp)" << std::endl;
        out << "MOVE $sp, $fp" << std::endl; 

        if(funcName != "main"){
            out << "JR $31" << std::endl;
        }
        out << ".end " << funcName << std::endl;
    }
    virtual void printC (std::ostream &out) const override{
        out << type << " " << funcName << "(";
        if(varList != NULL){
            varList->printC(out);
        }
        out << ") {" << std::endl;
        branch->printC(out);//return 1
        out << "}" << std::endl;

    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "def " << funcName << "(";
        if(varList != NULL){
            varList->printPy(out, myPy);
        }
        out << "):" << std::endl;
        myPy.indent++;
        for(int i = myPy.indent; i > 0; i--){
          out << "\t";
        }
        myPy.indent--;
        branch->printPy(out, myPy);//return 1
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
        if(varList != NULL){
            varList->printC(out);
        }
        out << ");" << std::endl;
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "def " << funcName << "(";
        if(varList != NULL){
            varList->printPy(out, myPy);
        }
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

class GlobalList
    : public Base
{
protected:
    BasePtr func;
    BasePtr nextFunc;

public:
    GlobalList(BasePtr _func, BasePtr _nextFunc)
        : func(_func), nextFunc(_nextFunc)
    {}

    ~GlobalList(){
        if(nextFunc!=NULL){
            delete nextFunc;
        }
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        if(func != NULL){
          if(nextFunc != NULL){
              nextFunc->printC(out);
              out << std::endl;
          }
          func->printC(out);
        }
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
      if(func != NULL){
        if(nextFunc != NULL){
            nextFunc->printPy(out, myPy);
            out << std::endl;
        }
        func->printPy(out, myPy);
      }
    }
};

class BranchList
    : public Base
{
protected:
    BasePtr statement;
    BasePtr branch;

public:
    BranchList(BasePtr _statement, BasePtr _branch)
        : statement(_statement), branch(_branch)
    {}

    ~BranchList(){
        if(branch!=NULL){
            delete branch;
        }
    }

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        if(statement != NULL){
          if(branch != NULL){
              branch->printC(out);
              out << std::endl;
          }
          statement->printC(out);
        }
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
      if(statement != NULL){
        if(branch != NULL){
            branch->printPy(out, myPy);
            out << std::endl;
        }
        statement->printPy(out, myPy);
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
