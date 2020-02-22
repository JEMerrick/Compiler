#ifndef H_UNARY
#define H_UNARY

#include <string>
#include <iostream>


class Unary
    : public Base
{
private:
    BasePtr expr;
protected:
    Unary(const BasePtr _expr)
        : expr(_expr)
    {}
public:
    virtual ~Unary()
    {
        delete expr;
    }

    virtual const char *getOpcode() const =0;

    BasePtr getExpr() const
    { return expr; }

    virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << getOpcode();
        dst << " ";
        expr->print(dst);
        dst << " )";
    }
};

class NegOperator
    : public Unary
{
public:
    NegOperator(const BasePtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

    virtual double evaluate(
        const std::map<std::string, double> &bindings
    ) const override
    {
        double myNum = getExpr()->evaluate(bindings);
        return -myNum;
    }
};

#endif
