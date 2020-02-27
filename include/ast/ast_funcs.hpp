#ifndef H_FUNCS
#define H_FUNCS

#include <iostream>
#include <string>

#include "ast_base.hpp"

class Functions
    : public Base
{
protected:
    std::string type;
    std::string funcName;
    BasePtr varList;
public:
    Functions(std::string _type, std::string _funcName, BasePtr _varList)
        : type(_type), funcName(_funcName), varList(_varList)
    {}
    
    virtual ~Functions(){
        //delete type;
        //delete funcName;
        delete varList;
    }
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class DecFunc
    : public Functions
{

public:
    DecFunc(std::string _type, std::string _funcName, BasePtr _varList)
        : Functions(_type, _funcName, _varList)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class DefFunc
    : public Functions
{

public:
    DefFunc(std::string _type, std::string _funcName, BasePtr _varList)
        : Functions(_type, _funcName, _varList)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class CallFunc
    : public Functions
{

public:
    CallFunc(std::string _type, std::string _funcName, BasePtr _varList)
        : Functions(_type, _funcName, _varList)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

#endif
