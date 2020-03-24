#include "ast.hpp"
#include <iostream>

int main()
{
    const Base* ast = parseAST();

    ast -> printC(std::cout);
    std::cout << std::endl;

    Py myPython;
    ast -> printPy(std::cout, myPython);
    std::cout << std::endl;

    MIPZ myMIPS;
    ast->printMIPS("Hi", std::cout, myMIPS);
    std::cout<<std::endl;
    
    return 0;
}
