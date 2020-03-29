#ifndef H_ASSIGNOPS
#define H_ASSIGNOPS

#include <iostream>
#include <string>
#include "ast_base.hpp"

class AssignOp
    : public Base
{
protected:
    std::string variable;

public:
    AssignOp(std::string _variable)
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
    AssignEqualOperator(std::string &_variable, BasePtr _val)
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

class AssignEqualArray
    : public AssignOp
{
protected:
    BasePtr val;
    int index;
public:
    AssignEqualArray(std::string &_variable, BasePtr _val, int _index)
        : AssignOp(_variable), val(_val), index(_index)
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
        out << "[" << index << "]=";
        val->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << variable;
        out << "[" << index << "]=";
        val->printPy(out, myPy);
    }
};

class AddEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    AddEqualOperator(std::string &_variable, BasePtr _val)
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

class AddEqualArray
    : public AssignOp
{
protected:
    BasePtr val;
    int index;
public:
    AddEqualArray(std::string &_variable, BasePtr _val, int _index)
        : AssignOp(_variable), val(_val), index(_index)
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
        out << "[" << index << "]+=";
        val->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << variable;
        out << "[" << index << "]+=";
        val->printPy(out, myPy);
    }
};

class SubEqualOperator
    : public AssignOp
{
protected:
    BasePtr val;
public:
    SubEqualOperator(std::string &_variable, BasePtr _val)
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

class SubEqualArray
    : public AssignOp
{
protected:
    BasePtr val;
    int index;
public:
    SubEqualArray(std::string &_variable, BasePtr _val, int _index)
        : AssignOp(_variable), val(_val), index(_index)
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
        out << "[" << index << "]-=";
        val->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << variable;
        out << "[" << index << "]-=";
        val->printPy(out, myPy);
    }
};

class PreIncrement
    : public AssignOp
{

public:
    PreIncrement(std::string &_variable)
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

class PreIncrementArray
    : public AssignOp
{

protected:
    int index;

public:
    PreIncrementArray(std::string &_variable, int _index)
        : AssignOp(_variable), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << "++" << variable << "[" << index << "]" << std::endl;

    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "++" << variable << "[" << index << "]" << std::endl;
    }
};

class PreDecrement
    : public AssignOp
{

public:
    PreDecrement(std::string &_variable)
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

class PreDecrementArray
    : public AssignOp
{

protected:
    int index;

public:
    PreDecrementArray(std::string &_variable, int _index)
        : AssignOp(_variable), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << "--" << variable << "[" << index << "]" << std::endl;

    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "--" << variable << "[" << index << "]" << std::endl;
    }
};

class PostIncrement
    : public AssignOp
{

public:
    PostIncrement(std::string &_variable)
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

class PostIncrementArray
    : public AssignOp
{

protected:
    int index;

public:
    PostIncrementArray(std::string &_variable, int _index)
        : AssignOp(_variable), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << variable << "[" << index << "]++" << std::endl;

    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << variable << "[" << index << "]++" << std::endl;
    }
};

class PostDecrement
    : public AssignOp
{

public:
    PostDecrement(std::string &_variable)
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

class PostDecrementArray
    : public AssignOp
{

protected:
    int index;

public:
    PostDecrementArray(std::string &_variable, int _index)
        : AssignOp(_variable), index(_index)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{

    }
    virtual void printC (std::ostream &out) const override{
        out << variable << "[" << index << "]--" << std::endl;

    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << variable << "[" << index << "]--" << std::endl;
    }
};

#endif
