#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN
{
    private:
    std::stack<int> _rpnStack;

    public:
    RPN();
    RPN &operator=(RPN const &in);
    RPN(RPN &copy);
    RPN(char **argv);
    ~RPN();
    void makeMath(char symb, int num1, int num2);
};

#endif

// https://mathworld.wolfram.com/ReversePolishNotation.html