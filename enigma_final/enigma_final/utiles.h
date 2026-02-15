#pragma once

#ifndef UTILES_H
#define UTILES_H

#include <string>

// Prototipos de funciones de formato
std::string limpiarTexto(const std::string& textoEntrada);
std::string agruparEnBloquesDeCinco(const std::string& texto);
void mostrarOK(const std::string& mensaje);
void mostrarError(const std::string& mensaje);

// Prototipos de persistencia (Archivos)
bool guardarTexto(std::string nombreArchivo, std::string texto);
bool leerTexto(std::string nombreArchivo, std::string& contenido);

#endif
