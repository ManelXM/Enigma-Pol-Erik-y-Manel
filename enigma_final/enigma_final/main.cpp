#include <iostream>
#include <string>
#include "menu.h"
#include "utiles.h"

// Estructura simple para cada rotor (cableado + posición + muesca)
struct Rotor {
    std::string cableado;  // 26 letras permutadas (ej: "EKMFLGDQV...")
    int posicion;          // 0-25, donde está apuntando ahora
    char muesca;           // Letra que hace girar al siguiente rotor
};

// Avanza los rotores (r1 siempre gira, r2 si r1 toca muesca, r3 si r2 toca muesca)
void avanzarRotores(Rotor& r1, Rotor& r2, Rotor& r3) {
    // Comprueba si r1 está en su muesca para girar r2
    bool r1EnMuesca = (r1.posicion == (r1.muesca - 'A'));
    r1.posicion = (r1.posicion + 1) % 26;  // r1 SIEMPRE gira

    if (r1EnMuesca) {
        // Si r1 giró r2, comprueba si r2 está en muesca para girar r3
        bool r2EnMuesca = (r2.posicion == (r2.muesca - 'A'));
        r2.posicion = (r2.posicion + 1) % 26;  // r2 gira
        if (r2EnMuesca) {
            r3.posicion = (r3.posicion + 1) % 26;  // r3 gira
        }
    }
}

// Procesa UNA letra: CIFRAR (adelante) o DESCIFRAR (atrás)
char procesarLetra(char letra, Rotor& r1, Rotor& r2, Rotor& r3, bool cifrar) {
    avanzarRotores(r1, r2, r3);  // Gira rotores ANTES de procesar
    int num = letra - 'A';       // Convierte A=0, B=1, ..., Z=25

    if (cifrar) {
        // CIFRAR: r1 → r2 → r3 (hacia adelante)
        int temp1 = (num + r1.posicion) % 26;
        num = (r1.cableado[temp1] - 'A' - r1.posicion + 26) % 26;

        int temp2 = (num + r2.posicion) % 26;
        num = (r2.cableado[temp2] - 'A' - r2.posicion + 26) % 26;

        int temp3 = (num + r3.posicion) % 26;
        num = (r3.cableado[temp3] - 'A' - r3.posicion + 26) % 26;
    }
    else {
        // DESCIFRAR: r3 → r2 → r1 (hacia atrás, inverso)
        // Busca letra en cableado de r3
        char letraR3 = (char)((num + r3.posicion) % 26 + 'A');
        size_t posR3 = r3.cableado.find(letraR3);
        num = (posR3 - r3.posicion + 26) % 26;

        // Busca en r2
        char letraR2 = (char)((num + r2.posicion) % 26 + 'A');
        size_t posR2 = r2.cableado.find(letraR2);
        num = (posR2 - r2.posicion + 26) % 26;

        // Busca en r1
        char letraR1 = (char)((num + r1.posicion) % 26 + 'A');
        size_t posR1 = r1.cableado.find(letraR1);
        num = (posR1 - r1.posicion + 26) % 26;
    }
    return (char)(num + 'A');  // Convierte número de vuelta a letra
}

int main() {
    // Rotors estándar I, II, III (cableado real + muescas)
    Rotor rotor1 = { "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 0, 'Q' };
    Rotor rotor2 = { "AJDKSIRUXBLHWTMCQGZNPYFVOE", 0, 'E' };
    Rotor rotor3 = { "BDFHJLCPRTXVZNYEIWGAKMUSQO", 0, 'V' };

    bool salir = false;

    while (!salir) {
        mostrarMenu();
        int opcion = leerOpcionMenu();

        if (opcion == 1) {  // CIFRAR
            char ventanas[3];
            pedirVentanasIniciales(ventanas);

            // Configura posiciones iniciales de rotores
            rotor1.posicion = ventanas[0] - 'A';
            rotor2.posicion = ventanas[1] - 'A';
            rotor3.posicion = ventanas[2] - 'A';

            std::string textoOriginal;
            pedirTextoOriginal(textoOriginal);

            std::string textoLimpio = limpiarTexto(textoOriginal);  // Solo A-Z mayúsculas
            std::string textoCifrado = "";

            // Cifra letra por letra
            for (size_t i = 0; i < textoLimpio.size(); i++) {
                textoCifrado += procesarLetra(textoLimpio[i], rotor1, rotor2, rotor3, true);
            }

            // Guarda en Xifrat.txt con formato militar
            std::string textoFormateado = agruparEnBloquesDeCinco(textoCifrado);
            if (guardarTexto("Xifrat.txt", textoFormateado)) {
                int totalLetras = (int)textoCifrado.size();
                int totalGrupos = (totalLetras + 4) / 5;
                mostrarOK("Mensaje cifrado en \"Xifrat.txt\" (" +
                    std::to_string(totalLetras) + " letras, " +
                    std::to_string(totalGrupos) + " grupos)");
                std::cout << "Vista previa: " << textoFormateado << std::endl;
            }
            else {
                mostrarError("No se pudo guardar Xifrat.txt");
            }

        }
        else if (opcion == 2) {  // DESCIFRAR
            char ventanas[3];
            pedirVentanasIniciales(ventanas);

            // Reconfigura rotores a posiciones iniciales
            rotor1.posicion = ventanas[0] - 'A';
            rotor2.posicion = ventanas[1] - 'A';
            rotor3.posicion = ventanas[2] - 'A';

            std::string textoCifradoArchivo;
            if (leerTexto("Xifrat.txt", textoCifradoArchivo)) {
                std::string textoLimpio = limpiarTexto(textoCifradoArchivo);  // Quita espacios
                std::string textoDescifrado = "";

                // Descifra letra por letra
                for (size_t i = 0; i < textoLimpio.size(); i++) {
                    textoDescifrado += procesarLetra(textoLimpio[i], rotor1, rotor2, rotor3, false);
                }

                std::cout << "Texto descifrado: " << textoDescifrado << std::endl;
                mostrarOK("Descifrado completado correctamente");
            }
            else {
                mostrarError("No existe el archivo Xifrat.txt o error de lectura");
            }

        }
        else if (opcion == 3) {  // EDITAR ROTORES
            int numeroRotor = pedirNumeroRotor();
            if (numeroRotor >= 1 && numeroRotor <= 3) {
                std::cout << "Escribe nueva permutacion de 26 letras (ej: EKMFLGDQV...): ";
                std::string nuevaPermutacion;
                std::cin >> nuevaPermutacion;

                // TODO: Validar que tiene exactamente 26 letras únicas A-Z
                if (nuevaPermutacion.size() == 26) {
                    if (numeroRotor == 1) rotor1.cableado = nuevaPermutacion;
                    else if (numeroRotor == 2) rotor2.cableado = nuevaPermutacion;
                    else rotor3.cableado = nuevaPermutacion;
                    mostrarOK("Rotor " + std::to_string(numeroRotor) + " actualizado");
                }
                else {
                    mostrarError("Permutacion debe tener exactamente 26 letras");
                }
            }
            else {
                mostrarError("Numero de rotor invalido (1-3)");
            }

        }
        else if (opcion == 4) {
            salir = true;
            mostrarOK("Saliendo del programa...");
        }
        else {
            mostrarError("Opcion no valida (1-4)");
        }
    }

    return 0;
}
