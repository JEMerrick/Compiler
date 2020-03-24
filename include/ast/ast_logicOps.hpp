#ifndef H_LOGICOPS
#define H_LOGICOPS

#include <iostream>

#include "ast_base.hpp"

class LogicOp
    : public Base
{
protected:
    BasePtr left;
    BasePtr right;

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

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
    virtual void printC (std::ostream &out) const = 0;
    virtual void printPy (std::ostream &out, Py &myPy) const = 0;
};

class NotOperator
    : public Base
{
protected:
    BasePtr condition;
public:
    NotOperator(BasePtr _condition)
        : condition(_condition)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(findreg());
        condition->printMIPS(r1, out, help);
        std::string label = makelabl();

        out << "ADDI " << reg << ", $0, 1" << std::endl;
        out << "BEQ " << r1 << ", $0," << label << std::endl;
        out << "ADDI " << reg << ", $0, 0" << std::endl;
        out << label << ":" << std::endl;
        regFlag[std::stoi(r1.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        out << "!";
        condition->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        out << "!";
        condition->printPy(out);
    }
};

class AndOperator
    : public LogicOp
{

public:
    AndOperator(BasePtr _left, BasePtr _right)
        : LogicOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(findreg());
        left->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(findreg());
        right->printMIPS(r2, out, help);
        std::string label1 = makelabl();
        std::string label2 = makelabl();

        out << "ADDI " << reg << ", $0, 0" << std::endl;
        out << "BEQ " << r1 << ", $0," << label1 << std::endl;
        out << "BEQ " << r2 << ", $0," << label2 << std::endl;
        out << "J " << label2 << std::endl;
        out << label1 << ":" << std::endl;
        out << "ADDI " << reg << ", $0, 0" << std::endl;
        out << label2 << ":" << std::endl;

        regFlag[std::stoi(r1.substr(1))] = 0;
        regFlag[std::stoi(r2.substr(1))] = 0;
      }
    virtual void printC (std::ostream &out) const override{
        left->printC(out);
        out << " && ";
        right->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        left->printPy(out);
        out << " && ";
        right->printPy(out);
    }
};

class OrOperator
    : public LogicOp
{

public:
    OrOperator(BasePtr _left, BasePtr _right)
        : LogicOp(_left, _right)
    {}

    virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const override{
        std::string r1 = "$" + std::to_string(findreg());
        left->printMIPS(r1, out, help);
        std::string r2 = "$" + std::to_string(findreg());
        right->printMIPS(r2, out, help);
        std::string label1 = makelabl();
        std::string label2 = makelabl();

        out << "ADDI " << reg << ", $0, 0" << std::endl;
        out << "BNE " << r1 << ", $0," << label1 << std::endl;
        out << "BNE " << r2 << ", $0," << label2 << std::endl;
        out << "J " << label2 << std::endl;
        out << label1 << ":" << std::endl;
        out << "ADDI " << reg << ", $0, 1" << std::endl;
        out << label2 << ":" << std::endl;

        regFlag[std::stoi(r1.substr(1))] = 0;
        regFlag[std::stoi(r2.substr(1))] = 0;
    }
    virtual void printC (std::ostream &out) const override{
        left->printC(out);
        out << " || ";
        right->printC(out);
    }
    virtual void printPy (std::ostream &out, Py &myPy) const override{
        left->printPy(out);
        out << " || ";
        right->printPy(out);
    }
};

#endif
