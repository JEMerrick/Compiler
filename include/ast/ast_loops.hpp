#ifndef H_LOOPS
#define H_LOOPS

#include <iostream>

#include "ast_base.hpp"


class For
    : public Base
{
    
protected:
    BasePtr condition; 
    BasePtr branch;
    BasePtr initial;
    
public:
    For(BasePtr _condition, BasePtr _branch, BasePtr _initial)
        : condition (_condition), branch (_branch), initial(_initial)
    {}
    
    ~For(){
        delete condition;
        delete initial;
        delete branch;
    }
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class While
    : public Base
{
    
protected:
    BasePtr condition; 
    BasePtr branch;
    
public:
    While(BasePtr _condition, BasePtr _branch)
        : condition (_condition), branch (_branch)
    {}
    
    ~While(){
        delete condition;
        delete branch;    
    }
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class Do
    : public Base
{

protected:
    BasePtr condition; 
    BasePtr branch;
    
public:
    Do(BasePtr _condition, BasePtr _branch)
        : condition (_condition), branch (_branch)
    {}
    
    ~Do(){
        delete condition;
        delete branch;
    }
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class Break
    : public Base
{

public:
    Break()
    {}
    
    ~Break{}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class Continue
    : public Base
{

public:
    Continue()
    {}
    
    Continue{}~
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

#endif
