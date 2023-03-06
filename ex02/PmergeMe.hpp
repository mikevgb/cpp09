#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <string>

class PmergeMe
{
    private:
    std::string _input;
    std::vector<int> _firstGroupVector;
    std::vector<int> _secondGroupVector;
    std::vector<int> _finalVector;

    public:
    PmergeMe(std::string input) : _input(input) 
    {
        checkAndStore();
        insertionSortVectors();
        //mergeSortVectors();
    };
    ~PmergeMe() {};
    void checkAndStore()
    {
        for (unsigned long i = 0; i < _input.length(); i++)
        {
            std::cout << "checkandstore i " << i << std::endl;
            /*if (isdigit(_input[i]) == false)
            {
                std::cout << "Error" << std::endl;
                exit(1);
            }
            */
            // could use a bool operator
            if (i % 2 == 0)
                _firstGroupVector.push_back((int)(_input[i]));
            else
                _secondGroupVector.push_back((int)_input[i]);
        }
    };
    void insertionSortVectors()
    {
        //should use iterators
        std::cout << "insertionsortvectors 1" << std::endl;
        for (size_t i = 1; i < _firstGroupVector.size(); i++)
        {
            std::cout << "insertionsortvectors first" << _firstGroupVector[i] << std::endl;
            size_t temp = _firstGroupVector[_firstGroupVector.size()];
            size_t j = i - 1;
            while ( j >= 0 && temp <= (size_t)_firstGroupVector[j])
            {
                _firstGroupVector[j + 1] = _firstGroupVector[j];
                j = j - 1;
            }
            _firstGroupVector[j + 1] = temp;
        }
        for (size_t i = 1; i < _secondGroupVector.size(); i++)
        {
            std::cout << "insertionsortvectors second" << _secondGroupVector[i] << std::endl;
            size_t temp = _secondGroupVector[_secondGroupVector.size()];
            size_t j = i - 1;
            while ( j >= 0 && temp <= (size_t)_secondGroupVector[j])
            {
                _secondGroupVector[j + 1] = _secondGroupVector[j];
                j = j - 1;
            }
            _secondGroupVector[j + 1] = temp;
        }
    };
    void mergeSortVectors()
    {
        size_t i = 0; //firstgroupvector
        size_t j = 0; //secondgroupvector
        size_t k = 0; //finalvector

        while(i < _firstGroupVector.size() && j < _secondGroupVector.size())
        {
            if (_firstGroupVector[i] <= _secondGroupVector[j])
                _finalVector[k] = _firstGroupVector[i];
            else
                _finalVector[k] = _secondGroupVector[j];
            k++;
        }
        //copy left overs;
        while (i < _firstGroupVector.size())
        {
            _finalVector[k] = _firstGroupVector[i];
            i++;
            k++;
        }
        while (i < _secondGroupVector.size())
        {
            _finalVector[k] = _secondGroupVector[j];
            j++;
            k++;
        }
    }
    void printVector()
    {
        for (size_t i = 0; i < _finalVector.size(); i++)
            std::cout << _finalVector[i] << ' ';
        std::cout << std::endl;
    }
    void printInput()
    {
        std::cout << "_input " << _input << std::endl;
    }
};

#endif