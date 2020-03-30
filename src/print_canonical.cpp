#include "ast.hpp"
#include <iostream>
#include <fstream>

int main()
{
    const Base* ast = parseAST();

    MIPZ myMIPS;
    std::cout << "1" << '\n';
    ast->printMIPS("Hi", std::cout, myMIPS);
    std::cout << "2" << '\n';
    std::cout<<std::endl;

    return 0;

}
