#include "PmergeMe.hpp"

void PmergeMe::parseAndStore(char *argv)
{
    int len = strlen(argv);
    for (int i = 0; i < len; i++)
        if (!isdigit(argv[i])) //check if all chars are numbers
            std::cout << "Error: Bad input." << std::endl;
    char *end;
    long int tmp = strtol(argv, &end, 10);
    if (tmp > std::numeric_limits<int>::max()) //check if int range
        std::cout << "Error: Number out of range." << std::endl;
    // it = std::find(_vector.begin(), _vector.end(), tmp); //check repeated
    // if (it != _vector.end())
    //     printBadArgument(3);
    _vector.push_back(tmp); //store numbers
    _list.push_back(tmp);
    _bup.push_back(tmp);
};

PmergeMe::PmergeMe(int argc, char **argv)
{
    _howManyNumbers = argc - 1;
    for (int i = 1; i < argc; i++)
        parseAndStore(argv[i]);
    clock_t startTime = clock();
    mergeInsertionSortVector(_vector);
    _elapsedVector = (clock() - startTime) / (double)CLOCKS_PER_SEC;
    startTime = clock();
    mergeInsertionSortList(_list);
    _elapsedList = (clock() - startTime) / (double)CLOCKS_PER_SEC;
    printResults();
};

PmergeMe::~PmergeMe() {};

PmergeMe &PmergeMe::operator=(PmergeMe const &in)
{
    _vector = in._vector;
    _bup = in._bup;
    _list = in._list;
    _elapsedVector = in._elapsedVector;
    _elapsedList = in._elapsedList;
    _howManyNumbers = in._howManyNumbers;

};

PmergeMe::PmergeMe(PmergeMe &copy)
{
    *this = copy;
};

void PmergeMe::mergeInsertionSortVector(std::vector<int> &input) 
{
    const int threshold = 16;
    if (input.size() <= threshold)
    {
        std::sort(input.begin(), input.end());
        return;
    }
    std::vector<int> left(input.begin(), input.begin() + input.size() / 2);
    std::vector<int> right(input.begin() + input.size() / 2, input.end());
    mergeInsertionSortVector(left);
    mergeInsertionSortVector(right);
    input.clear();
    std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(input));
    if (input.size() > threshold)
    {
        std::vector<int>::iterator it = input.begin() + threshold;
        std::sort(it, input.end());
    }
};

void PmergeMe::mergeInsertionSortList(std::list<int> &input)
{
    const int threshold = 16;
    if (input.size() <= threshold) 
    {
        input.sort();
        return;
    }
    std::list<int> left, right;
    std::list<int>::iterator it = input.begin();
    for (size_t i = 0; i < input.size() / 2; i++) 
    {
        left.push_back(*it);
        it++;
    }
    while (it != input.end()) 
    {
        right.push_back(*it);
        it++;
    }
    mergeInsertionSortList(left);
    mergeInsertionSortList(right);
    input.clear();
    std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(input));
    if (input.size() > threshold) 
    {
        std::list<int>::iterator it = input.begin();
        std::advance(it, threshold);
        std::list<int> remaining(it, input.end());
        remaining.sort();
        input.erase(it, input.end());
        input.merge(remaining);
    }
};

void PmergeMe::printResults()
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _bup.size(); i++)
        std::cout << _bup[i] << " ";
    //std::cout << _vectorGroupCounter << std::endl;
    std::cout << std::endl << "After: ";
    for (size_t i = 0; i < _vector.size(); i++)
        std::cout << _vector[i] << " ";
    std::cout << std::endl << "Time to process a range of " << _howManyNumbers 
    << " elements with std::vector " << _elapsedVector << " seconds." << std::endl;
    std::cout << "Time to process a range of " << _howManyNumbers 
    << " elements with std::list " << _elapsedList << " seconds." << std::endl;
};