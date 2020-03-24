#include "ast.hpp"
#include <iostream>

int main()
{
    const Base* ast = parseAST();
    Py myPython;
    
    ast -> printC(std::cout);
    std::cout << std::endl;
    
    ast -> printPy(std::cout, myPython);
    std::cout << std::endl;
    return 0;
}
