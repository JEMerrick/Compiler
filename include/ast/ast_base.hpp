#ifndef H_BASE
#define H_BASE

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include <memory>

class Base;
class MIPZ;
class Py;

typedef const Base *BasePtr;

class Base {

    public:
        


        virtual ~Base(){}

        virtual void printMIPS (std::string reg, std::ostream &out, MIPZ &help) const = 0;
        virtual void printC (std::ostream &out) const = 0;
        virtual void printPy (std::ostream &out, Py &myPy) const = 0;
        
        


};


class MIPZ {
    public:
        MIPS(){
            //TODO:initial constructor
        }
        
        MIPS(MIPZ &help){
            //TODO:copy constructor
        }
        
        std::map <std::string, int> localVars;
    
        int abcdef = 0;
        std::vector <int> regFlag {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // can't use $0-$7, $8-$25 free

        int findreg(){
            int i = 8;
            while(regFlag[i] != 0){
            i++;
            }
            regFlag[i] = 1;
            return i;
        }

        std::string makelabl(){
            return "L_" + std::to_string(abcdef++);
        }
    
    
    
    
};


class Py {
    public:
    Py(){
        //TODO:constructor
    }
    Py(Py prevPy){
        //TODO:copy constructor
    }
    
    int indent = 0;
    //TODO: any functions needed for indent?
};

#endif
