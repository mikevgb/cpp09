#include "RPN.hpp"

RPN::RPN() {};

RPN::~RPN() {};

RPN &RPN::operator=(RPN const &in)
{
    _rpnStack = in._rpnStack;
    return *this;
};

RPN::RPN(RPN &copy)
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
                std::cout << "Error" << std::endl;
                exit(1);
            }
        }
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
            _rpnStack.push(num1 / num2); //check for 0's
            break;
        case '*':
            _rpnStack.push(num1 * num2);
            break;
    }
};