#include <iostream>
#include "ast.hpp"

int main()
{
    const Base* ast = parseAST();
    MIPZ myMIPS;
    ast->printMIPS("Hi", std::cout, myMIPS);
    std::cout<<std::endl;

    return 0;
}
