#include "Evaluador.h"

// Funci�n para verificar si un car�cter es un operador
//bool esOperador(char c) {
//    return c == '+' || c == '-' || c == '*' || c == '/';
//}
//
//// Funci�n para obtener la precedencia de un operador
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

// Funci�n para convertir una expresi�n infija a postfija y devolverla como string
std::string infijaAPostfija(const std::string& infija) {
    std::stringstream postfija;
    std::stack<char> pila;

    bool num_entero = false; // Bandera para verificar si estamos construyendo un n�mero entero
    bool ultimo_fue_digito = false; // Bandera para verificar si el �ltimo caracter fue un d�gito

    for (char ch : infija) {
        if (std::isspace(ch)) {
            // Ignorar espacios en blanco
            continue;
        }
        else if (isdigit(ch)) {
            if (!num_entero) {
                // Inicio de un nuevo n�mero entero
                num_entero = true;
                if (ultimo_fue_digito) {
                    postfija << ", "; // Separaci�n entre n�meros enteros consecutivos
                }
            }
            postfija << ch; // Agregar d�gito al n�mero entero actual
            ultimo_fue_digito = true;
        }
        else {
            // Si encontramos un operador o par�ntesis, finalizamos el n�mero entero actual
            if (num_entero) {
                postfija << ", "; // Separaci�n entre n�mero entero y operador
                num_entero = false;
                ultimo_fue_digito = false;
            }

            if (ch == '(') {
                pila.push(ch);
            }
            else if (ch == ')') {
                while (!pila.empty() && pila.top() != '(') {
                    postfija << pila.top() << ", ";
                    pila.pop();
                }
                pila.pop(); // Eliminar '(' de la pila
            }
            else {
                while (!pila.empty() && pila.top() != '(' && precedencia(pila.top()) >= precedencia(ch)) {
                    postfija << pila.top() << ", ";
                    pila.pop();
                }
                pila.push(ch);
            }

            ultimo_fue_digito = false;
        }
    }

    // Finalizar cualquier n�mero entero que est� en progreso
    if (num_entero) {
        postfija << ", "; // Separaci�n al final de un n�mero entero
    }

    while (!pila.empty()) {
        postfija << pila.top() << ", ";
        pila.pop();
    }

    // Convertir stringstream a string y eliminar la �ltima coma y espacio si existe
    std::string resultado = postfija.str();
    if (!resultado.empty() && resultado.substr(resultado.size() - 2) == ", ") {
        resultado = resultado.substr(0, resultado.size() - 2);
    }

    return resultado;
}