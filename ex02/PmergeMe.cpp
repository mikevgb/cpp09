#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    _howManyNumbers = argc - 1;
    _isStraggler = false;
    if (_howManyNumbers % 2 != 0)
    {
        _straggler = atoi(argv[_howManyNumbers]);
        _isStraggler = true;
        argv[_howManyNumbers] = NULL;
    }
    for (int i = 1; i < argc; i += 2)
    {
        if (argv[i] == NULL)
            break;
        else
        {
            if (!isdigit(*argv[i]) || !isdigit(*argv[i + 1]))
                std::cerr << "Error: Bad input." << std::endl;
            else
            {
                int tmp1 = atoi(argv[i]);
                int tmp2 = atoi(argv[i + 1]);
                _vector.push_back(std::make_pair(tmp1, tmp2));
                _list.push_back(std::make_pair(tmp1, tmp2));
                _bup.push_back(tmp1);
                _bup.push_back(tmp2);
            }
        }    
    };
    clock_t startTime = clock();
    mergeInsertionSortVector();
    _elapsedVector = (clock() - startTime) / (double)(CLOCKS_PER_SEC / 1000000);
    startTime = clock();
    mergeInsertionSortList();
    _elapsedList = (clock() - startTime) / (double)(CLOCKS_PER_SEC / 1000000);
    printResults();
};

PmergeMe::~PmergeMe() {};

PmergeMe &PmergeMe::operator=(PmergeMe const &in)
{
    _vector = in._vector;
    _finalVector = in._finalVector;
    _finalList = in._finalList;
    _bup = in._bup;
    _list = in._list;
    _elapsedVector = in._elapsedVector;
    _elapsedList = in._elapsedList;
    _howManyNumbers = in._howManyNumbers;
    return *this;
};

PmergeMe::PmergeMe(PmergeMe &copy)
{
    _vector = copy._vector;
    _finalVector = copy._finalVector;
    _finalList = copy._finalList;
    _bup = copy._bup;
    _list = copy._list;
    _elapsedVector = copy._elapsedVector;
    _elapsedList = copy._elapsedList;
    _howManyNumbers = copy._howManyNumbers;
};

void PmergeMe::mergeInsertionSortVector()
{
    //sort each pair
    for (std::vector<std::pair<int, int> >::iterator it = _vector.begin(); it != _vector.end(); it++)
    {
        if (it->first < it->second)
            std::swap(it->first, it->second);
    }
    //store the B values (the small values) in _finalVector
    for (std::vector<std::pair<int, int> >::iterator it = _vector.begin(); it != _vector.end(); it++)
    {
        _finalVector.push_back(it->second);
    }
    //sort the B values in descending order
    std::sort(_finalVector.begin(), _finalVector.end(), std::greater<int>());
    //insert the first values of _vector in _finalVector in descending order
    for (std::vector<std::pair<int, int> >::iterator it = _vector.begin(); it != _vector.end(); ++it)
    {
        _finalVector.insert(std::upper_bound(_finalVector.begin(), _finalVector.end(), it->first, std::greater<int>()), it->first);
    }
    //if straggler exists, insert it
    if ( _isStraggler == true)
    {
        _finalVector.insert(std::upper_bound(_finalVector.begin(), _finalVector.end(), _straggler, std::greater<int>()), _straggler);
    }
}

void PmergeMe::mergeInsertionSortList()
{
    //sort each pair
    for (std::list<std::pair<int, int> >::iterator it = _list.begin(); it != _list.end(); it++)
    {
        if (it->first < it->second)
            std::swap(it->first, it->second);
    }
    //store the B values (the small values) in the _finalList)
    for (std::list<std::pair<int, int> >::iterator it = _list.begin(); it != _list.end(); it++)
    {
        _finalList.push_back(it->second);
    }
    //sort the B values in descending order
    _finalList.sort(std::greater<int>());
    //insert the first values of _list in _finalList in descending order
    for (std::list<std::pair<int, int> >::iterator it = _list.begin(); it != _list.end(); it++)
    {
        _finalList.insert(std::upper_bound(_finalList.begin(), _finalList.end(), it->first, std::greater<int>()), it->first);
    }
    //if straggler exists, insert it
    if ( _isStraggler == true)
    {
        _finalList.insert(std::upper_bound(_finalList.begin(), _finalList.end(), _straggler, std::greater<int>()), _straggler);
    }
}

void PmergeMe::printResults()
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _bup.size(); i++)
        std::cout << _bup[i] << " ";
    std::cout << std::endl << "After: ";
    for (std::vector<int>::iterator it = _finalVector.begin(); it != _finalVector.end(); it++)
        std::cout << *it << " ";
    // std::cout << std::endl << "After (list): ";
    // for (std::list<int>::iterator it = _finalList.begin(); it != _finalList.end(); it++)
    //     std::cout << *it << " ";
    std::cout << std::endl << "Time to process a range of " << _howManyNumbers 
    << " elements with std::vector : " << _elapsedVector << " us" << std::endl;
    std::cout << "Time to process a range of " << _howManyNumbers 
    << " elements with std::list : " << _elapsedList << " us" << std::endl;
};