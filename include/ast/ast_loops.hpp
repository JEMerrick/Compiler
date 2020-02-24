#ifndef H_LOOPS
#define H_LOOPS

#include <iostream>

#include "ast_base.hpp"

class Loop
    : public Base
{
protected:
    BasePtr left;
    BasePtr right;

    Loop(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Loop()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class For
    : public Loop
{

public:
    For(BasePtr _left, BasePtr _right)
        : Loop(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class While
    : public Loop
{

public:
    While(BasePtr _left, BasePtr _right)
        : Loop(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class Do
    : public Loop
{

public:
    Do(BasePtr _left, BasePtr _right)
        : Loop(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class Break
    : public Loop
{

public:
    Break(BasePtr _left, BasePtr _right)
        : Loop(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class Continue
    : public Loop
{

public:
    Continue(BasePtr _left, BasePtr _right)
        : Loop(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

#endif
