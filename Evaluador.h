#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

bool esOperador(char c);
int precedencia(char c);
int evaluarPostfija(const std::string& expresion);

