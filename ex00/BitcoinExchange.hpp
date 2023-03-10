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
    //!! value must be either a float or a positive int
    std::map<std::string, std::string> _csvData;
    std::map<std::string, std::string> _inputData;
    //std::map<std::string, int> _result;
    
    void printError(std::string message)
    {
        std::cerr << message << std::endl;
        exit(1);
    }

    public:
    BitcoinExchange() 
    {
        readDatabaseCSV();
        //printMaps();
        readFileInput();
        printMaps();
        //multiValues();

    };
    //!! implementation in hpp file is forbidden!!!
    BitcoinExchange(std::string fileInput) 
    {
        (void)fileInput;
        readDatabaseCSV();
        readFileInput();
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
                _csvData[date] = value;
            }
            file.close();
        }
        else
            printError("Error: could not open data.csv");
    };

    //void readFileInput(std::string fileName)
    void readFileInput()
    {
        std::ifstream file("input.txt");
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                std::stringstream ss(line);
                std::string date, value;
                std::getline(ss, date, '|');
                std::getline(ss, value, '|');
                _inputData[date] = value;
            }
            file.close();
        }
        else
            printError("Error: could not open file.");
    };

    void parseDate(std::string date)
    {
        int year = std::stoi(date.substr(0,4));
        int month = std::stoi(date.substr(5,2));
        int day = std::stoi(date.substr(8,2));
        if (year < 2009 || year > 2022 || month < 1 || month > 12 || day < 1 || day > 31)
            std::cout << "Error: bad input" << " => " << date << std::endl;
        if (month == 2 && day > 29)
            std::cout << "Error: bad input" << " => " << date << std::endl; 
    };

    void printMaps()
    {
        // std::map<std::string, std::string>::const_iterator it;
        // for(it = _csvData.begin(); it != _csvData.end(); it++)
        //     std::cout << it->first << " " << it->second << std::endl;
        std::map<std::string, std::string>::const_iterator it2;
        for(it2 = _inputData.begin(); it2 != _inputData.end(); it2++)
            std::cout << it2->first << " " << it2->second << std::endl;
    };

    void multiValues()
    {
        std::map<std::string, std::string>::const_iterator it;
        std::map<std::string, std::string>::const_iterator it2;
        it2 = _inputData.begin();
        for (it = _csvData.begin(); it != _csvData.end(); it++)
        {
            for (it2 = _inputData.begin(); it2 != _inputData.end(); it2++)
            {
                if (it->first == it2->first && it->first != "date" && it2->first != "date")
                {
                    // std::cout << "hey!" << std::endl;
                    float tmp1;
                    float tmp2;
                    float result = 0.0;
                    tmp1 = std::stof(_csvData.at(it->second));
                    tmp2 = std::stof(_inputData.at(it2->second));
                    //if (tmp2 > 0)
                    //{
                        result = tmp1 * tmp2;
                        std::cout << it->first << " => " << it2->second << " " << result << std::endl;
                    //}
                    if (tmp2 > 0)
                        std::cout << "Error: not a positive number." << std::endl;
                }
            }
        }
    };
};

#endif