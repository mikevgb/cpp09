#include "RPN.hpp"

RPN::RPN() {};

RPN::~RPN() {};

RPN &RPN::operator=(RPN const &in)
{
    _rpnStack = in._rpnStack;
    return *this;
};

RPN::RPN(RPN const &copy)
{
    *this = copy;
};

RPN::RPN(char **argv)
{
    std::string input = argv[1];
    input.erase(remove_if(input.begin(), input.end(), isspace), input.end()); //clean whitespaces

    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
        {
            if (_rpnStack.size() < 2)
            {
                throw std::runtime_error("Error: Not enough operands");
            }
            int x = _rpnStack.top();
            _rpnStack.pop();
            int y = _rpnStack.top();
            _rpnStack.pop();
            makeMath(input[i], y, x);
        }
        else 
        {
            if (isdigit(input[i]))
                _rpnStack.push(input[i] - 48);
            else
            {
                throw std::runtime_error("Error: Invalid character");
            }
        }
    }

    if (_rpnStack.size() != 1) //check if the final result is correct
    {
        throw std::runtime_error("Error: Invalid RPN expression");
    }
    std::cout << _rpnStack.top() << std::endl;  
};

void RPN::makeMath(char symb, int num1, int num2)
{
    switch(symb)
    {
        case '+':
            _rpnStack.push(num1 + num2);
            break;
        case '-':
            _rpnStack.push(num1 - num2);
            break;
        case '/':
            if (num1 == 0 || num2 == 0)
            {
               throw std::runtime_error("Error: Can't divide by 0");
            }
            _rpnStack.push(num1 / num2);
            break;
        case '*':
            _rpnStack.push(num1 * num2);
            break;
    }
};