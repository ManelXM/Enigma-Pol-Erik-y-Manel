#include "enigma.h"

/**
 * AVANCE MECÁNICO DE LOS ROTORES
 * Simula el movimiento de los engranajes. El primer rotor avanza con cada tecla.
 * El segundo y tercero solo avanzan cuando el rotor anterior completa un ciclo
 * (llega a su muesca o "letra clave").
 */
void avanzarRotores(Rotor& r1, Rotor& r2, Rotor& r3) {
    // 1. Detectamos si los rotores están en su posición de muesca antes de moverlos
    // Esto es crucial porque la muesca es la que "empuja" al siguiente rotor.
    bool r1EnMuesca = (r1.cadena_de_letras[r1.posicion] == r1.letra_clave);

    // 2. El Rotor 1 (el más rápido) siempre avanza una posición con cada pulsación
    r1.posicion = (r1.posicion + 1) % 26;

    // 3. Si el Rotor 1 activó su muesca, giramos el Rotor 2
    if (r1EnMuesca) {
        bool r2EnMuesca = (r2.cadena_de_letras[r2.posicion] == r2.letra_clave);
        r2.posicion = (r2.posicion + 1) % 26;

        // 4. Si el Rotor 2 también estaba en su muesca, giramos el Rotor 3 (el más lento)
        if (r2EnMuesca) {
            r3.posicion = (r3.posicion + 1) % 26;
        }
    }
}

/**
 * PROCESO DE CIFRADO
 * Transforma una letra pasando la señal eléctrica a través de los tres rotores
 * en el orden: Rotor 1 -> Rotor 2 -> Rotor 3.
 */
char cifrarLetra(char letra, Rotor& r1, Rotor& r2, Rotor& r3) {
    // En la Enigma real, el rotor gira justo antes de que pase la corriente
    avanzarRotores(r1, r2, r3);

    // Normalizamos la letra de entrada (A-Z) a un índice numérico (0-25)
    int num = letra - 'A';

    // PASO POR LOS ROTORES (Ida)
    // Se aplica la sustitución según el cableado interno y la rotación actual.
    // La fórmula compensa el desfase de la posición del rotor para que la entrada sea relativa.
    num = (r1.cadena_de_letras[(num + r1.posicion) % 26] - 'A' - r1.posicion + 26) % 26;
    num = (r2.cadena_de_letras[(num + r2.posicion) % 26] - 'A' - r2.posicion + 26) % 26;
    num = (r3.cadena_de_letras[(num + r3.posicion) % 26] - 'A' - r3.posicion + 26) % 26;

    // Convertimos el índice final de nuevo a carácter A-Z
    return (char)(num + 'A');
}

/**
 * PROCESO DE DESCIFRADO
 * Realiza el camino inverso para recuperar la letra original.
 * El orden de los rotores se invierte: Rotor 3 -> Rotor 2 -> Rotor 1.
 */
char descifrarLetra(char letra, Rotor& r1, Rotor& r2, Rotor& r3) {
    // El avance de rotores debe ser idéntico al del cifrado para mantener la sincronía
    avanzarRotores(r1, r2, r3);

    int num = letra - 'A';

    // Función Lambda para realizar la búsqueda inversa en el cableado del rotor
    // En lugar de ver qué salida da una entrada, buscamos qué entrada daría esa salida.
    auto buscarInverso = [](int n, Rotor& r) {
        // Determinamos qué letra física representa el contacto de salida
        char letraBuscada = (char)(((n + r.posicion) % 26) + 'A');

        // Buscamos en qué posición del cableado (cadena_de_letras) se encuentra esa letra
        int encontrada = r.cadena_de_letras.find(letraBuscada);

        // Ajustamos el índice restando la rotación para obtener la entrada original
        return (encontrada - r.posicion + 26) % 26;
        };

    // PASO POR LOS ROTORES (Vuelta)
    num = buscarInverso(num, r3);
    num = buscarInverso(num, r2);
    num = buscarInverso(num, r1);

    return (char)(num + 'A');
}