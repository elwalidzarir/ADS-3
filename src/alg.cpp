#include "tstack.h"
#include <string>

using namespace std;

int priority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return -1;
    }
}

bool isDigit(char c) {
    int ascii = (int) c;
    return ascii >= 48 && ascii <= 57;
}

std::string infx2pstfx(std::string inf) {
    TStack<char> stack1;
    std::string output;
    for (int i = 0; i < inf.length(); i++) {
        if (isDigit(inf[i])) {
            output += inf[i];
        } else if (inf[i] == '(') {
            stack1.push(inf[i]);
        } else if (inf[i] == ')') {
            while (!stack1.isEmpty() && stack1.get() != '(') {
                output = output + stack1.get();
                stack1.pop();
            }
            if (stack1.get() == '(') {
                stack1.pop();
            }
        } else {
            while (!stack1.isEmpty() && priority(stack1.get()) >= priority(inf[i])) {
                output = output + stack1.get();
                stack1.pop();
            }
            stack1.push(inf[i]);
        }

    }

    while (!stack1.isEmpty()) {
        output = output + stack1.get();
        stack1.pop();
    }

    return output;
}

int eval(std::string pst) {
    TStack<int> stack2;
    for (int i = 0; i < pst.length(); i++) {
        if (isDigit(pst[i])) {
            stack2.push(pst[i] - '0');
        } else {
            int a = stack2.get();
            stack2.pop();
            int b = stack2.get();
            stack2.pop();
            if (pst[i] == '*') {
                stack2.push(a * b);
            } else if (pst[i] == '/') {
                stack2.push(b / a);
            } else if (pst[i] == '+') {
                stack2.push(a + b);
            } else if (pst[i] == '-') {
                stack2.push(b - a);
            }
        }
    }
    return stack2.get();
}