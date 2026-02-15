#include "menu.h"
#include <iostream>

void mostrarMenu() {
    std::cout << "============================" << std::endl;
    std::cout << "        MAQUINA ENIGMA      " << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "1. Cifrar mensaje" << std::endl;
    std::cout << "2. Descifrar mensaje" << std::endl;
    std::cout << "3. Editar rotores" << std::endl;
    std::cout << "4. Salir" << std::endl;
    std::cout << "Elige una opcion: ";
}

int leerOpcionMenu() {
    int opcion = 0;
    std::cin >> opcion;
    return opcion;
}

void pedirVentanasIniciales(char ventanas[3]) {
    std::cout << "Introduce las 3 letras de ventana (por ejemplo A C B):" << std::endl;
    std::cin >> ventanas[0] >> ventanas[1] >> ventanas[2];
}

void pedirTextoOriginal(std::string& texto) {
    std::cout << "Escribe el mensaje a procesar:" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, texto);
}

int pedirNumeroRotor() {
    int numero = 0;
    std::cout << "Que rotor quieres editar? (1, 2 o 3): ";
    std::cin >> numero;
    return numero;
}