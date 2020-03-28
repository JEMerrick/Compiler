#include <iostream>
#include <fstream>
#include "ast.hpp"

int main(int argc, char *argv[]){
    const Base* ast = parseAST();
    ast -> printC(std::cout);
    std::cout << std::endl;
    std::fstream fs;
    fs.open(argv[2]);

    if(static_cast<std::string>(argv[1]) == "--translate"){
        ofstream outfile;
        outfile.open(argv[4]);
        Py myPython;
        ast->printPy(outfile, myPython);
        std::cout << std::endl;
        outfile.close();
    }

    else if (static_cast<std::string>(argv[1]) == "-S"){
        MIPZ myMIPS;
        ast->printMIPS("Hi", std::cout, myMIPS);
        std::cout<<std::endl;
    }

    return 0;
}
