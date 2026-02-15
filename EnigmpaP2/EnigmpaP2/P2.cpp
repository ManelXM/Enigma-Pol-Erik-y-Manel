#include "enigma.h"

/**
 * AVANCE DE ROTORS: El primer rotor avanza siempre.
 * El segundo y tercero avanzan si el anterior llega a su letra_clave[cite: 35, 36, 37].
 */
void avanzarRotores(Rotor& r1, Rotor& r2, Rotor& r3) {
    // Verificamos si el rotor 1 está en su letra_clave antes de moverlo
    bool pasoLetraClaveR1 = (r1.cadena_de_letras[r1.posicion] == r1.letra_clave);

    // El primer rotor (rápido) siempre gira 1 paso [cite: 35, 103]
    r1.posicion = (r1.posicion + 1) % 26;

    // Si R1 alcanzó su letra_clave, gira el segundo rotor (medio) [cite: 36]
    if (pasoLetraClaveR1) {
        bool pasoLetraClaveR2 = (r2.cadena_de_letras[r2.posicion] == r2.letra_clave);
        r2.posicion = (r2.posicion + 1) % 26;

        // Si R2 alcanzó su letra_clave, gira el tercer rotor (lento) [cite: 37]
        if (pasoLetraClaveR2) {
            r3.posicion = (r3.posicion + 1) % 26;
        }
    }
}

/**
 * CIFRADO: La letra entra por R1, luego R2 y finalmente R3[cite: 38].
 */
char cifrarLetra(char lletra, Rotor& r1, Rotor& r2, Rotor& r3) {
    // El avance ocurre antes de que la señal eléctrica pase por los rotores
    avanzarRotores(r1, r2, r3);

    // Convertimos la letra A-Z a índice 0-25
    int num = lletra - 'A';

    // Paso por Rotor 1 -> Rotor 2 -> Rotor 3
    // La fórmula aplica la sustitución según la cadena_de_letras y la posición actual
    num = (r1.cadena_de_letras[(num + r1.posicion) % 26] - 'A' - r1.posicion + 26) % 26;
    num = (r2.cadena_de_letras[(num + r2.posicion) % 26] - 'A' - r2.posicion + 26) % 26;
    num = (r3.cadena_de_letras[(num + r3.posicion) % 26] - 'A' - r3.posicion + 26) % 26;

    return (char)(num + 'A');
}

/**
 * DESCIFRADO: Usa el cableado inverso y orden inverso (R3 -> R2 -> R1).
 */
char descifrarLetra(char lletra, Rotor& r1, Rotor& r2, Rotor& r3) {
    // El avance debe ser idéntico al del cifrado para mantener la sincronía [cite: 59]
    avanzarRotores(r1, r2, r3);

    int num = lletra - 'A';

    // Función auxiliar para buscar qué letra del alfabeto produce la letra de entrada
    auto buscarInverso = [](int n, Rotor& r) {
        // Buscamos qué letra está "viendo" el rotor en esa posición
        char letraBuscada = (char)(((n + r.posicion) % 26) + 'A');

        // Encontramos la posición de esa letra en la cadena_de_letras (búsqueda inversa)
        int encontrada = r.cadena_de_letras.find(letraBuscada);

        // Ajustamos por el giro del rotor
        return (encontrada - r.posicion + 26) % 26;
        };

    // Para desxifrar, pasamos en orden inverso: 3 -> 2 -> 1 
    num = buscarInverso(num, r3);
    num = buscarInverso(num, r2);
    num = buscarInverso(num, r1);

    return (char)(num + 'A');
}