#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
        RPN calcu(argv);
    else
        std::cerr << "Wrong number of arguments, ex: \" 1 1 + 1 1 + + \" " << std::endl;
    return 0;
}

// int main(int argc, char **argv)
// {
//     if (argc > 1 && argc < 3)
//         RPN calcu(argv);
//     else
//         std::cerr << "Wrong number of arguments, ex: \" 1 1 + 1 1 + + \" " << std::endl;
//     return 0;
// }