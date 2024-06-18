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

void imprimirEstado(const std::string& resultado, const std::stack<char>& pila) {
    std::cout << "Resultado => " << resultado << "\n";
    std::cout << "Pila => [ ";
    std::stack<char> pilaCopia = pila;
    while (!pilaCopia.empty()) {
        std::cout << pilaCopia.top() << " ";
        pilaCopia.pop();
    }
    std::cout << "]\n";
}

std::string infijaAPostfija(const std::string& infija) {
    std::cout << "-----Convirtiendo de infija a postfija-----" << std::endl;
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
                imprimirEstado(postfija, pila);
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
                    imprimirEstado(postfija, pila);
                }
                pila.pop();
            } else {
                while (!pila.empty() && precedencia(pila.top()) >= precedencia(ch)) {
                    if (!postfija.empty()) {
                        postfija += ", ";
                    }
                    postfija += pila.top();
                    pila.pop();
                    imprimirEstado(postfija, pila);
                }
                pila.push(ch);
            }
            imprimirEstado(postfija, pila);
        }
    }

    if (!numero.empty()) {
        if (!postfija.empty()) {
            postfija += ", ";
        }
        postfija += numero;
        imprimirEstado(postfija, pila);
    }

    while (!pila.empty()) {
        if (!postfija.empty()) {
            postfija += ", ";
        }
        postfija += pila.top();
        pila.pop();
        imprimirEstado(postfija, pila);
    }

    return postfija;
}

void imprimirEstadoPila(const std::stack<double>& pila) {
    std::stack<double> pilaCopia = pila;
    std::ostringstream oss;
    oss << "Pila => [ ";
    while (!pilaCopia.empty()) {
        oss << pilaCopia.top() << " ";
        pilaCopia.pop();
    }
    oss << "]";
    std::cout << oss.str() << "\n";
}

double evaluarPostfija(const std::string& expresion) {
    std::cout << "-----Evaluando expresion postfija-----" << std::endl;
    std::stack<double> pila;
    std::stringstream ss(expresion);
    std::string token;

    while (std::getline(ss, token, ',')) {
        token.erase(0, token.find_first_not_of(" "));
        token.erase(token.find_last_not_of(" ") + 1);

        if (!token.empty() && (std::isdigit(token[0]) || token[0] == '.' || (token[0] == '-' && token.length() > 1))) {
            pila.push(std::stod(token));
            imprimirEstadoPila(pila);
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
            imprimirEstadoPila(pila);
        }
    }
    return pila.top();
}

bool evaluarInfija(const std::string& expresion) {
    std::stack<char> pila;
    bool ultimoEsOperador = true;
    bool puntoEnNumero = false;
    bool huboDivision = false;

    for (size_t i = 0; i < expresion.length(); ++i) {
        char c = expresion[i];

        if (std::isdigit(c)) {
            if (huboDivision) {
                if (c == '0') {
                    size_t j = i + 1;
                    while (j < expresion.length() && (std::isdigit(expresion[j]) || expresion[j] == '.')) {
                        if (expresion[j] != '0') {
                            break;
                        }
                        j++;
                    }
                    if (j == expresion.length() || !std::isdigit(expresion[j])) {
                        std::cout << "Error: Division por cero.\n";
                        return false;
                    }
                }
                huboDivision = false;
            }
            ultimoEsOperador = false;
            puntoEnNumero = false;
        } else if (c == '.') {
            if (puntoEnNumero) {
                std::cout << "Error: Numero inválido con multiples puntos.\n";
                return false;
            }
            if (ultimoEsOperador) {
                std::cout << "Error: El punto decimal no puede estar despues de un operador o al inicio.\n";
                return false;
            }
            puntoEnNumero = true;
        } else if (esOperador(c)) {
            if (ultimoEsOperador) {
                std::cout << "Error: Dos operadores seguidos o expresion comenzando con operador.\n";
                return false;
            }
            if (c == '/') {
                huboDivision = true;
            }
            ultimoEsOperador = true;
        } else if (c == '(') {
            pila.push(c);
            ultimoEsOperador = true;
        } else if (c == ')') {
            if (pila.empty() || pila.top() != '(') {
                std::cout << "Error: Parentesis desbalanceados.\n";
                return false;
            }
            pila.pop();
            ultimoEsOperador = false;
        } else if (!std::isspace(c)) {
            std::cout << "Error: Caracter inválido en la expresion.\n";
            return false;
        }
    }

    if (ultimoEsOperador) {
        std::cout << "Error: La expresion no puede terminar con un operador.\n";
        return false;
    }

    if (!pila.empty()) {
        std::cout << "Error: Parentesis desbalanceados.\n";
        return false;
    }

    return true;
}