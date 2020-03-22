//TODO: BREAK, CONTINUE, RETURN, EXPGRESSION STMT, DECLARE STMT,
#include <string>
#include <iostream>

#include "ast_base.hpp"

class Expr_stmt
    : public Base
{
protected:
    BasePtr expr;
public:
    Expr_stmt(BasePtr _expr)
        : expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
        expr->printMIPS(reg, out);
    }
    virtual void printC (std::ostream &out) const override{
        expr->printC(out);
        out << ";";
    }
    virtual void printPy (std::ostream &out) const override{
        for(int i = indent; i > 0; i--){
            out << "\t";
        }
        expr->printPy(out);
    }
};

class Return_stmt
    : public Base
{
protected:
    BasePtr expr;
public:
    Return_stmt(BasePtr _expr)
        : expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "return ";
        expr->printC(out);
        out << ";";
    }
    virtual void printPy (std::ostream &out) const override{
        for(int i = indent; i > 0; i--){
            out << "\t";
        }
        out << "return ";
        expr->printPy(out);
    }
};

class Decl_stmt
    : public Base
{
protected:
    std::string type;
    BasePtr expr;
public:
    Decl_stmt(type _type, BasePtr _expr)
        : type(_type), expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << type << " ";
        expr->printC(out);
        out << ";";
    }
    virtual void printPy (std::ostream &out) const override{
        for(int i = indent; i > 0; i--){
            out << "\t";
        }
        expr->printPy(out);
    }
};

class Declare
    : public Base
{
protected:
    std::string type;
    BasePtr expr;
public:
    Declare(type _type, BasePtr _expr)
        : type(_type), expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << type << "=";
        expr->printC(out);
        out << ";";
    }
    virtual void printPy (std::ostream &out) const override{
        for(int i = indent; i > 0; i--){
            out << "\t";
        }
        out << type << "=";
        expr->printPy(out);
    }
};
