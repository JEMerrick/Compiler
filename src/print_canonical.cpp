#include "ast.hpp"
#include <iostream>
#include <fstream>

extern "C" FILE *yyin;

int main()
{
    yyin = fopen(argv[2], "r");
    const Base* ast = parseAST();

    Py myPython;
    ast -> printPy(std::cout, myPython);
    std::cout << std::endl;

    MIPZ myMIPS;
    ast->printMIPS("Hi", std::cout, myMIPS);
    std::cout<<std::endl;

    return 0;

}
