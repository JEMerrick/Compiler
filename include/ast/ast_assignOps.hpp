#ifndef H_ASSIGNOPS
#define H_ASSIGNOPS

#include <iostream>
#include <string>
#include "ast_base.hpp"

class AssignOp
    : public Base
{
protected:
    Baseptr variable;

public:
    AssignOp(BasePtr _variable)
        : variable(_variable)
    {}

    virtual ~AssignOp()
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out, Py &myPy) const = 0;
};

class AssignEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    AssignEqualOperator(BasePtr _variable, BasePtr _val)
        : AssignOp(_variable), val(_val)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        if(!(help.globalexists(variable) && help.localexists(variable))){
            throw "Variable not declared.";
        }
        out << "ADDU " << reg << ", %0, " << r1 << std::endl;
        if(help.localexists(variable)){
            out << "SW " << reg << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            std::string r2 = "$" + std::to_string(help.findreg());
            val->printMIPS(r2, out, help);
            help.regFlag[std::stoi(r2.substr(1))] = 0;
        }
        else{
            throw "Variable not declared.";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << " = ";
        val->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << variable;
        out << " = ";
        val->printPy(out, myPy);
    }
};

class AddEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    AddEqualOperator(BasePtr _variable, BasePtr _val)
        : AssignOp(_variable), val(_val)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(help.findreg());
        val->printMIPS(r1, out, help);
        if(help.localexists(variable)){
            out << "SW " << reg << ", " << help.findlocal(variable) << "($fp)" << std::endl;
        }
        else if(help.globalexists(variable)){
            std::string r2 = "$" + std::to_string(help.findreg());
            val->printMIPS(r2, out, help);
            help.regFlag[std::stoi(r2.substr(1))] = 0;
        }
        else{
            throw "Variable not declared.";
        }
        help.regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << " += ";
        val->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << variable;
        out << " += ";
        val->printPy(out, myPy);
    }
};

class SubEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    SubEqualOperator(BasePtr _variable, BasePtr _val)
        : AssignOp(_variable), val(_val)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << variable;
        out << " -= ";
        val->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << variable;
        out << " -= ";
        val->printPy(out, myPy);
    }
};

class PreIncrement
    : public AssignOp
{

public:
    PreIncrement(BasePtr _variable)
        : AssignOp(_variable)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << "++" << variable;
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "++" << variable;
    }
};

class PreDecrement
    : public AssignOp
{

public:
    PreDecrement(BasePtr _variable)
        : AssignOp(_variable)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << "--" << variable;
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "--" << variable;
    }
};

class PostIncrement
    : public AssignOp
{

public:
    PostIncrement(BasePtr _variable)
        : AssignOp(_variable)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << variable << "++";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << variable << "++";
    }
};

class PostDecrement
    : public AssignOp
{

public:
    PostDecrement(BasePtr _variable)
        : AssignOp(_variable)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << variable << "--";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << variable << "--";
    }
};

#endif
