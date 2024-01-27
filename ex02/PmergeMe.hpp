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
    std::vector<std::pair<int, int> > _vector;
    std::vector<int> _finalVector;
    std::vector<int> _bup;
    std::list<std::pair<int, int> > _list;
    std::list<int> _finalList;
    double _elapsedVector;
    double _elapsedList;
    int _howManyNumbers;
    long int _straggler;
    bool _isStraggler;

    public:
    PmergeMe(int argc, char **argv);
    ~PmergeMe();
    PmergeMe &operator=(PmergeMe const &in);
    PmergeMe(PmergeMe &copy);
    void mergeInsertionSortVector();
    void mergeInsertionSortList();
    void printResults();
};

//./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "` //linux
//./PmergeMe $(jot -r 3000 1 100000) //mac

#endif
