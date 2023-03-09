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
    RPN(int argc, char **argv) 
    {
        for(int i = 1; i < argc; i++)
        {
            std::string input = argv[i];
            if (input == "+" || input == "-" || input == "*" || input == "/")
            {
                int x = _rpnStack.top();
                std::cout << "x = " << x << std::endl;
                _rpnStack.pop();
                int y = _rpnStack.top();
                std::cout << "y = " << y << std::endl;
                _rpnStack.pop();
                makeMath(input[0], x, y);
            }
            else 
            {
                //!! check if its a number 
                _rpnStack.push(atoi(input.c_str()));
            }
        }
        std::cout << "Result: " <<  _rpnStack.top() << std::endl;        
    };
    ~RPN() {};
    void makeMath(char symb, int num1, int num2)
    {
        switch(symb)
        {
            case '+':
                std::cout << num1 << " + " << num2 << " = " << num1 + num2 << std::endl;
                _rpnStack.push(num1 + num2);
                break;
            case '-':
                std::cout << num1 << "-" << num2 << " = " << num1 - num2 << std::endl;
                _rpnStack.push(num1 - num2);
                break;
            case '/':
                std::cout << num1 << "/" << num2 << " = " << num1 / num2 << std::endl;
                _rpnStack.push(num1 / num2); //check for 0's
                break;
            case '*':
                std::cout << num1 << "*" << num2 << " = " << num1 * num2 << std::endl;
                _rpnStack.push(num1 * num2);
                break;
            
        }
    }
};

#endif

// https://mathworld.wolfram.com/ReversePolishNotation.html