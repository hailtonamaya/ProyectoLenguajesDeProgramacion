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

// Función para convertir una expresión infija a postfija y devolverla como string
std::string infijaAPostfija(const std::string& infija) {
    std::stringstream postfija;
    std::stack<char> pila;

    bool num_entero = false; // Bandera para verificar si estamos construyendo un número entero
    bool ultimo_fue_digito = false; // Bandera para verificar si el último caracter fue un dígito

    for (char ch : infija) {
        if (std::isspace(ch)) {
            // Ignorar espacios en blanco
            continue;
        }
        else if (isdigit(ch)) {
            if (!num_entero) {
                // Inicio de un nuevo número entero
                num_entero = true;
                if (ultimo_fue_digito) {
                    postfija << ", "; // Separación entre números enteros consecutivos
                }
            }
            postfija << ch; // Agregar dígito al número entero actual
            ultimo_fue_digito = true;
        }
        else {
            // Si encontramos un operador o paréntesis, finalizamos el número entero actual
            if (num_entero) {
                postfija << ", "; // Separación entre número entero y operador
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

    // Finalizar cualquier número entero que esté en progreso
    if (num_entero) {
        postfija << ", "; // Separación al final de un número entero
    }

    while (!pila.empty()) {
        postfija << pila.top() << ", ";
        pila.pop();
    }

    // Convertir stringstream a string y eliminar la última coma y espacio si existe
    std::string resultado = postfija.str();
    if (!resultado.empty() && resultado.substr(resultado.size() - 2) == ", ") {
        resultado = resultado.substr(0, resultado.size() - 2);
    }

    return resultado;
}