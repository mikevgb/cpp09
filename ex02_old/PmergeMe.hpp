#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <list>
#include <limits>


class PmergeMe
{
    private:
    std::vector<int> _vector;
    std::vector<int> _bup;
    std::list<int> _list;
    std::vector<int>::iterator it;
    double _elapsedVector;
    double _elapsedList;
    int _howManyNumbers;

    public:
    void parseAndStore(char *argv);
    PmergeMe(int argc, char **argv);
    ~PmergeMe();
    PmergeMe &operator=(PmergeMe const &in);
    PmergeMe(PmergeMe &copy);
    void mergeInsertionSortVector(std::vector<int> &input);
    void mergeInsertionSortList(std::list<int>& input);
    void printResults();
};

//./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`

#endif
