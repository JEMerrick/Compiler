#ifndef H_LOGICOPS
#define H_LOGICOPS

class LogicOp
    : public Base
{
private:
    BasePtr left;
    BasePtr right;
protected:
    LogicOp(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~LogicOp()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class AndOperator
    : public LogicOp
{

public:
    AndOperator(BasePtr _left, BasePtr _right)
        : LogicOp(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

class OrOperator
    : public LogicOp
{

public:
    OrOperator(BasePtr _left, BasePtr _right)
        : LogicOp(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
        
    }
};

#endif
