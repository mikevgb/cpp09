#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string arg1;
        for (int i = 1; i < argc; i++)
        {
            
            arg1.append(argv[i]);
            arg1.append(" ");
            
        }
        std::cout << "Input " << arg1 << std::endl;
        PmergeMe shorty(arg1);
        shorty.printInput();
        shorty.printVector();
    }
    return 0;
}