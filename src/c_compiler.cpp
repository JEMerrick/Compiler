#include <iostream>
#include <fstream>
#include "ast.hpp"
extern "C" int yydebug;

extern "C" FILE *yyin;

int main(int argc, char *argv[]){
    yydebug = 1;
    //std::fstream fs;
    //fs.open(argv[2]);
    yyin = fopen(argv[2], "r");
    const Base* ast = parseAST();

    std::cout << std::endl;
    freopen(argv[4], "w", stdout);


    if(static_cast<std::string>(argv[1]) == "--translate"){
        //ofstream outfile;
        //outfile.open(argv[4]);
        Py myPython;
        ast->printPy(std::cout, myPython);
        std::cout << std::endl;
        //outfile.close();
    }

    else if (static_cast<std::string>(argv[1]) == "-S"){
        MIPZ myMIPS;
        ast->printMIPS("Hi", std::cout, myMIPS);
        std::cout<<std::endl;
    }

    return 0;
}
