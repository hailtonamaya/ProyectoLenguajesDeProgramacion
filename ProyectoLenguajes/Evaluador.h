#pragma once
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <map>
#include <cctype>

bool esOperador(char c);
int precedencia(char c);
double evaluarPostfija(const std::string& expresion);
void imprimirEstado(const std::string& resultado, const std::stack<char>& pila);
std::string infijaAPostfija(const std::string& infija);
bool evaluarInfija(const std::string& expresion);