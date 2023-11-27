// Materia: Programación I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creación: 27/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 8
// Problema planteado: Escribir un programa que genere a partir de un fichero de entrada que contiene una tabla de
//números reales otro fichero de salida <nombre>.BIN grabado en formato binario.
#include <iostream>
#include <fstream>
#include <sstream>
const char* MYARCHIVO = "FICHERO1.txt";
const char* ARCHIVOB = "ARCHIVOBIN.bin";
void escribirArchivoDeTexto(const char* MYARCHIVO);
void conversorABinario(const char* ARCHIVOB);
int main() {
    escribirArchivoDeTexto(MYARCHIVO);
    conversorABinario(ARCHIVOB);
    return 0;
}
void escribirArchivoDeTexto(const char* MYARCHIVO) {
    std::ofstream archivoSalida(MYARCHIVO);
    if (!archivoSalida.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }
    int cantFilas, cantColumnas;
    std::cout << "Ingrese la cantidad de filas para su archivo: ";
    std::string filaInput;
    std::getline(std::cin, filaInput);
    std::istringstream(filaInput) >> cantFilas;
    std::cout << "Ingrese la cantidad de columnas para su archivo: ";
    std::string columnaInput;
    std::getline(std::cin, columnaInput);
    std::istringstream(columnaInput) >> cantColumnas;
    double m[cantFilas][cantColumnas];
    for (int i = 0; i < cantFilas; i++) {
        for (int j = 0; j < cantColumnas; j++) {
            std::cout << "Ingrese el número decimal para la fila nro: " << i + 1 << " y columna nro: " << j + 1 << ": ";
            std::string numeroInput;
            std::getline(std::cin, numeroInput);
            std::istringstream(numeroInput) >> m[i][j];
            archivoSalida << m[i][j] << " ";
        }
        archivoSalida << std::endl;
    }
    archivoSalida.close();
    std::cout << "Se ha completado la escritura en el archivo." << std::endl;
}
void conversorABinario(const char* ARCHIVOB) {
    std::ifstream archivoEntrada(MYARCHIVO);
    std::ofstream archivoBinario(ARCHIVOB, std::ios::binary);
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error al abrir el archivo de texto para lectura." << std::endl;
        return;
    }
    if (!archivoBinario.is_open()) {
        std::cerr << "Error al abrir el archivo binario para escritura." << std::endl;
        return;
    }
    double valor;
    while (archivoEntrada >> valor) {
        archivoBinario.write(reinterpret_cast<const char*>(&valor), sizeof(double));
    }
    archivoEntrada.close();
    archivoBinario.close();
    std::cout << "Se ha completado la escritura del archivo binario." << std::endl;
}
