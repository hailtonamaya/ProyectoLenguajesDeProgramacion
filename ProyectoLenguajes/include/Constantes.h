#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <algorithm>

struct Constante {
    std::string nombre;
    double valor;
};

class Constantes {
public:
    Constantes();
    virtual ~Constantes();

    std::string obtenerCadenaDeConstantes() const;
    std::string reemplazarConstantes(const std::string &expresion) const;
    bool validarNombre(const std::string &nombre) const;
void imprimirConstantes() const;
private:
    std::vector<Constante> constantes;
    std::unordered_map<std::string, double> constantesMap;

    void leerArchivo(const std::string &filename);
};

Constantes::Constantes() {

   try {
        leerArchivo("constantes");
    } catch (const std::exception &ex) {
        std::cerr << "Error al inicializar Constantes: " << ex.what() << std::endl;

    }
}

Constantes::~Constantes() {}

void Constantes::leerArchivo(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {

        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

        if (line.empty() || line[0] == '#') {
            continue;
        }


        auto equalPos = line.find('=');
        if (equalPos == std::string::npos) {
            std::cerr << "Error de formato en la línea: " << line << std::endl;
            continue;
        }

        std::string nombre = line.substr(0, equalPos);
        std::string valorStr = line.substr(equalPos + 1);
        double valor = std::stod(valorStr);


        auto it = std::find_if(constantes.begin(), constantes.end(),
                               [&nombre](const Constante &c) { return c.nombre == nombre; });

        if (it != constantes.end()) {
            std::cerr << "Advertencia: La constante '" << nombre << "' ya está definida." << std::endl;
            continue;
        }


        Constante constante = {nombre, valor};
        constantes.push_back(constante);
        constantesMap[nombre] = valor;
    }

    file.close();
}

std::string Constantes::obtenerCadenaDeConstantes() const {
    std::stringstream ss;
    for (const auto &constante : constantes) {
        ss << constante.nombre << "=" << constante.valor << "\n";
    }
    return ss.str();
}

std::string Constantes::reemplazarConstantes(const std::string &expresion) const {
    std::string resultado = expresion;
    for (const auto &constante : constantes) {
        std::regex constRegex("\\b" + constante.nombre + "\\b");
        resultado = std::regex_replace(resultado, constRegex, std::to_string(constante.valor));
    }
    return resultado;
}

bool Constantes::validarNombre(const std::string &nombre) const {
    auto it = std::find_if(constantes.begin(), constantes.end(),
                           [&nombre](const Constante &c) { return c.nombre == nombre; });

    return it == constantes.end();
}


void Constantes::imprimirConstantes() const {
    for (const auto &constante : constantes) {
        std::cout << constante.nombre << " = " << constante.valor << std::endl;
    }
}




#endif // CONSTANTES_H
