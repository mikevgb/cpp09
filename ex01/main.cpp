#include "RPN.hpp"
//#include <iostream>
//#include <stack>

int main(int argc, char **argv)
{
    if (argc > 1 && argc < 3)
        RPN calcu(argv);
    else
        std::cerr << "Wrong number of arguments, ex: \" 1 1 + 1 1 + + \" " << std::endl;
    return 0;
}