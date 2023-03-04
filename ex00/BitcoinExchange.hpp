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
    std::map<std::string, int> _result;
    BitcoinExchange() {};
    void printError(std::string message)
    {
        std::cerr << message << std::endl;
        exit(1);
    }

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
                _csvData[date] = intval;
            }
            file.close();
        }
        else
            printError("Error: could not open data.csv");
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
                if (intval < 0 || intval > 1000)
                    std::cerr << "Error: too large number." << std::endl;
                if (!parseDate(date) && intval > 0 || intval <= 1000)
                    _inputData[date] = intval;
            }
            file.close();
        }
        else
            printError("Error: could not open file.");
    };
    int parseDate(std::string date)
    {
        int year = std::stoi(date.substr(0,4));
        int month = std::stoi(date.substr(5,2));
        int day = std::stoi(date.substr(8,2));
        if (year < 2009 || year > 2022 || month < 1 || month > 12 || day < 1 || day > 31)
        {
            std::cout << "Error: bad input" << " => " << date << std::endl;
            return(1);
        }
        if (month == 2 && day > 29)
        {
            std::cout << "Error: bad input" << " => " << date << std::endl; 
            return(1);
        }
        return(0);     
    };
};

#endif