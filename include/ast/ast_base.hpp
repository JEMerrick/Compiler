#ifndef H_BASE
#define H_BASE

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include <memory>

int count = 0;
std::vector <int> regFlag {8, 9, 10, 11, 12, 13, 14, 15, 16,
                          17, 18, 19 20, 21, 22, 23, 24, 25}; // 0 is free

class Base;

typedef const Base *BasePtr;

class Base {

    public:
        std::map <std::string, int> localVars;


        virtual ~Base(){}

        virtual void printMIPS (std::string reg, std::ostream &out) const = 0;
        virtual void printC (std::ostream &out) const = 0;
        virtual void printPy (std::ostream &out) const = 0;


        std::string makelabel(){
          return "L_" + std::to_string(count++);
        }
};

int findreg(){
  int i = 0;
  while(regFlag[i] != 0){
    i++;
  }
  regFlag[i] = 1;
  return i;
}

#endif
