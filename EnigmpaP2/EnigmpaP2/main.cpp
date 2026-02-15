#include <iostream>
#include <string>
#include "menu.h"
#include "utiles.h"

// Estructura para los rotores de la maquina
struct Rotor {
    std::string cableado;
    int posicion;
    char muesca; // Letra que hace girar al siguiente rotor
};

// --- LOGICA ENIGMA ---

void avanzarRotores(Rotor& r1, Rotor& r2, Rotor& r3) {
    // Si r1 toca su muesca, gira r2. Si r2 toca muesca, gira r3.
    bool r1GiraR2 = (r1.cableado[r1.posicion] == r1.muesca);
    r1.posicion = (r1.posicion + 1) % 26;

    if (r1GiraR2) {
        bool r2GiraR3 = (r2.cableado[r2.posicion] == r2.muesca);
        r2.posicion = (r2.posicion + 1) % 26;
        if (r2GiraR3) r3.posicion = (r3.posicion + 1) % 26;
    }
}

char procesarLetra(char letra, Rotor& r1, Rotor& r2, Rotor& r3, bool cifrar) {
    avanzarRotores(r1, r2, r3);
    int num = letra - 'A';

    if (cifrar) {
        // Paso por los 3 rotores hacia adelante
        num = (r1.cableado[(num + r1.posicion) % 26] - 'A' - r1.posicion + 26) % 26;
        num = (r2.cableado[(num + r2.posicion) % 26] - 'A' - r2.posicion + 26) % 26;
        num = (r3.cableado[(num + r3.posicion) % 26] - 'A' - r3.posicion + 26) % 26;
    }
    else {
        // Paso inverso buscando la letra en el cableado
        auto buscar = [](int n, Rotor& r) {
            char letraBusca = (char)(((n + r.posicion) % 26) + 'A');
            int pos = r.cableado.find(letraBusca);
            return (pos - r.posicion + 26) % 26;
            };
        num = buscar(num, r3);
        num = buscar(num, r2);
        num = buscar(num, r1);
    }
    return (char)(num + 'A');
}

int main() {
    // Configuracion de los rotores originales (I, II, III)
    Rotor R1 = { "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 0, 'Q' };
    Rotor R2 = { "AJDKSIRUXBLHWTMCQGZNPYFVOE", 0, 'E' };
    Rotor R3 = { "BDFHJLCPRTXVZNYEIWGAKMUSQO", 0, 'V' };

    bool salir = false;
    while (!salir) {
        mostrarMenu();
        int opcion = leerOpcionMenu();

        if (opcion == 1 || opcion == 2) {
            char v[3];
            pedirVentanasIniciales(v);
            R1.posicion = v[0] - 'A';
            R2.posicion = v[1] - 'A';
            R3.posicion = v[2] - 'A';

            std::string texto, resultado = "";

            if (opcion == 1) { // CIFRAR
                pedirTextoOriginal(texto);
                std::string limpio = limpiarTexto(texto);
                for (char c : limpio) resultado += procesarLetra(c, R1, R2, R3, true);

                guardarTexto("Xifrat.txt", resultado);
                std::cout << "Resultado: " << agruparEnBloquesDeCinco(resultado) << "\n";
                mostrarOK("Mensaje guardado en Xifrat.txt");
            }
            else { // DESCIFRAR
                if (leerTexto("Xifrat.txt", texto)) {
                    for (char c : texto) resultado += procesarLetra(c, R1, R2, R3, false);
                    std::cout << "Descifrado: " << resultado << "\n";
                    mostrarOK("Lectura completa");
                }
                else {
                    mostrarError("No existe el archivo Xifrat.txt");
                }
            }
        }
        else if (opcion == 3) {
            int r = pedirNumeroRotor();
            r >= 1 && r <= 3 ? mostrarOK("Configurando rotor...") : mostrarError("Rotor invalido");
        }
        else if (opcion == 4) {
            salir = true;
            mostrarOK("Saliendo del sistema...");
        }
    }
    return 0;
}