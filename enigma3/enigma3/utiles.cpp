// utiles.cpp - funciones para limpiar texto y mostrar mensajes

#include "utiles.h"
#include <iostream>

std::string limpiarTexto(const std::string& textoEntrada) {
    std::string textoLimpio;

    for (size_t i = 0; i < textoEntrada.size(); i++) {
        char c = textoEntrada[i];

        // pasar a mayusculas
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }

        // solo dejamos A-Z
        if (c >= 'A' && c <= 'Z') {
            textoLimpio += c;
        }
    }

    return textoLimpio;
}

std::string agruparEnBloquesDeCinco(const std::string& texto) {
    std::string resultado;
    int contador = 0;

    for (size_t i = 0; i < texto.size(); i++) {
        resultado += texto[i];
        contador++;

        if (contador == 5 && i + 1 < texto.size()) {
            resultado += ' ';
            contador = 0;
        }
    }

    return resultado;
}

void mostrarOK(const std::string& mensaje) {
    std::cout << "[OK] " << mensaje << std::endl;
}

void mostrarError(const std::string& mensaje) {
    std::cout << "[ERROR] " << mensaje << std::endl;
}
