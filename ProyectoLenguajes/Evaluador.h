#pragma once
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <map>
#include <cctype>
using namespace std;

bool esOperador(char c);
int precedencia(char c);
int evaluarPostfija(const std::string& expresion);
string infijaAPostfija(const std::string& infija);