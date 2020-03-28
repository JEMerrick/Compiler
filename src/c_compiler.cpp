#include <iostream>
#include <fstream>
#include "ast.hpp"

int main(int argc, char *argv[]){
    //std::fstream fs;
    //fs.open(argv[2]);
    freopen(argv[2], "r", stdin);
    const Base* ast = parseAST();
    std::cout << std::endl;

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
