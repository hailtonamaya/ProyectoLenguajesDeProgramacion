#include "Evaluador.h"
#include <stack>
#include <sstream>
#include <string>
#include <cctype>

int precedencia(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '(':
    case ')':
        return 0;
    default:
        return -1;
    }
}

bool esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infijaAPostfija(const std::string& infija) {
    std::string postfija;
    std::stack<char> pila;
    std::string numero;

    for (char ch : infija) {
        if (std::isspace(ch)) {
            continue;
        } else if (std::isdigit(ch) || ch == '.') {
            numero += ch;
        } else {
            if (!numero.empty()) {
                if (!postfija.empty()) {
                    postfija += ", ";
                }
                postfija += numero;
                numero.clear();
            }

            if (ch == '(') {
                pila.push(ch);
            } else if (ch == ')') {
                while (!pila.empty() && pila.top() != '(') {
                    if (!postfija.empty()) {
                        postfija += ", ";
                    }
                    postfija += pila.top();
                    pila.pop();
                }
                pila.pop();
            } else {
                while (!pila.empty() && precedencia(pila.top()) >= precedencia(ch)) {
                    if (!postfija.empty()) {
                        postfija += ", ";
                    }
                    postfija += pila.top();
                    pila.pop();
                }
                pila.push(ch);
            }
        }
    }

    if (!numero.empty()) {
        if (!postfija.empty()) {
            postfija += ", ";
        }
        postfija += numero;
    }

    while (!pila.empty()) {
        if (!postfija.empty()) {
            postfija += ", ";
        }
        postfija += pila.top();
        pila.pop();
    }

    return postfija;
}

double evaluarPostfija(const std::string& expresion) {
    std::stack<double> pila;
    std::stringstream ss(expresion);
    std::string token;

    while (std::getline(ss, token, ',')) {
        token.erase(0, token.find_first_not_of(" "));
        token.erase(token.find_last_not_of(" ") + 1);

        if (!token.empty() && (std::isdigit(token[0]) || token[0] == '.' || (token[0] == '-' && token.length() > 1))) {
            pila.push(std::stod(token));
        } else if (!token.empty() && esOperador(token[0])) {
            double operand2 = pila.top(); pila.pop();
            double operand1 = pila.top(); pila.pop();

            switch (token[0]) {
            case '+':
                pila.push(operand1 + operand2);
                break;
            case '-':
                pila.push(operand1 - operand2);
                break;
            case '*':
                pila.push(operand1 * operand2);
                break;
            case '/':
                pila.push(operand1 / operand2);
                break;
            }
        }
    }
    return pila.top();
}

bool evaluarInfija(const std::string& expresion) {
    std::stack<char> pila;
    bool ultimoEsOperador = true; 

    for (char c : expresion) {
        if (std::isdigit(c) || c == '.') {
            ultimoEsOperador = false;
        } else if (esOperador(c)) {
            if (ultimoEsOperador) return false; 
            ultimoEsOperador = true;
        } else if (c == '(') {
            pila.push(c);
            ultimoEsOperador = true;
        } else if (c == ')') {
            if (pila.empty() || pila.top() != '(') return false;
            pila.pop();
            ultimoEsOperador = false;
        } else if (!std::isspace(c)) { 
            return false;
        }
    }
    if (ultimoEsOperador) return false; 
    return pila.empty();
}
