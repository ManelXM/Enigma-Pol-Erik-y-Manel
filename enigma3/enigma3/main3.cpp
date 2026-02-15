#include <iostream>
#include <string>
#include "menu.h"
#include "utiles.h"

int main() {
    bool salir = false;

    while (!salir) {
        mostrarMenu();
        int opcion = leerOpcionMenu();

        if (opcion == 1) {
            // CIFRAR - SIN REFERENCIAS
            char ventanas[3];  // array simple de 3 chars
            pedirVentanasIniciales(ventanas);

            std::cout << "Ventanas iniciales: " << ventanas[0]
                << " " << ventanas[1] << " " << ventanas[2] << std::endl;

            // persona 2: configurarRotores(ventanas[0], ventanas[1], ventanas[2]);

            std::string textoOriginal;
            pedirTextoOriginal(textoOriginal);

            std::string textoLimpio = limpiarTexto(textoOriginal);

            std::string textoCifrado;
            for (size_t i = 0; i < textoLimpio.size(); i++) {
                char letra = textoLimpio[i];
                // char letraCifrada = cifrarLetra(letra);  // persona 2
                char letraCifrada = letra; // temporal
                textoCifrado += letraCifrada;
            }

            std::string textoConGrupos = agruparEnBloquesDeCinco(textoCifrado);

            std::cout << "Texto cifrado: " << textoConGrupos << std::endl;

            // persona 1: guardarTexto("Xifrat.txt", textoConGrupos);
            mostrarOK("Mensaje cifrado listo (falta guardar archivo)");

        }
        else if (opcion == 2) {
            // DESCIFRAR - igual de simple
            char ventanas[3];
            pedirVentanasIniciales(ventanas);

            std::string textoCifrado;
            pedirTextoOriginal(textoCifrado);

            std::string textoLimpio = limpiarTexto(textoCifrado);

            std::string textoDescifrado;
            for (size_t i = 0; i < textoLimpio.size(); i++) {
                char letra = textoLimpio[i];
                // char letraDescifrada = descifrarLetra(letra);
                char letraDescifrada = letra;
                textoDescifrado += letraDescifrada;
            }

            std::cout << "Texto descifrado: " << textoDescifrado << std::endl;
            mostrarOK("Mensaje descifrado listo");

        }
        else if (opcion == 3) {
            int rotor = pedirNumeroRotor();
            if (rotor < 1 || rotor > 3) {
                mostrarError("Numero de rotor mal");
            }
            else {
                mostrarOK("Editar rotor " + std::to_string(rotor) + " (falta conectar con persona 1)");
            }

        }
        else if (opcion == 4) {
            salir = true;
            mostrarOK("Hasta luego!");
        }
        else {
            mostrarError("Opcion mal");
        }
    }

    return 0;
}
