#include "rpn.hpp"
//#include <iostream>
//#include <stack>

int main(int argc, char **argv)
{
    RPN calcu(argc, argv);
    // std::stack<int> _rpnStack;
  
    // for ( int i = 1; i < argc; i++)
    // {
    //     std::string input = argv[i];
    //     if (input == "+")
    //     {
    //         int x = _rpnStack.top();
    //         _rpnStack.pop();
    //         int y = _rpnStack.top();
    //         _rpnStack.pop();
    //         _rpnStack.push(x + y);
    //     }
    //     else if(input == "-")
    //     {
    //         int x = _rpnStack.top();
    //         _rpnStack.pop();
    //         int y = _rpnStack.top();
    //         _rpnStack.pop();
    //         _rpnStack.push(x - y);
    //     }
    //     else if(input == "*")
    //     {
    //         int x = _rpnStack.top();
    //         _rpnStack.pop();
    //         int y = _rpnStack.top();
    //         _rpnStack.pop();
    //         _rpnStack.push(x * y);
    //     }
    //     else if(input == "/")
    //     {
    //         int x = _rpnStack.top();
    //         _rpnStack.pop();
    //         int y = _rpnStack.top();
    //         _rpnStack.pop();
    //         _rpnStack.push(x / y);
    //     }
    //     else
    //         _rpnStack.push(atoi(input.c_str()));
    // }

    // std::cout << "Result: " <<  _rpnStack.top() << std::endl;
    return 0;
}