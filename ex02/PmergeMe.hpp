#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>

class PmergeMe
{
    std::string _input;
    std::vector<std::pair<int, int> > _pairV;

    public:
    PmergeMe(int argc, char **argv)
    {
        //!!!measure time
        
        vectorOfPairs(argc, argv);
    };
    ~PmergeMe() {};
    void vectorOfPairs(int argc, char **argv)
    {
        //!!! check if number of elements its odd or even
        //4 even
        std::cout << "Before: ";
        for (int i = 1; i < argc; i++)
        {
            std::cout << argv[i] << " ";
        }
        std::cout << std::endl;

        for (int i = 1; i < argc; i+=2)
        {
            //make sorted pairs
            int tmp1;
            int tmp2;
            std::stringstream ss(argv[i]);
            ss >> tmp1;
            std::stringstream ss2(argv[i + 1]);
            ss2 >> tmp2;
            if (tmp1 < tmp2)
                _pairV.push_back(std::make_pair(tmp1, tmp2));
            else
                _pairV.push_back(std::make_pair(tmp2, tmp1));
            
        }
        //sort based on A
        std::sort(_pairV.begin(), _pairV.end());
        //call binaryInsertion till end
        int mid;
        
        for(size_t i = 0; i < _pairV.size(); i++)
        {
            
            if (_pairV[i].second != -1)
            {
                mid = _pairV.size() / 2;
                //printVectorOfPairs();
                //std::cout << "mid send = " << mid << std::endl;
                //std::cout << "valToIndex = " << _pairV[i].second << std::endl;
                binarySearchInsertionVectorOfPairs(mid, _pairV[i].second);
                _pairV[i].second = -1;
                //std::cout << "------------------------" << std::endl;
            }
        }
        std::cout << "After:  ";
        for (size_t i = 0; i < _pairV.size(); i++)
        {
            std::cout << _pairV[i].first << " ";
        }
        std::cout << std::endl;
        //printVectorOfPairs();
    };


    int recalcMidVectorOfPairs(int lastMid)
    {
        int idk = ((_pairV.size() - lastMid) / 2);
        return _pairV.size() / 2 + idk;
    };

    void binarySearchInsertionVectorOfPairs(int lastMid, int valToIndex)
    {
        int recalcMid;
        if (valToIndex > _pairV[lastMid].first)
        {
            if (valToIndex < _pairV[lastMid + 1].first)
                _pairV.insert(_pairV.begin() + lastMid + 1, std::make_pair(valToIndex, -1));
            else if (valToIndex > _pairV[_pairV.size() - 1].first)
                _pairV.push_back(std::make_pair(valToIndex, -1));
            else
            {
                recalcMid = recalcMidVectorOfPairs(lastMid);
                binarySearchInsertionVectorOfPairs(recalcMid, valToIndex);
            }      
        }
        else if (valToIndex < _pairV[lastMid].first)
        {
            if (valToIndex > _pairV[lastMid + 1].first)
                _pairV.insert(_pairV.begin() + lastMid - 1, std::make_pair(valToIndex, -1));
            else
            {
                recalcMid = recalcMidVectorOfPairs(lastMid);
                binarySearchInsertionVectorOfPairs(recalcMid, valToIndex);
            }
        }
    };

    void printVectorOfPairs()
    {
        for(size_t i = 0; i < _pairV.size(); i++)
        {
            std::cout << _pairV[i].first << " " << _pairV[i].second << std::endl;
        }
    };
};

#endif


//1. group list into pairs, if list has odd number of elements, the last one is unpaired

//2. sort each pair (comparing A and B)

//3. order the list based on A, the unpaired is consider the last B

//4. binary insertion sort of group B on A