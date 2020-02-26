#include "ast.hpp"

int main()
{
    const Base* ast = parseAST();

    ast->printC(std::cout);
    std::cout<<std::endl;

    return 0;
}
