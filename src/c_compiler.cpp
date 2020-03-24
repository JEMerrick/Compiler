#include <iostream>
#include "ast.hpp"

int main(int argc, char *argv[]){
    const Base* ast = parseAST();
    ast -> printC(std::cout);
    std::cout << std::endl;

    if(argv[1] == "--translate"){
        Py myPython;
        ast->printPy(std::cout, myPython);
        std::cout << std::endl;
    }

    else if (argv[1] == "-S"){
        MIPZ myMIPS;
        ast->printMIPS("Hi", std::cout, myMIPS);
        std::cout<<std::endl;
    }

    return 0;
}
