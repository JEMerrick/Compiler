#ifndef H_PRIMATIVES
#define H_PRIMATIVES

#include <string>
#include <iostream>

#include "ast_base.hpp"

class Variable
    : public Base
{
protected:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        if(help.globalexists(id)){
            std::string r1 = "$" + std::to_string(help.findreg());
            out << "LUI " << r1 << ", %hi(" << id << ")" << std::endl;
            out << "ADDI " << r1 << ", " << r1 << ", %lo(" << id << ")" << std::endl;
            out << "LW " << reg << ", 0(" << r1 << ")" << std::endl;
            help.regFlag[std::stoi(r1.substr(1))] = 0;
        }
        else if(help.localexists(id)){
            out << "LW " << reg << ", " << help.findlocal(id) << "($fp)" << std::endl;
        }
        else{
            throw "variable not declared.";
        }
    }
    virtual void printC (std::ostream &out) const{
        out << id;
    }
    virtual void printPy (std::ostream &out, Py &myPy) const{
        out << id;
    }


};

class Number
    : public Base
{
protected:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        out << "ADDI " << reg << ", $0, " << value << std::endl;
    }
    virtual void printC (std::ostream &out) const{
        out << value;
    }
    virtual void printPy (std::ostream &out, Py &myPy) const{
        out << value;
    }

};

class Array
    : public Base
{
protected:
    std::string var;
    BasePtr expr;
public:
    Array(std::string _var, BasePtr _expr)
        : var(_var), expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{

    }
    virtual void printC (std::ostream &out) const{
       // out << name << "[" << index << "]";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const{
        out << var << "[";
        expr->printPy(out, myPy);
        out << "]";
    }

};


#endif
