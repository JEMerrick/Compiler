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

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        expr->printMIPS(reg, out);
    }
    virtual void printC (std::ostream &out) const override{
        expr->printC(out);
        out << ";";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
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

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << "return ";
        expr->printC(out);
        out << ";";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
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
    BasePtr list;
public:
    Decl_stmt(std::string _type, BasePtr _list)
        : type(_type), list(_list)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << type << " ";
        list->printC(out);
        out << ";";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        for(int i = indent; i > 0; i--){
            out << "\t";
        }
        list->printPy(out);
    }
};

class Declare
    : public Base
{
protected:
    std::string id;
    BasePtr expr;
public:
    Declare(std::string _id, BasePtr _expr)
        : id(_id), expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
    }
    virtual void printC (std::ostream &out) const override{
        out << id << "=";
        expr->printC(out);
        out << ";";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        for(int i = indent; i > 0; i--){
            out << "\t";
        }
        out << id << "=";
        expr->printPy(out);
    }
};
