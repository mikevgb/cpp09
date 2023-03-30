#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <algorithm>
// #include <sstream>
#include <cstring>
#include <list>
#include <limits>

class PmergeMe
{
    private:
    std::vector<int> _vector;
    std::list<int> _list;
    std::vector<int>::iterator it;

    public:
    void printBadArgument(int code)
    {
        std::cerr << "Error: bad argument " << code << std::endl;
        exit(1);
    };
    void parseAndStore(char *argv)
    {
        int len = strlen(argv);
        for (int i = 0; i < len; i++)
            if (!isdigit(argv[i])) //check if all chars are numbers
                printBadArgument(1);
        char *end;
        long int tmp = strtol(argv, &end, 10);
        if (tmp > std::numeric_limits<int>::max()) //check if int range
            printBadArgument(2);
        it = std::find(_vector.begin(), _vector.end(), tmp); //check repeated
        if (it != _vector.end())
            printBadArgument(3);
        _vector.push_back(tmp); //store numbers
        _list.push_back(tmp);
    };
    PmergeMe(int argc, char **argv)
    {
        int tmp;
        for (int i = 1; i < argc; i++)
            parseAndStore(argv[i]);

        //printVector();
        clock_t startTime = clock();
        mergeInsertionSortVector(_vector);
        double elapsedTime = (clock() - startTime) / (double)CLOCKS_PER_SEC;
        std::cout << "Time vector = " << elapsedTime << std::endl;
        startTime = clock();
        mergeInsertionSortList(_list);
        elapsedTime = (clock() - startTime) / (double)CLOCKS_PER_SEC;
        std::cout << "Time list = " << elapsedTime << std::endl;
        //printVector();
    };
    ~PmergeMe() {};
    void mergeInsertionSortVector(std::vector<int> &input) 
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
    void mergeInsertionSortList(std::list<int>& input)
    {
        const int threshold = 16;
        if (input.size() <= threshold) 
        {
            input.sort();
            return;
        }
        std::list<int> left, right;
        std::list<int>::iterator it = input.begin();
        for (int i = 0; i < input.size() / 2; i++) 
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

    void printVector()
    {
        std::cout << "print vector" << std::endl;
        //std::cout << _vectorGroupCounter << std::endl;
        for (int i = 0; i < _vector.size(); i++)
            std::cout << i << " = " << _vector[i] << std::endl;
    }

};

//make groups of 15 elements
//insertion sort https://iq.opengenus.org/insertion-sort/

//./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`

#endif
