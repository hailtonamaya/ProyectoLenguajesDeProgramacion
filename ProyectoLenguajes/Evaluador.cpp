#include "Evaluador.h"

// Función para verificar si un carácter es un operador
//bool esOperador(char c) {
//    return c == '+' || c == '-' || c == '*' || c == '/';
//}
//
//// Función para obtener la precedencia de un operador
//int precedencia(char c) {
//    if (c == '+' || c == '-')
//        return 1;
//    else if (c == '*' || c == '/')
//        return 2;
//    return 0;
//}
//
//int evaluarPostfija(const string& expresion) {
//    stack<int> pila;
//    stringstream ss(expresion);
//    string token;
//
//    while (ss >> token) {
//        if (isdigit(token[0])) {
//            pila.push(stoi(token));
//        }
//        else if (esOperador(token[0])) {
//            int operand2 = pila.top(); pila.pop();
//            int operand1 = pila.top(); pila.pop();
//
//            switch (token[0]) {
//            case '+':
//                pila.push(operand1 + operand2);
//                break;
//            case '-':
//                pila.push(operand1 - operand2);
//                break;
//            case '*':
//                pila.push(operand1 * operand2);
//                break;
//            case '/':
//                pila.push(operand1 / operand2);
//                break;
//            }
//        }
//    }
//
//    return pila.top();
//}


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

std::string infijaAPostfija(const std::string& infija) {
    std::string postfija;
    std::stack<char> pila;
    std::string numero;

    for (char ch : infija) {
        if (std::isspace(ch)) {
            continue;
        }
        else if (isdigit(ch)) {
            numero += ch;
        }
        else {
            if (!numero.empty()) {
                if (!postfija.empty()) {
                    postfija += ", ";
                }
                postfija += numero;
                numero.clear();
            }

            if (ch == '(') {
                pila.push(ch);
            }
            else if (ch == ')') {
                while (!pila.empty() && pila.top() != '(') {
                    if (!postfija.empty()) {
                        postfija += ", ";
                    }
                    postfija += pila.top();
                    pila.pop();
                }
                pila.pop(); 
            }
            else {
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
