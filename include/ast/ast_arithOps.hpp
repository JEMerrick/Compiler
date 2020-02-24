#ifndef H_OP
#define H_OP

#include <string>
#include <iostream>
#include <math.h>

class Operator
    : public Base
{
private:
    BasePtr left;
    BasePtr right;
protected:
    Operator(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class AddOperator
    : public Operator
{

public:
    AddOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "( " << left -> printC(out) << " + " << right -> printC(out) << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
    SubOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "( " << left -> printC(out) << " - " << right -> printC(out) << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};


class MulOperator
    : public Operator
{

public:
    MulOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << "( " << left -> printC(out) << " * " << right -> printC(out) << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        
};

class DivOperator
    : public Operator
{

public:
    DivOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "( " << left -> printC(out) << " + " << right -> printC(out) << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        
};


#endif
