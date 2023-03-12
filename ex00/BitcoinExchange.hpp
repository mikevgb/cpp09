#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>

class BitcoinExchange
{
    private:
    std::map<std::string, std::string> _csvData;
    std::map<std::string, std::string> _inputData;
    std::string _fileInput;

    public:
    BitcoinExchange();
    BitcoinExchange &operator=(BitcoinExchange const &in);
    BitcoinExchange(BitcoinExchange &copy);
    BitcoinExchange(std::string fileInput);
    ~BitcoinExchange();
    void readDatabaseCSV();
    void readFileInput();
    bool parseDate(std::string date);
    void printMaps();
    void multiValues();
};

#endif