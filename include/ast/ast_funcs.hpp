#ifndef H_FUNCS
#define H_FUNCS

class Functions
    : public Base
{
private:
    BasePtr left;
    BasePtr right;
protected:
    Functions(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Functions()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class DecFunc
    : public Functions
{

public:
    DecFunc(BasePtr _left, BasePtr _right)
        : Functions(_left, _right)
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
    DefFunc(BasePtr _left, BasePtr _right)
        : Functions(_left, _right)
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
    CallFunc(BasePtr _left, BasePtr _right)
        : Functions(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};
