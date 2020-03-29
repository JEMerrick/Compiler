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
        out << "addi " << reg << "$0, " << value;
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
    int index;
    std::string name;
public:
    Number(std::string _name, int _index)
        : name(_name), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        
    }
    virtual void printC (std::ostream &out) const{
        out << name << "[" << index << "]";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const{
        out << name << "[" << index << "]";
    }

};


#endif
