#ifndef H_FUNC
#define H_FUNC

#include <cmath>

class Function
    : public Base
{
private:
    BasePtr arg;
protected:
    Function(BasePtr _arg)
        : arg(_arg)
    {}
public:
    virtual ~Function()
    {
        delete arg;
    }

    virtual const char * getFunction() const =0;

    BasePtr getArg() const
    { return arg; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<getFunction()<<"( ";
        arg->print(dst);
        dst<<" )";
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
    }
};

class LogFunction
    : public Function
{
public:
    LogFunction(BasePtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "log"; }
    virtual double evaluate (
        const std::map<std::string,double> &bindings
    ) const override
    {
        double myNum = getArg() -> evaluate(bindings);
        return log(myNum);
    }
};

class ExpFunction
    : public Function
{
public:
    ExpFunction(BasePtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "exp"; }
    virtual double evaluate (
        const std::map<std::string,double> &bindings
    ) const override
    {
        double myNum = getArg() -> evaluate(bindings);
        return exp(myNum);
    }
};

class SqrtFunction
    : public Function
{
public:
    SqrtFunction(BasePtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "sqrt"; }
    virtual double evaluate (
        const std::map<std::string,double> &bindings
    ) const override
    {
        double myNum = getArg() -> evaluate(bindings);
        return sqrt(myNum);
    }
};


#endif
