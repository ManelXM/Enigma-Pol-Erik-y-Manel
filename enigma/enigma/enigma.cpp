#include <iostream>
#include <fstream>
#include <string>

std::string limpiarTexto(std::string textoOriginal) {

    std::string textoLimpio = "";//variable donde guardaremos el resultado de la transformacion

    for (int i = 0; i < textoOriginal.size(); i++) {//hacemos el for el qual va a recorrer todo el contenido introducido por el usuario 

        char caracter = textoOriginal[i];//cogemos el caracter el qual el for esta recorriendo 

        if (caracter >= 'a' && caracter <= 'z')
            caracter = caracter - 32;//a traves de asscii lo convertimos a mayuscula 

        if (caracter >= 'A' && caracter <= 'Z')
            textoLimpio += caracter;//guardamos el caracter en mayuscula 
    }

    return textoLimpio;//devolvemos el contenido ya convertido a mayusuclas
}


bool guardarTexto(std::string nombreArchivo, std::string texto) {

    std::ofstream archivoSalida(nombreArchivo);//creamos el archivo

    if (!archivoSalida) {
        std::cout << "ERROR al crear archivo\n";//si no se crea mostramos error
        return false;
    }

    archivoSalida << texto;//guardamos el texto dentro del archivo
    archivoSalida.close();//cerramos el archivo

    return true;
}


bool leerTexto(std::string nombreArchivo, std::string& contenido) {

    std::ifstream archivoEntrada(nombreArchivo);//abrimos el archivo

    if (!archivoEntrada) {
        std::cout << "ERROR al abrir archivo\n";//si no se abre mostramos error
        return false;
    }

    std::getline(archivoEntrada, contenido);//leemos todo el contenido del archivo
    archivoEntrada.close();//cerramos el archivo

    return true;
}



std::string agruparEnBloques(std::string textoLimpio) {

    std::string textoAgrupado = "";//variable donde guardaremos el texto separado en bloques

    for (int i = 0; i < textoLimpio.size(); i++) {//recorremos todo el texto limpio

        if (i > 0 && i % 5 == 0)//cada 5 letras añadimos un espacio
            textoAgrupado += " ";

        textoAgrupado += textoLimpio[i];//añadimos la letra
    }

    return textoAgrupado;//devolvemos el texto agrupado
}


int main() {

    std::string mensajeOriginal;
    std::string contenidoArchivo;
    std::string mensajeAgrupado;


    std::cout << "Introduce mensaje: ";//Pedimos al usuario el mensaje a cifrar 
    std::getline(std::cin, mensajeOriginal);//lo cogemos de mensaje original

    std::string mensajeLimpio = limpiarTexto(mensajeOriginal);//convertimos mensaje que nos ha dado anteriormente y lo pasamos a mayusuclas

    // El error estaba en que guardabas mensajeLimpio pero no mostrabas la version agrupada
    if (guardarTexto("missatge.txt", mensajeLimpio))//guardamos el mensaje limpio en archivo
        std::cout << "[OK] Guardado en missatge.txt\n";//mensaje de confirmacion

    if (leerTexto("missatge.txt", contenidoArchivo)) {//leemos el archivo para comprobar
        std::cout << "Contenido archivo: " << contenidoArchivo << std::endl;//mostramos lo que hay dentro

        // Ahora sí usamos tu función y guardamos el resultado
        mensajeAgrupado = agruparEnBloques(contenidoArchivo);//agrupamos en bloques de 5
        std::cout << "Mensaje agrupado: " << mensajeAgrupado << std::endl; // Mostramos el resultado final
    }

    return 0;
}