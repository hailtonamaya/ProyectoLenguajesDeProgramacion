#ifndef EVALUADOR_H
#define EVALUADOR_H

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <map>
#include <cctype>
#include <gtk/gtk.h>


bool esOperador(char c);
int precedencia(char c);

class Evaluador {
public:
    Evaluador( GtkWidget *mainWindow);
    Evaluador( );

    void showAlert(const std::string& message);
    void imprimirEstado(const std::string& resultado, const std::stack<char>& pila);
    std::string infijaAPostfija(const std::string& infija);
    void imprimirEstadoPila(const std::stack<double>& pila);
    double evaluarPostfija(const std::string& expresion);
    bool evaluarInfija(const std::string& expresion);

private:

    GtkWidget *mainWindow;
    bool MostrarInterfaz = false;
};

#endif // EVALUADOR_H
