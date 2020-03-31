#ifndef H_PRIMATIVES
#define H_PRIMATIVES

#include <string>
#include <iostream>

#include "ast_base.hpp"

class Variable
    : public Base
{
protected:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        if(help.globalexists(id)){
            std::string r1 = "$" + std::to_string(help.findreg());
            out << "LUI " << r1 << ", %hi(" << id << ")" << std::endl;
            out << "ADDI " << r1 << ", " << r1 << ", %lo(" << id << ")" << std::endl;
            out << "LW " << reg << ", 0(" << r1 << ")" << std::endl;
            help.regFlag[std::stoi(r1.substr(1))] = 0;
        }
        else if(help.localexists(id)){
            out << "LW " << reg << ", " << 4+help.findlocal(id) << "($fp)" << std::endl;
        }
        else{
            throw "variable not declared.";
        }
    }
    virtual void printC (std::ostream &out) const{
        out << id;
    }
    virtual void printPy (std::ostream &out, Py &myPy) const{
        out << id;
    }


};

class Number
    : public Base
{
protected:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        out << "ADDI " << reg << ", $0, " << value << std::endl;
    }
    virtual void printC (std::ostream &out) const{
        out << value;
    }
    virtual void printPy (std::ostream &out, Py &myPy) const{
        out << value;
    }

};

class Array
    : public Base
{
protected:
    std::string var;
    BasePtr expr;
public:
    Array(std::string _var, BasePtr _expr)
        : var(_var), expr(_expr)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
        if(help.localexists(id)){
            //out << "LW "<< reg<<", "<<help.findarrayelement(id, element)<<"($fp)"<<std::endl;
        }else if(help.globalexists(id)){

            out << "LUI " << r1 << ", %hi(" << id << ")" << std::endl;
            out << "ADDI " << r1 << ", " << r1 << ", %lo(" << id << ")" << std::endl;
            out << "LW " << reg << ", ";
            expr->printMIPS(reg, out, help); // times 4
            out << "(" << r1 << ")" << std::endl;
            help.regFlag[std::stoi(r1.substr(1))] = 0;
        }else{
            throw "Variable not declared. ";
        }
    }
    virtual void printC (std::ostream &out) const{
       // out << name << "[" << index << "]";
    }
    virtual void printPy (std::ostream &out, Py &myPy) const{
        out << var << "[";
        expr->printPy(out, myPy);
        out << "]";
    }

};

class Struct
    : public Base
{
protected:
    std::string var;
    BasePtr inside;

public:
    Struct (std::string _var, BasePtr _inside)
    : var(_var), inside(_inside)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "class " << var << "(object):\n";
        myPy.indent++;
        for(int i = 0; i < myPy.globalv.size(); i++){
            for(int j = myPy.indent; j > 0; j--){
                out << "\t";
            }
            out << "global " << myPy.globalv[i] << std::endl;
        }
        for(int j = myPy.indent; j > 0; j--){
                out << "\t";
        }
        out << "__slots__ = [";
        inside->printPy(out, myPy);
        out << "]\n";
        myPy.indent--;
    }

};

class StructVar
    : public Base
{
protected:
    std::string type;
    std::string var;

public:
    StructVar(std::string _type, std::string _var)
    : type(_type), var(_var)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
     virtual void printPy (std::ostream &out, Py &myPy) const override{
         out << var;
    }
};

class StructVarList
    : public Base
{
protected:
    BasePtr var;
    BasePtr nextVar;

public:
    StructVarList(BasePtr _var, BasePtr _nextVar)
    : var(_var), nextVar(_nextVar)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const{
    }
    virtual void printC (std::ostream &out) const{
    }
     virtual void printPy (std::ostream &out, Py &myPy) const override{
         if(nextVar != NULL){
             nextVar->printPy(out, myPy);
             out << ", ";
         }
         var->printPy(out, myPy);
    }
};

#endif
