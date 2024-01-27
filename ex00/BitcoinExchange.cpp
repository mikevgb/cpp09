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

BitcoinExchange::BitcoinExchange(std::string fileInput) : _fileInput(fileInput)
{
    try 
    {
        readDatabaseCSV();
        readFileInput();
        multiValues();  
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

BitcoinExchange::~BitcoinExchange() {};

void BitcoinExchange::readDatabaseCSV()
{
    std::ifstream file("data.csv");
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open data.csv");
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date, value;
        if (std::getline(ss, date, ',') && std::getline(ss, value, ','))
        {
            if (parseDate(date))
            {
                _csvData.insert(std::pair<std::string, std::string>(date, value));
            }
        }
    }
    file.close();
};

void BitcoinExchange::readFileInput()
{
    std::ifstream file(_fileInput);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file " + _fileInput);
    }
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }
        std::stringstream ss(line);
        std::string date, value;
        if (std::getline(ss, date, '|') && std::getline(ss, value, '|'))
        {
            date.erase(remove_if(date.begin(), date.end(), isspace), date.end()); //clean whitespaces
            value.erase(remove_if(value.begin(), value.end(), isspace), value.end());
            if (date == "date" && value == "value")
                continue;
            if (parseDate(date) && !value.empty())
            {
                _inputData.insert(std::pair<std::string, std::string>(date, value));
            }
        }    
        else
        {
            std::cerr << "Error: Incorrect format in " << _fileInput << " => " << line << std::endl;
        }        
    }
    file.close();
};

bool BitcoinExchange::parseDate(std::string date)
{
    if (date == "date")
    {
        return true;
    }
    if (date.length() != 10)
    {
        std::cerr << "Error: Incorrect date format (length) => " << date << std::endl;
        return false;
    }
    int year, month, day;
    if (sscanf(date.c_str(), "%4d-%2d-%2d", &year, &month, &day) != 3)
    {
        std::cerr << "Error: Incorrect date format => " << date << std::endl;
        return false;
    }
    if (year < 2009 || year > 2022 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        std::cerr << "Error: Incorrect date format => " << date << std::endl;
        return false;
    }   
    if (month == 2 && day > 29)
    {
        std::cerr << "Error: Incorrect date format => " << date << std::endl;
        return false;
    }
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
    try
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
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
};