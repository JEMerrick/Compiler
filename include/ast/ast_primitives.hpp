#ifndef H_PRIMATIVES
#define H_PRIMATIVES

#include <string>
#include <iostream>

class Variable
    : public Base
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    virtual void printMIPS (std::ostream &out) const{
        
    }
    virtual void printC (std::ostream &out) const{
        out << id;
    }
    virtual void printPy (std::ostream &out) const{
        
    }


};

class Number
    : public Base
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    virtual void printMIPS (std::ostream &out) const{
        
    }
    virtual void printC (std::ostream &out) const{
        out << value;
    }
    virtual void printPy (std::ostream &out) const{
        
    }

};


#endif
