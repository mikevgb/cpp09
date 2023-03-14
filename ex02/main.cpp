#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        /*
        std::string arg1;
        for (int i = 1; i < argc; i++)
        {
            
            arg1.append(argv[i]);
            arg1.append(" ");
            
        }
        */
       
        //std::cout << "Input " << argv << std::endl;
        PmergeMe shorty(argc, argv);
        //shorty.printVectorOfPairs();
        // shorty.printInput();
        // shorty.printVector();
    }
    return 0;
}