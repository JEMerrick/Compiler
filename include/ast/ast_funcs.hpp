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

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      out << type << " " << funcName << "(";
      varList->printC(out);
      out << ") {" << std::endl;
      branch->printC(out);//return 1
      out << "}" << std::endl;

    }
    virtual void printPy (std::ostream &out) const override{
      out << "def " << funcName << "(";
      varList->printPy(out);
      out << "):" << std::endl;
      indent++;
      for(int i = indent; i > 0; i--){
        out << "\t";
      }
      branch->printPy(out);//return 1
      indent--;
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

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      out << type << " " << funcName << "(";
      varList->printC(out);
      out << ");" << std::endl;
    }
    virtual void printPy (std::ostream &out) const override{
      out << "def " << funcName << "(";
      varList->printPy(out);
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
    Arg(std::string _type, std::string _id, BasePtr _nextArg):
        type(_type), id(_id), nextArg(_nextArg){}

~Arg(){
    if(nextArg!=NULL){
        delete nextArg;
    }
}

virtual void printC(std::ostream &out) const override{
    if(nextArg != NULL){
        nextArg->printC(out);
        out << ", ";
    }
    out << type << " " << id;
}

virtual void printPy(std::ostream &out) const override{
    if(nextArg!=NULL){
        nextArg->printPy(out);
        out << ", ";
    }
    out << id;
}
virtual void printMIPS(std::string reg, std::ostream &out) const override{

}
};

#endif
