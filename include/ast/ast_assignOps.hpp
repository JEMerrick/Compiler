#ifndef H_ASSIGNOPS
#define H_ASSIGNOPS

class AssignOp
    : public Base
{
private:
    BasePtr left;
    BasePtr right;
protected:
    AssignOp(BasePtr _left, BasePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~AssignOp()
    {
        delete left;
        delete right;
    }

    virtual void printMIPS (std::ostream &out) const{}
    virtual void printC (std::ostream &out) const{}
    virtual void printPy (std::ostream &out) const{}
};

class AssignEqualOperator
    : public AssignOp
{

public:
    AssignEqualOperator(BasePtr _left, BasePtr _right)
        : AssignOp(_left, _right)
    {}
    
    virtual void printMIPS (std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
    }
    virtual void printPy (std::ostream &out) const override{
    }
};


//classes for +=, -=, ++ post/pre, -- post/pre here

#endif
