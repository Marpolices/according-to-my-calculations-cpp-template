#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cctype>

class Calculator {
public:
    double evaluate(const std::string& expression) {
        std::queue<std::string> postfix = infixToPostfix(expression);
        return evaluatePostfix(postfix);
    }

private:
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    
    std::queue<std::string> infixToPostfix(const std::string& expression) {
        std::stack<char> ops;
        std::queue<std::string> output;

        for (size_t i = 0; i < expression.size(); ++i) {
            char c = expression[i];

            if (isdigit(c)) {
                std::string number;
                while (i < expression.size() && isdigit(expression[i])) {
                    number.push_back(expression[i]);
                    i++;
                }
                output.push(number);
                i--; 
            }
            else if (c == '(') {
                ops.push(c);
            }
            else if (c == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    output.push(std::string(1, ops.top()));
                    ops.pop();
                }
                ops.pop(); 
            }
            else if (isOperator(c)) {
                while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                    output.push(std::string(1, ops.top()));
                    ops.pop();
                }
                ops.push(c);
            }
        }

        while (!ops.empty()) {
            output.push(std::string(1, ops.top()));
            ops.pop();
        }

        return output;
    }

    
    double evaluatePostfix(std::queue<std::string>& postfix) {
        std::stack<double> values;

        while (!postfix.empty()) {
            std::string token = postfix.front();
            postfix.pop();

            if (isdigit(token[0])) {
                values.push(std::stod(token));
            }
            else if (isOperator(token[0])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();

                switch (token[0]) {
                    case '+': values.push(a + b); break;
                    case '-': values.push(a - b); break;
                    case '*': values.push(a * b); break;
                    case '/': values.push(a / b); break;
                }
            }
        }

        return values.top();
    }
};


int main() {
    Calculator calculator;

    std::cout << calculator.evaluate("7+8") << std::endl;       
    std::cout << calculator.evaluate("1+3*5") << std::endl;     
    std::cout << calculator.evaluate("9*(8+3)") << std::endl;   
    std::cout << calculator.evaluate("(2+4)/7") << std::endl;   

    return 0;
}