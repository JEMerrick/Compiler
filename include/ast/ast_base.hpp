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
        std::map <std::string, int> localVars;
        int lcount = 0;
        std::vector <int> regFlag {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // can't use $0-$7, $8-$25 free
        int scopecount;
        int frameptr;

        MIPZ(){
            //TODO:initial constructor
            scopecount = 0;
            frameptr = 0;
            for(int i = 8; i < 26; i++){
              regFlag[i] = 0;
            }
        }

        MIPZ(MIPZ &help){
            //TODO:copy constructor
            localVars = help.localVars;
            scopecount = help.scopecount;
            frameptr = help.frameptr;
            for(int i = 8; i < 26; i++){
              regFlag[i] = help.regFlag[i];
            }
        }

        int findreg(){
            int i = 8;
            while(regFlag[i] != 0){
            i++;
            }
            regFlag[i] = 1;
            return i;
        }

        void newfunc(){
            localVars.clear();
            frameptr = 0;
        }

        std::string makelabl(){
            return "L_" + std::to_string(lcount++);
        }

        void newscope(){
            scopecount++;
        }

        int createlocal(std::string str){
          localVars[str] = frameptr;
          frameptr -= 4;
          return (frameptr + 4);
        }

        int findlocal(std::string str){
            return localVars[str];
        }

        bool localexists(std::string str){
            if(localVars[str] > 0){
                return true;
            }
            else{
                return false;
            }
        }



};


class Py {
    public:
    Py(){
        //TODO:constructor
    }
    Py(Py &prevPy){
        //TODO:copy constructor
    }

    int indent = 0;
    //TODO: any functions needed for indent?
};

#endif
