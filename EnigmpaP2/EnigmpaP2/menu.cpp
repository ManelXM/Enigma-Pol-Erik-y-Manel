#include "menu.h"
#include <iostream>

void mostrarMenu() {
    std::cout << "\n============================" << std::endl;
    std::cout << "      MAQUINA ENIGMA        " << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "1. Cifrar mensaje y guardar" << std::endl;
    std::cout << "2. Descifrar desde archivo" << std::endl;
    std::cout << "3. Editar rotores (Config)" << std::endl;
    std::cout << "4. Salir" << std::endl;
    std::cout << "Elige una opcion: ";
}

int leerOpcionMenu() {
    int opcion;
    std::cin >> opcion;
    return opcion;
}

void pedirVentanasIniciales(char ventanas[3]) {
    std::cout << "Introduce las 3 letras de posicion (ej: A B C): ";
    for (int i = 0; i < 3; i++) std::cin >> ventanas[i];
}

void pedirTextoOriginal(std::string& texto) {
    std::cout << "Introduce el mensaje: ";
    std::cin.ignore();
    std::getline(std::cin, texto);
}

int pedirNumeroRotor() {
    int n;
    std::cout << "Que rotor quieres editar? (1-3): ";
    std::cin >> n;
    return n;
}