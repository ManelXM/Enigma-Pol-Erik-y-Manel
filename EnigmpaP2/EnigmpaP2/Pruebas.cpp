#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// --- CLASE ROTOR (Representa cada disco de la máquina) ---
class Rotor {
private:
    string cableado; // Las 26 letras mezcladas [cite: 26, 69]
    char muesca;     // Letra que hace girar al siguiente rotor (notch) [cite: 36, 71]
    int posicion;   // Posición actual del rotor (0-25) [cite: 27]

public:
    Rotor() : cableado("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), muesca('Z'), posicion(0) {}

    // Comprueba si el cableado tiene 26 letras únicas de la A a la Z [cite: 95, 111]
    static bool esValido(const string& texto) {
        if (texto.length() != 26) return false;
        set<char> letras;
        for (char c : texto) {
            if (c < 'A' || c > 'Z') return false;
            letras.insert(c);
        }
        return letras.size() == 26;
    }

    // Carga la configuración desde el fichero (cableado y muesca) [cite: 67, 68]
    bool cargarDesdeFichero(const string& nombreFichero) {
        ifstream archivo(nombreFichero);
        if (!archivo.is_open()) return false;

        string linea1, linea2;
        if (!(archivo >> linea1)) return false;
        if (!(archivo >> linea2)) muesca = 'Z'; // Si no hay muesca, por defecto es Z [cite: 73]
        else muesca = linea2[0];

        if (!esValido(linea1)) return false;
        cableado = linea1;
        return true;
    }

    // Guarda la configuración en el fichero [cite: 110]
    void guardarEnFichero(const string& nombreFichero) {
        ofstream archivo(nombreFichero);
        if (archivo.is_open()) {
            archivo << cableado << "\n" << muesca << "\n";
        }
    }

    void cambiarCableado(const string& nuevo) { cableado = nuevo; }
    void establecerPosicion(char letra) { posicion = toupper(letra) - 'A'; }

    // El rotor gira una posición. Si llega a la muesca, avisa para mover el siguiente [cite: 36, 103]
    bool avanzar() {
        bool activarSiguiente = (cableado[posicion] == muesca);
        posicion = (posicion + 1) % 26;
        return activarSiguiente;
    }

    // Transforma la letra según la posición y el cableado [cite: 38]
    char cifrar(char c) {
        int entrada = (c - 'A' + posicion) % 26;
        char letraTransformada = cableado[entrada];
        int salida = (letraTransformada - 'A' - posicion + 26) % 26;
        return (char)('A' + salida);
    }

    // Hace el proceso inverso para descifrar [cite: 61]
    char descifrar(char c) {
        int entrada = (c - 'A' + posicion) % 26;
        size_t encontrado = cableado.find((char)('A' + entrada));
        int salida = ((int)encontrado - posicion + 26) % 26;
        return (char)('A' + salida);
    }
};

// --- FUNCIONES DE AYUDA ---

// Limpia el texto: solo mayúsculas y quita lo que no sea A-Z [cite: 30, 80, 81]
string limpiarTexto(string sucio) {
    string limpio = "";
    for (char c : sucio) {
        if (isalpha(c)) limpio += toupper(c);
    }
    return limpio;
}

// Separa el texto en grupos de 5 letras para el formato militar [cite: 30, 56, 86]
string formatearTexto(string texto) {
    string resultado = "";
    for (int i = 0; i < (int)texto.length(); ++i) {
        resultado += texto[i];
        if ((i + 1) % 5 == 0 && i != (int)texto.length() - 1) resultado += " ";
    }
    return resultado;
}

// --- LÓGICA PRINCIPAL ---

void ejecutarMaquina(bool modoCifrar) {
    Rotor rotores[3];
    for (int i = 0; i < 3; ++i) {
        string nombre = "Rotor" + to_string(i + 1) + ".txt";
        if (!rotores[i].cargarDesdeFichero(nombre)) {
            cout << "[ERROR] " << nombre << ": Permutacion incorrecta o archivo no encontrado." << endl;
            return;
        }
    }

    char v1, v2, v3;
    cout << "Configuracion de ventana (3 letras, ej: A B C): ";
    cin >> v1 >> v2 >> v3;
    rotores[0].establecerPosicion(v1);
    rotores[1].establecerPosicion(v2);
    rotores[2].establecerPosicion(v3);

    string mensaje;
    cout << "Escribe el mensaje: ";
    cin.ignore();
    getline(cin, mensaje);
    mensaje = limpiarTexto(mensaje);

    string resultado = "";
    for (char letra : mensaje) {
        // 1. Los rotores avanzan (el primero siempre, el resto si hay muesca) [cite: 35, 104]
        if (rotores[0].avanzar()) {
            if (rotores[1].avanzar()) {
                rotores[2].avanzar();
            }
        }

        // 2. La letra pasa por los 3 rotores [cite: 51]
        if (modoCifrar) {
            char p1 = rotores[0].cifrar(letra);
            char p2 = rotores[1].cifrar(p1);
            resultado += rotores[2].cifrar(p2);
        }
        else {
            // El descifrado usa el orden inverso de rotores (3 -> 2 -> 1) [cite: 61]
            char p1 = rotores[2].descifrar(letra);
            char p2 = rotores[1].descifrar(p1);
            resultado += rotores[0].descifrar(p2);
        }
    }

    string textoFinal = formatearTexto(resultado);
    string nombreArchivo = modoCifrar ? "Xifrat.txt" : "desxifrat.txt";

    ofstream archivoSalida(nombreArchivo);
    if (archivoSalida.is_open()) {
        archivoSalida << textoFinal;
        cout << "[OK] Guardado en \"" << nombreArchivo << "\" (" << resultado.length() << " letras)." << endl;
        cout << "Resultado: " << textoFinal << endl;
    }
}

void menuEditarRotores() {
    int id;
    string nuevoCableado;
    cout << "Numero de rotor (1-3): "; cin >> id;
    cout << "Escribe las 26 letras nuevas: "; cin >> nuevoCableado;

    if (Rotor::esValido(nuevoCableado)) {
        Rotor r;
        r.cambiarCableado(nuevoCableado);
        r.guardarEnFichero("Rotor" + to_string(id) + ".txt");
        cout << "[OK] Rotor actualizado." << endl;
    }
    else {
        cout << "[ERROR] Cableado no valido. Debe tener 26 letras de la A a la Z." << endl;
    }
}

int main() {
    int opcion;
    do {
        cout << "\n--- MENU ENIGMA ---" << endl;
        cout << "1. Cifrar mensaje" << endl;
        cout << "2. Descifrar mensaje" << endl;
        cout << "3. Editar rotores" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: ejecutarMaquina(true); break;
        case 2: ejecutarMaquina(false); break;
        case 3: menuEditarRotores(); break;
        }
    } while (opcion != 4);

    return 0;
}