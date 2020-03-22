#ifndef H_FUNCS
#define H_FUNCS

#include <iostream>
#include <string>

#include "ast_base.hpp"

//TODO: FuncList - list of functions: vars: currentFunc, nextFunc.

class Functions
    : public Base
{
protected:
    std::string type;
    std::string funcName;
    BasePtr varList;
    BasePtr branch;
public:
    Functions(std::string _type, std::string _funcName, BasePtr _varList, BasePtr _branch)
        : type(_type), funcName(_funcName), varList(_varList), branch(_branch)
    {}

    virtual ~Functions(){
        delete varList;
        delete branch;
    }

    virtual void printMIPS (std::string reg, std::ostream &out) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out) const = 0;
};

class DecFunc
    : public Functions
{
protected:
    std::string type;
    std::string funcName;
    BasePtr varList;
    BasePtr branch;

public:
    DecFunc(std::string _type, std::string _funcName, BasePtr _varList, BasePtr _branch)
        : Functions(_type, _funcName, _varList, _branch)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
      out << type << " " << funcName << "(";
      varList->printC(out);
      out << ");" << std::endl;
    }
    virtual void printPy (std::ostream &out) const override{

    }
};

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
    : public Functions
{

public:
    CallFunc(std::string _type, std::string _funcName, BasePtr _varList, BasePtr _branch)
        : Functions(_type, _funcName, _varList, _branch)
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

class Arg: public Base
{
    protected:
        std::string type;
        std::string id;
        nodePtr nextArg;
    public:
        Arg(std::string _type, std::string _id, nodePtr _nextArg):
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
    virtual void printMips(std::string reg, std::ostream &out) const override{

    }
};

#endif
