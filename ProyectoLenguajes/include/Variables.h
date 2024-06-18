#ifndef VARIABLES_H
#define VARIABLES_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <algorithm>
#include "Constantes.h"
#include <gtk/gtk.h>

struct Variable {
    std::string nombre;
    double valor;
};

class Variables {
public:
    Variables(Constantes constantesFile, GtkWidget *mainWindow)
        : constantes(constantesFile), mainWindow(mainWindow) {}

    // Función para mostrar una alerta en GTK
    void show_alert(const std::string &message) const {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(mainWindow),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "%s", message.c_str());
        gtk_window_set_title(GTK_WINDOW(dialog), "Alerta");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    std::string reemplazarVariables(const std::string &expresion) const {
        std::string resultado = expresion;
        for (const auto &var : variables) {
            std::regex varRegex("\\b" + var.nombre + "\\b");
            resultado = std::regex_replace(resultado, varRegex, std::to_string(var.valor));
        }
        return resultado;
    }

    void insertarVariable(const std::string &cadena) {
        std::string linea = cadena;

        linea.erase(std::remove_if(linea.begin(), linea.end(), ::isspace), linea.end());

        std::istringstream stream(linea);
        std::string nombre;
        double valor;

        if (std::getline(stream, nombre, '=') && stream >> valor) {
            // Verificar si el nombre ya existe en las constantes
            if (!constantes.validarNombre(nombre)) {
                std::stringstream ss;
                ss << "Error: El nombre '" << nombre << "' está definido como constante y no se puede modificar.";
                show_alert(ss.str());
                return;
            }

            // Verificar si el nombre ya existe en las variables
            auto it = std::find_if(variables.begin(), variables.end(),
                                   [&nombre](const Variable &v) { return v.nombre == nombre; });

            if (it != variables.end()) {
                // Actualizar el valor de la variable existente
                it->valor = valor;
            } else {
                // Insertar nueva variable
                Variable var = {nombre, valor};
                variables.push_back(var);
            }
        } else {
            std::stringstream ss;
            ss << "Formato de cadena incorrecto: " << cadena;
            show_alert(ss.str());
        }
    }

    void imprimirVariables() const {
        for (const auto &var : variables) {
            std::cout << "Nombre: " << var.nombre << ", Valor: " << var.valor << std::endl;
        }
    }

    const char *obtenerCadenaDeVariables() const {
        std::stringstream ss;
        for (const auto &var : variables) {
            ss << var.nombre << "=" << var.valor << "\n";
        }
        cadenaDeVariables = ss.str();
        return cadenaDeVariables.c_str();
    }

private:
    std::vector<Variable> variables;
    std::unordered_map<std::string, double> variablesMap;
    mutable std::string cadenaDeVariables;

    Constantes constantes;
    GtkWidget *mainWindow;
};

#endif // VARIABLES_H
