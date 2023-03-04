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
    std::map<std::string, int> _csvData;
    std::map<std::string, int> _inputData;
    void printError(std::string message)
    {
        std::cerr << message << std::endl;
        exit(1);
    };

    public:
    //!! implementation in hpp file is forbidden!!!
    BitcoinExchange(std::string fileInput) 
    {
        readDatabaseCSV();
    };
    ~BitcoinExchange() {};
    //!! canonical
    void readDatabaseCSV()
    {
        std::ifstream file("data.csv");
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                std::stringstream ss(line);
                std::string date, value;
                std::getline(ss, date, ',');
                std::getline(ss, value, ',');
                int intval = std::stoi(value);
                parseDate(date);
                _csvData[date] = intval;
            }
            file.close();
        }
        else
            printError("Error: cant open data.csv");
    };
    void readFileInput(std::string fileName)
    {
        std::ifstream file(fileName);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                std::stringstream ss(line);
                std::string date, value;
                std::getline(ss, date, '|');
                std::getline(ss, value, '|');
                int intval = std::stoi(value);
                parseDate(date);
                _inputData[date] = intval;
            }
            file.close();
        }
        else
            printError("Error: cant open input file");
    };
    void parseDate(std::string date)
    {
        int year = std::stoi(date.substr(0,4));
        int month = std::stoi(date.substr(5,2));
        int day = std::stoi(date.substr(8,2));
        if (year < 2009 || year > 2022)
            printError("Error: year out of range.");
        if (month < 1 || month > 12)
           printError("Error: month out of range.");
        if (day < 1 || day > 31)
            printError("Error: day out of range");
        if (month == 2 && day > 29)
            printError("Error: day out of range");        
    };
};

#endif