#include "utiles.h"
#include <iostream>
#include <fstream>

// Convierte a mayúsculas y elimina caracteres que no sean letras A-Z
std::string limpiarTexto(const std::string& textoEntrada) {
    std::string textoLimpio = "";
    // Recorre cada carácter del texto de entrada
    for (size_t i = 0; i < textoEntrada.size(); i++) {
        char c = textoEntrada[i];
        if (c >= 'a' && c <= 'z') c -= 32; // Convertir a MAYÚSCULA
        if (c >= 'A' && c <= 'Z') textoLimpio += c; // Solo guarda letras válidas
    }
    return textoLimpio;
}

// Añade espacio cada 5 letras para formato militar (WRTXA ZMCHH OXQ)
std::string agruparEnBloquesDeCinco(const std::string& texto) {
    std::string resultado = "";
    // Recorre el texto letra por letra
    for (size_t i = 0; i < texto.size(); i++) {
        resultado += texto[i];           // Añade la letra
        if ((i + 1) % 5 == 0 && i + 1 < texto.size()) {
            resultado += " ";            // Espacio cada 5 letras
        }
    }
    return resultado;
}

// Guarda texto en archivo .txt - devuelve true si funciona
bool guardarTexto(std::string nombreArchivo, std::string texto) {
    std::ofstream archivo(nombreArchivo);  // Abre archivo para escribir
    if (!archivo) return false;            // Si falla la apertura, devuelve false
    archivo << texto;                      // Escribe el texto
    archivo.close();                       // Cierra el archivo
    return true;                           // Todo OK
}

// Lee contenido de archivo .txt - devuelve true si funciona
bool leerTexto(std::string nombreArchivo, std::string& contenido) {
    std::ifstream archivo(nombreArchivo);  // Abre archivo para leer
    if (!archivo) return false;            // Si no existe, devuelve false
    contenido = "";                        // Limpia contenido anterior
    std::string linea;
    // Lee línea por línea hasta el final del archivo
    while (std::getline(archivo, linea)) {
        contenido += linea;
    }
    archivo.close();                       // Cierra el archivo
    return true;                           // Todo OK
}

// Muestra mensaje de éxito con formato [OK]
void mostrarOK(const std::string& mensaje) {
    std::cout << "[OK] " << mensaje << std::endl;
}

// Muestra mensaje de error con formato [ERROR]
void mostrarError(const std::string& mensaje) {
    std::cout << "[ERROR] " << mensaje << std::endl;
}
