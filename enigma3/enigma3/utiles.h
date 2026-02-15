#pragma once
// utiles.h - funciones para limpiar texto y mostrar mensajes

#include <string>

std::string limpiarTexto(const std::string& textoEntrada);
std::string agruparEnBloquesDeCinco(const std::string& texto);
void mostrarOK(const std::string& mensaje);
void mostrarError(const std::string& mensaje);
