#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    if (argc > 3)
    {
        std::cerr << "Error: Too many arguments." << std::endl;
        return 1;
    }
}