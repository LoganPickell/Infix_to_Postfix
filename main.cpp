// University of Arkansas at Little Rock
// Department of Computer Science
// CPSC 2380: Algorithms
// Fall 2023
// Project 2: Infix to Postfix Conversion
// Due Date: November 21, 2023
// Name: Logan Pickell
// T-number (Last 4 Digits): 5865
// Description of the Program (2-3 sentences): 
// This program converts infix arithmetic expressions to postfix. 
// Each operator and operand is separated by at least one space.
// Date Written: 11/8
// Date Revised:

#include <iostream>
#include <stack>
#include <string>

using namespace std;

string infixToPostfix(char* str);
int getPrecedence(char op);


int main()
{
    char* str = new char[80];
    while(1)// type control_c to exit the loop
    {
        //assuming legal arithemic expressions only
        cout << "Enter an arithmetic equation..." << endl; cin.getline(str, 80);
        cout << infixToPostfix(str) << endl;
    }
}


string infixToPostfix(char* str)
{
    stack<char>operators;//adding operators to the stack. If stack operater has higher precedence, we add it to the string. 
    string postfix;
    int i{ 0 };
    while (str[i] != '\0')
    {
  
        switch (str[i])
        {
        case('+'):
        case('-'):
        case('*'):
        case('/'):
        case('^'):
            while (!operators.empty() && operators.top() != '(' && getPrecedence(operators.top()) >= getPrecedence(str[i]))//check which operation should go first
            {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.push(str[i]);
            break;
        case ('('):
            operators.push(str[i]);
            break;
        case (')'): 
            while (!operators.empty() && operators.top() != '(') { // stack will contain the operator before and any operators inside the '()'
                postfix += operators.top();//we add all the operators inside the '(' to the string (which are in order), then pop off stack
                postfix += ' ';
                operators.pop();
            }
            operators.pop();//pop '(' off and continue
            break;

        case (' ')://ignore spaces, were adding spaces after each operand and operator
            break;

        default://add operands to string
            postfix += str[i];
            postfix += ' ';
            break;
        }//end switch
        i++;
    }//end of string

        while (!operators.empty())
        {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
        }
    return postfix;
}

int getPrecedence(char op)
{
    switch (op)
    {
    case('+'):
    case('-'):
        return 1;
    case('*'):
    case('/'):
        return 2;
    case('('):
    case(')'):
        return 3;
    case('^'):
        return 4;
    default:
        return 0;
    }
}