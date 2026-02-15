#pragma once
#ifndef ENIGMA_H
#define ENIGMA_H

#include <string>

/**
 * ESTRUCTURA DEL ROTOR
 * Representa un disco físico de la máquina con su cableado interno y su muesca.
 */
struct Rotor {
    std::string cadena_de_letras; // Alfabeto interno desordenado (cableado)
    char letra_clave;             // Letra que activa el giro del siguiente rotor (muesca)
    int posicion;                 // Desfase actual del rotor (índice 0-25)
};

// --- Funciones del Núcleo de la Máquina ---

/**
 * Gestiona el movimiento mecánico de los rotores antes de procesar cada letra.
 */
void avanzarRotores(Rotor& r1, Rotor& r2, Rotor& r3);

/**
 * Realiza el proceso de cifrado: la señal viaja del Rotor 1 al Rotor 3.
 */
char cifrarLetra(char letra, Rotor& r1, Rotor& r2, Rotor& r3);

/**
 * Realiza el proceso de descifrado: la señal viaja en orden inverso (Rotor 3 al 1).
 */
char descifrarLetra(char letra, Rotor& r1, Rotor& r2, Rotor& r3);

#endif