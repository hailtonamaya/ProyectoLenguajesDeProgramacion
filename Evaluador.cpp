#include "Evaluador.h"

// Función para verificar si un carácter es un operador
bool esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Función para obtener la precedencia de un operador
int precedencia(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    return 0; 
}

int evaluarPostfija(const string& expresion) {
    stack<int> pila;
    stringstream ss(expresion);
    string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            pila.push(stoi(token));
        } else if (esOperador(token[0])) {
            int operand2 = pila.top(); pila.pop();
            int operand1 = pila.top(); pila.pop();

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

