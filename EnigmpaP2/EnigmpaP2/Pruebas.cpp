//#include <iostream>
//#include <fstream>
//#include <string>
//
//struct Rotor {
//    std::string cadena_de_letras;
//    int posicion;
//    char letra_clave;
//};
//
//// --- FUNCIONES DE GESTIÓN DE TEXTO Y ARCHIVOS ---
//
//std::string limpiarTexto(std::string textoOriginal) {
//    std::string textoLimpio = "";
//    for (int i = 0; i < (int)textoOriginal.size(); i++) {
//        char caracter = textoOriginal[i];
//        if (caracter >= 'a' && caracter <= 'z') caracter -= 32;
//        if (caracter >= 'A' && caracter <= 'Z') textoLimpio += caracter;
//    }
//    return textoLimpio;
//}
//
//bool guardarTexto(std::string nombreArchivo, std::string texto) {
//    std::ofstream archivoSalida(nombreArchivo);
//    if (!archivoSalida) return false;
//    archivoSalida << texto;
//    archivoSalida.close();
//    return true;
//}
//
//bool leerTexto(std::string nombreArchivo, std::string& contenido) {
//    std::ifstream archivoEntrada(nombreArchivo);
//    if (!archivoEntrada) return false;
//    std::getline(archivoEntrada, contenido);
//    archivoEntrada.close();
//    return true;
//}
//
//std::string agruparEnBloques(std::string textoLimpio) {
//    std::string textoAgrupado = "";
//    for (int i = 0; i < (int)textoLimpio.size(); i++) {
//        if (i > 0 && i % 5 == 0) textoAgrupado += " ";
//        textoAgrupado += textoLimpio[i];
//    }
//    return textoAgrupado;
//}
//
//// --- FUNCIONES DE LÓGICA ENIGMA ---
//
//void avanzarRotores(Rotor& r1, Rotor& r2, Rotor& r3) {
//    bool r1EnMuesca = (r1.cadena_de_letras[r1.posicion] == r1.letra_clave);
//    r1.posicion = (r1.posicion + 1) % 26;
//    if (r1EnMuesca) {
//        bool r2EnMuesca = (r2.cadena_de_letras[r2.posicion] == r2.letra_clave);
//        r2.posicion = (r2.posicion + 1) % 26;
//        if (r2EnMuesca) r3.posicion = (r3.posicion + 1) % 26;
//    }
//}
//
//char cifrarLetra(char letra, Rotor& r1, Rotor& r2, Rotor& r3) {
//    avanzarRotores(r1, r2, r3);
//    int num = letra - 'A';
//    num = (r1.cadena_de_letras[(num + r1.posicion) % 26] - 'A' - r1.posicion + 26) % 26;
//    num = (r2.cadena_de_letras[(num + r2.posicion) % 26] - 'A' - r2.posicion + 26) % 26;
//    num = (r3.cadena_de_letras[(num + r3.posicion) % 26] - 'A' - r3.posicion + 26) % 26;
//    return (char)(num + 'A');
//}
//
//char descifrarLetra(char letra, Rotor& r1, Rotor& r2, Rotor& r3) {
//    avanzarRotores(r1, r2, r3);
//    int num = letra - 'A';
//    auto buscarInverso = [](int n, Rotor& r) {
//        char letraBuscada = (char)(((n + r.posicion) % 26) + 'A');
//        int encontrada = r.cadena_de_letras.find(letraBuscada);
//        return (encontrada - r.posicion + 26) % 26;
//        };
//    num = buscarInverso(num, r3);
//    num = buscarInverso(num, r2);
//    num = buscarInverso(num, r1);
//    return (char)(num + 'A');
//}
//
//// --- MAIN CON MENÚ ---
//
//int main() {
//    Rotor R1 = { "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 0, 'Q' };
//    Rotor R2 = { "AJDKSIRUXBLHWTMCQGZNPYFVOE", 0, 'E' };
//    Rotor R3 = { "BDFHJLCPRTXVZNYEIWGAKMUSQO", 0, 'V' };
//
//    int opcion;
//    std::string texto, resultado = "";
//
//    std::cout << "--- MAQUINA ENIGMA ---\n";
//    std::cout << "1. Cifrar mensaje y guardar\n";
//    std::cout << "2. Descifrar mensaje desde archivo\n";
//    std::cout << "Seleccione una opcion: ";
//    std::cin >> opcion;
//    std::cin.ignore(); // Limpiar el buffer
//
//    if (opcion == 1) {
//        std::cout << "Introduce el mensaje a cifrar: ";
//        std::getline(std::cin, texto);
//        std::string limpio = limpiarTexto(texto);
//
//        for (char c : limpio) resultado += cifrarLetra(c, R1, R2, R3);
//
//        if (guardarTexto("missatge.txt", resultado)) {
//            std::cout << "[OK] Mensaje cifrado guardado en missatge.txt\n";
//            std::cout << "Contenido: " << agruparEnBloques(resultado) << "\n";
//        }
//    }
//    else if (opcion == 2) {
//        if (leerTexto("missatge.txt", texto)) {
//            for (char c : texto) resultado += descifrarLetra(c, R1, R2, R3);
//            std::cout << "Mensaje descifrado: " << resultado << "\n";
//        }
//        else {
//            std::cout << "ERROR: No se pudo leer el archivo missatge.txt\n";
//        }
//    }
//    else {
//        std::cout << "Opcion no valida.\n";
//    }
//
//    return 0;
//}
