#include <iostream>
#include <string>


class Stack
{
private:

    struct Node
    {
        char data;
        Node* next;

        Node(char value)
        {
            data = value;
            next = nullptr;
        }
    };

    Node* top;

public:

    Stack()
    {
        top = nullptr;
    }
    ~Stack()
    {
        clear();
    }

    void push(char value)
    {
        Node* newNode = new Node(value);

        newNode->next = top;
        top = newNode;
    }

    char pop()
    {
        if (top == nullptr)
        {
            return '\0';
        }

        Node* temp = top;
        char value = top->data;

        top = top->next;

        delete temp;

        return value;
    }

    char peek()
    {
        if (top == nullptr)
        {
            return '\0';
        }

        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    void clear()
    {
        while (top != nullptr)
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};


class IntStack
{
private:
    
    struct Node
    {
        int data;
        Node* next;

        Node(int value)
        {
            data = value;
            next = nullptr;
        }
    };

    Node* top;

public:

    IntStack()
    {
        top = nullptr;
    }
    ~IntStack()
    {
        clear();
    }

    void push(int value)
    {
        Node* newNode = new Node(value);

        newNode->next = top;
        top = newNode;
    }

    int pop()
    {
        if (top == nullptr)
        {
            return 0;
        }

        Node* temp = top;
        int value = top->data;

        top = top->next;

        delete temp;

        return value;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    void clear()
    {
        while (top != nullptr)
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};


int precedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }

    if (op == '*' || op == '/' || op == '%')
    {
        return 2;
    }

    return 0;
}


std::string infixToPostfix(std::string expression)
{
    if (expression.empty())
    {
        return "";
    }

    Stack s;
    std::string postfix;

    for (int i = 0; i < expression.length(); i++)
    {
        if (isdigit(expression[i]))
        {
            while (i < expression.length() && isdigit(expression[i]))
            {
                postfix += expression[i];
                i++;
            }

            postfix += ' ';
            i--;
        }

        else if (expression[i] == '(')
        {
            s.push('(');
        }

        else if (expression[i] == ')')
        {
            while (!s.isEmpty() && s.peek() != '(')
            {
                postfix += s.pop();
                postfix += ' ';
            }


            if (s.isEmpty())
            {
                return "";
            }

            s.pop();
        }

        else if (expression[i] == '+' || expression[i] == '-' ||
                 expression[i] == '*' || expression[i] == '/' ||
                 expression[i] == '%')
        {
            while (!s.isEmpty() &&
                   s.peek() != '(' &&
                   precedence(s.peek()) >= precedence(expression[i]))
            {
                postfix += s.pop();
                postfix += ' ';
            }

            s.push(expression[i]);
        }
    }

    while (!s.isEmpty())
    {
      
        if (s.peek() == '(')
        {
            return "";
        }

        postfix += s.pop();
        postfix += ' ';
    }

    return postfix;
}


bool evaluatePostfix(std::string postfix, int& result)
{
    if (postfix.empty())
    {
        return false;
    }

    IntStack s;

    for (int i = 0; i < postfix.length(); i++)
    {
        if (postfix[i] == ' ')
        {
            continue;
        }

        if (isdigit(postfix[i]))
        {
            int num = 0;

            while (i < postfix.length() && isdigit(postfix[i]))
            {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }

            s.push(num);
            i--;
        }

        else if (postfix[i] == '+' || postfix[i] == '-' ||
                 postfix[i] == '*' || postfix[i] == '/' ||
                 postfix[i] == '%')
        {
            if (s.isEmpty())
            {
                return false;
            }

            int a = s.pop();

            if (s.isEmpty())
            {
                return false;
            }

            int b = s.pop();

            int value;

            if (postfix[i] == '+')
            {
                value = b + a;
            }

            else if (postfix[i] == '-')
            {
                value = b - a;
            }

            else if (postfix[i] == '*')
            {
                value = b * a;
            }

            else if (postfix[i] == '/')
            {
                if (a == 0)
                {
                    return false;
                }

                value = b / a;
            }

            else
            {
                if (a == 0)
                {
                    return false;
                }

                value = b % a;
            }

            s.push(value);
        }

        else
        {
            return false;
        }
    }

    if (s.isEmpty())
    {
        return false;
    }

    result = s.pop();

   
    if (!s.isEmpty())
    {
        return false;
    }

    return true;
}


int main()
{
    std::string expressions[] =
    {
        "2 + 3 * 4",              // Test 1
        "(2 + 3) * 4",            // Test 2
        "10 + 2 * 6",             // Test 3
        "(10 + 2) * (6 - 3)",     // Test 4
        "20 / 5 + 3",             // Test 5

        "((2 + 3) * (4 + 1))",    // Nested parentheses
        "2 + 3 * 4 - 6 / 2",      // Multiple operators
        "",                        // Empty expression
        "(2 + 3 * 4",             // Mismatched parentheses
        "10 / (5 - 5)"            // Division by zero
    };

    int totalTests = 10;

    for(int i = 0; i < totalTests; i++)
    {
        std::cout << "Test " << i + 1 << std::endl;
        std::cout << "Infix: " << expressions[i] << std::endl;

        std::string postfix = infixToPostfix(expressions[i]);

        if(postfix.empty())
        {
            std::cout << "Invalid expression" << std::endl;
        }
        else
        {
            std::cout << "Postfix: " << postfix << std::endl;

            int result;

            if(evaluatePostfix(postfix, result))
            {
                std::cout << "Result: " << result << std::endl;
            }
            else
            {
                std::cout << "Invalid expression or division by zero" << std::endl;
            }
        }

        std::cout << "-----------------------------------" << std::endl;
    }

    return 0;
}