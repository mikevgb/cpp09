#include "rpn.hpp"
//#include <iostream>
//#include <stack>

int main(int argc, char **argv)
{
    if (argc > 4)
    {
        std::cout << "Not enough arguments";
        return 0;
    }
    RPN calcu(argc, argv);

    return 0;
}