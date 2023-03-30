#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &in)
{
    _csvData = in._csvData;
    _inputData = in._inputData;
    _fileInput = in._fileInput;
    return *this;
};

BitcoinExchange::BitcoinExchange(BitcoinExchange &copy)
{
    *this = copy;
};

BitcoinExchange::BitcoinExchange(std::string fileInput)
{
    _fileInput = fileInput;
    readDatabaseCSV();
    readFileInput();
    multiValues();
}

BitcoinExchange::~BitcoinExchange() {};

void BitcoinExchange::readDatabaseCSV()
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
            _csvData.insert(std::pair<std::string, std::string>(date, value));
        }
        file.close();
    }
    else
    {
        std::cerr << "Error: could not open data.csv" << std::endl;
        exit(1);
    }
};

void BitcoinExchange::readFileInput()
{
    std::ifstream file(_fileInput);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string date, value;
            std::getline(ss, date, '|');
            std::getline(ss, value, '|');
            date.erase(remove_if(date.begin(), date.end(), isspace), date.end()); //clean whitespaces
            value.erase(remove_if(value.begin(), value.end(), isspace), value.end());
            _inputData.insert(std::pair<std::string, std::string>(date, value));
        }
        file.close();
    }
    else
    {
            std::cerr << "Error: could not open file " << _fileInput << std::endl;
            exit(1);
    }   
};

bool BitcoinExchange::parseDate(std::string date)
{
    std::stringstream ss(date.substr(0,4));
    int year;
    ss >> year;
    std::stringstream ss2(date.substr(5,2));
    int month;
    ss2 >> month;
    std::stringstream ss3(date.substr(8,2));
    int day;
    ss3 >> day;
    if (year < 2009 || year > 2022 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        std::cout << "Error: bad input" << " => " << date << std::endl;
        return false;
    }   
    if (month == 2 && day > 29)
    {
        std::cout << "Error: bad input" << " => " << date << std::endl;
        return false;
    }
    else
        return true;   
};

void BitcoinExchange::printMaps()
{
    std::map<std::string, std::string>::const_iterator it;
    for (it = _csvData.begin(); it != _csvData.end(); it++)
        std::cout << it->first << " " << it->second << std::endl;
    std::map<std::string, std::string>::const_iterator it2;
    for(it2 = _inputData.begin(); it2 != _inputData.end(); it2++)
        std::cout << it2->first << it2->second << std::endl;
};

void BitcoinExchange::multiValues()
{
    std::multimap<std::string, std::string>::const_iterator it;
    std::multimap<std::string, std::string>::const_iterator it2;
    for (it2 = _inputData.begin(); it2 != _inputData.end(); it2++)
    {
        if (it2->first != "date")
        {
            if (parseDate(it2->first) == true)
            {
                it = _csvData.lower_bound(it2->first);
                if (it != _csvData.end())
                {
                    float tmp1;
                    float tmp2;
                    float result = 0.0;
                    std::stringstream ss(it->second); //no stof allowed :(
                    ss >> tmp1;
                    std::stringstream ss2(it2->second);
                    ss2 >> tmp2;
                    if (tmp2 < 0)
                        std::cerr << "Error: not a positive number." << std::endl;
                    else if (tmp2 > 1000)
                        std::cerr << "Error: too large number." << std::endl;
                    else
                    {
                        result = tmp1 * tmp2;
                        std::cout << it->first << " => " << it2->second << " " << "= " << result << std::endl;
                    }
                }
            }         
        }
    }
};