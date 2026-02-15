#pragma once

#ifndef MENU_H
#define MENU_H

#include <string>

void mostrarMenu();
int leerOpcionMenu();

// devuelve las 3 ventanas como resultado
void pedirVentanasIniciales(char ventanas[3]);
void pedirTextoOriginal(std::string& texto);

int pedirNumeroRotor();

#endif
