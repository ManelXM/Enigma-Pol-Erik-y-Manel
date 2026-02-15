#pragma once
#ifndef ENIGMA_H
#define ENIGMA_H

#include <string>

// Estructura simplificada para representar cada rotor
struct Rotor {
    std::string cadena_de_letras; // Permutación de 26 letras (wiring) [cite: 69]
    char letra_clave;             // Letra de muesca o salto (notch) [cite: 71]
    int posicion;                 // Posición actual de la ventana (0-25) [cite: 76]
};

// --- Funciones lógicas del núcleo ---

// Gestiona el giro de los rotores [cite: 33]
void avanzarRotores(Rotor& r1, Rotor& r2, Rotor& r3);

// Cifrado pasando por los rotores 1, 2 y 3 [cite: 38]
char cifrarLetra(char lletra, Rotor& r1, Rotor& r2, Rotor& r3);

// Descifrado pasando por los rotores en orden inverso 3, 2 y 1 
char descifrarLetra(char lletra, Rotor& r1, Rotor& r2, Rotor& r3);

#endif