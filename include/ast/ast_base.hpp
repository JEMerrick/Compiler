#ifndef H_BASE
#define H_BASE

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include <memory>

int count = 0;
std::vector <int> regFlag {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // can't use $0-$7, $8-$25 free

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
  int i = 8;
  while(regFlag[i] != 0){
    i++;
  }
  regFlag[i] = 1;
  return i;
}

#endif
