#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
        std::cerr << "Need at least one number" << std::endl;
    else
        PmergeMe PM(argc, argv);

    return 0;
}