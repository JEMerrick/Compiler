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
        std::vector <int> regFlag; // 0 is free

        virtual ~Base(){}

        virtual void printMIPS (std::string reg, std::ostream &out) const = 0;
        virtual void printC (std::ostream &out) const = 0;
        virtual void printPy (std::ostream &out) const = 0;

        // void loopy(){
        //   int i = 0;
        //   while(regFlag[i] != 0){
        //     i++;
        //   }
        //   regFlag[i] = 1;
        //   return i;
        // }


};



#endif
