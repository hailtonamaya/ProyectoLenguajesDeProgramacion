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
    std::string postfija;
    std::stack<char> pila;

    // Mapa para almacenar la precedencia de los operadores
    std::map<char, int> precedencias;
    precedencias['+'] = 1;
    precedencias['-'] = 1;
    precedencias['*'] = 2;
    precedencias['/'] = 2;
    precedencias['('] = 0; // Par�ntesis izquierdo tiene la menor precedencia

    for (char ch : infija) {
        if (std::isspace(ch)) {
            // Ignorar espacios en blanco
            continue;
        }
        else if (isdigit(ch)) {
            // Manejar n�meros enteros correctamente
            if (!postfija.empty() && std::isdigit(postfija.back())) {
                postfija.back() = ch; // Continuar construyendo el n�mero
            }
            else {
                if (!postfija.empty()) {
                    postfija += ", "; // Separaci�n entre elementos
                }
                postfija += ch; // Inicio de un nuevo n�mero
            }
        }
        else if (ch == '(') {
            // Si es un par�ntesis izquierdo, agregarlo a la pila
            pila.push(ch);
        }
        else if (ch == ')') {
            // Si es un par�ntesis derecho, desapilar operadores hasta encontrar el par�ntesis izquierdo correspondiente
            while (!pila.empty() && pila.top() != '(') {
                postfija += ", ";
                postfija += pila.top();
                pila.pop();
            }
            pila.pop(); // Sacar el par�ntesis izquierdo de la pila
        }
        else { // Operador encontrado
            while (!pila.empty() && precedencias[pila.top()] >= precedencias[ch]) {
                postfija += ", ";
                postfija += pila.top();
                pila.pop();
            }
            pila.push(ch);
            postfija += ", "; // Separaci�n despu�s del operador
        }
    }

    // Vaciar la pila al final de la expresi�n
    while (!pila.empty()) {
        postfija += ", ";
        postfija += pila.top();
        pila.pop();
    }

    // Eliminar el �ltimo espacio si existe
    if (!postfija.empty()) {
        postfija.pop_back();
    }

    return postfija;
}