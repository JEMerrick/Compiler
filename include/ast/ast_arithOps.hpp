#ifndef H_ARITHOPS
#define H_ARITHOPS

#include <string>
#include <iostream>
#include <math.h>

class ArithOp
    : public Base
{
private:
    BasePtr left;
    BasePtr right;
protected:
    ArithOp(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~ArithOp()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class AddOperator
    : public ArithOp
{

public:
    AddOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
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
    : public ArithOp
{
public:
    SubOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
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
    : public ArithOp
{

public:
    MulOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << "( " << left -> printC(out) << " * " << right -> printC(out) << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        
};

class DivOperator
    : public ArithOp
{

public:
    DivOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "( " << left -> printC(out) << " / " << right -> printC(out) << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        
};

class ModOperator
    : public ArithOp
{

public:
    ModOperator(BasePtr _left, BasePtr _right)
        : ArithOp(_left, _right)
    {}

    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "( " << left -> printC(out) << " % " << right -> printC(out) << " )";
    }
    virtual void printPy (std::ostream &out) const override{
        
};


#endif
