#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN
{
    private:
    std::stack<int> _rpnStack;

    public:
    RPN() {};
    ~RPN() {};
    int isNum(char x)
    {
        if (isdigit(x) == true)
            return 0;
        return 1;
    };
    int isOperator(char x)
    {
        if (x == '+' || x == '-' || x == '*' || x == '/')
            return 0;
        return 1;
    };
};

#endif

// https://mathworld.wolfram.com/ReversePolishNotation.html