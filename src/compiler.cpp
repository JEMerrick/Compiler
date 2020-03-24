#include <iostream>
#include "ast.hpp"

int main()
{
    const Base* ast = parseAST();
    
    ast->printMIPS(std::cout);
    std::cout<<std::endl;

    return 0;
}

