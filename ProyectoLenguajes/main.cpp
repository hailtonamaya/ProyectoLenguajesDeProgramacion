#include "Evaluador.h"

int main() {
    string expresion = "180+23-2+3*2";
    cout << "Expresion: " << expresion << endl;

    string resultado = infijaAPostfija(expresion);
    cout << "Resultado: " << resultado << endl;

    cout <<"evaluar posfija: " << evaluarPostfija(resultado) << endl;
    return 0;
}