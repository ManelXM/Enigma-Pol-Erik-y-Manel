#include "utiles.h"
#include <iostream>
#include <fstream>

// Convierte a mayúsculas y elimina caracteres que no sean letras
std::string limpiarTexto(const std::string& textoEntrada) {
    std::string textoLimpio = "";
    for (char c : textoEntrada) {
        if (c >= 'a' && c <= 'z') c -= 32; // Convertir a MAYUS
        if (c >= 'A' && c <= 'Z') textoLimpio += c;
    }
    return textoLimpio;
}

// Añade un espacio cada 5 letras para formato militar
std::string agruparEnBloquesDeCinco(const std::string& texto) {
    std::string resultado = "";
    for (int i = 0; i < (int)texto.size(); i++) {
        if (i > 0 && i % 5 == 0) resultado += " ";
        resultado += texto[i];
    }
    return resultado;
}

// Guarda un string en un archivo .txt
bool guardarTexto(std::string nombreArchivo, std::string texto) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo) return false;
    archivo << texto;
    return true;
}

// Lee el contenido de un archivo .txt
bool leerTexto(std::string nombreArchivo, std::string& contenido) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo) return false;
    std::getline(archivo, contenido);
    return true;
}

void mostrarOK(const std::string& mensaje) { std::cout << "[OK] " << mensaje << std::endl; }
void mostrarError(const std::string& mensaje) { std::cout << "[ERROR] " << mensaje << std::endl; }