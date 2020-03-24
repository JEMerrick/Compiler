#include "ast.hpp"
#include <iostrem>

int main()
{
    const Base* ast = parseAST();
    Py myPython;
    
    ast -> printC(std::cout);
    std::cout << std::endl;
    
    ast -> printPy(std::cout);
    std::cout << std::endl;
    return 0;
}
