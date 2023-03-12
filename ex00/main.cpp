#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: missing arguments." << std::endl;
        return 1;
    }
    else if (argc > 2)
    {
        std::cerr << "Error: Too many arguments." << std::endl;
        return 1;
    }
    else
        BitcoinExchange btx(argv[1]);

    return 0;
}