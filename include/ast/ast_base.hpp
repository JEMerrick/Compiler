#ifndef H_BASE
#define H_BASE

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include <memory>

class Base;

typedef const Base *BasePtr;

class Base {
    
    public:
        std::map <std::string, int> localVars;
        std::vector <int> regFlag;
        
        virtual ~Base(){};
        
        virtual void printMIPS (std::ostream &out) const{};
        virtual void printC (std::ostream &out) const{};
        virtual void printPy (std::ostream &out) const{};
    
    
};



#endif
