// Materia: Programación I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creación: 27/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 9
// Problema planteado: Dado una tabla grabada en un fichero en formato binario <nombre>.BIN hallar la suma
//horizontal y vertical y grabar la tabla y los resultados en otro fichero de texto o binario según se
//introduzca por pantalla.
#include <iostream>
#include <fstream>
#include <iomanip>
const char*ARCHIVOBIN="FICHEROBINARIO.bin";
const char*ARCHIVOTEXTO="RESULTADOS.txt";
void introducirtabla(const char*ARCHIVOBIN);
void calcularsumas(const char*ARCHIVOTEXTO);
int main(){
    introducirtabla(ARCHIVOBIN);
    calcularsumas(ARCHIVOTEXTO);
}
void introducirtabla(const char*ARCHIVOBIN){
    int cantFilas, cantColumnas;
    std::cout << "Ingrese la cantidad de filas para su archivo: ";
    std::cin >> cantFilas;
    std::cout << "Ingrese la cantidad de columnas para su archivo: ";
    std::cin >> cantColumnas;
    double m[cantFilas][cantColumnas];
    std::ofstream archivoBinario(ARCHIVOBIN, std::ios::binary);
    if (!archivoBinario.is_open()) {
        std::cerr << "Error al abrir el archivo binario para escritura." << std::endl;
        return;
    }
    archivoBinario.write(reinterpret_cast<const char*>(&cantFilas), sizeof(cantFilas));
    archivoBinario.write(reinterpret_cast<const char*>(&cantColumnas), sizeof(cantColumnas));
    for (int i = 0; i < cantFilas; i++) {
        for (int j = 0; j < cantColumnas; j++) {
            std::cout << "Ingrese el número decimal para la fila " << i + 1 << " y columna " << j + 1 << ": ";
            std::cin >> m[i][j];
            archivoBinario.write(reinterpret_cast<const char*>(&m[i][j]), sizeof(m[i][j]));
        }
    }
    archivoBinario.close();
    std::cout << "Se ha completado la escritura en el archivo binario." << std::endl;
}
void calcularsumas(const char* ARCHIVOTEXTO) {
    std::ifstream archivoBinario(ARCHIVOBIN, std::ios::binary);
    if (!archivoBinario.is_open()) {
        std::cerr << "Error al abrir el archivo binario para lectura." << std::endl;
        return;
    }
    int cantFilas, cantColumnas;
    archivoBinario.read(reinterpret_cast<char*>(&cantFilas), sizeof(cantFilas));
    archivoBinario.read(reinterpret_cast<char*>(&cantColumnas), sizeof(cantColumnas));
    double m[cantFilas][cantColumnas];
    for (int i = 0; i < cantFilas; i++) {
        for (int j = 0; j < cantColumnas; j++) {
            archivoBinario.read(reinterpret_cast<char*>(&m[i][j]), sizeof(m[i][j]));
        }
    }
    archivoBinario.close();
    double sumasFilas[cantFilas] = {0.0};
    double sumasColumnas[cantColumnas] = {0.0};

    for (int i = 0; i < cantFilas; i++) {
        for (int j = 0; j < cantColumnas; j++) {
            sumasFilas[i] += m[i][j];
            sumasColumnas[j] += m[i][j];
        }
    }
    std::ofstream archivoTexto(ARCHIVOTEXTO);
    if (!archivoTexto.is_open()) {
        std::cerr << "Error al abrir el archivo de texto para escritura." << std::endl;
        return;
    }
    for (int i = 0; i < cantFilas; i++) {
        for (int j = 0; j < cantColumnas; j++) {
            archivoTexto << std::fixed << std::setprecision(2) << std::setw(7) << m[i][j] << " ";
        }

    // Calcular e imprimir suma de la fila junto a la fila
    double sumaFila = 0.0;
    for (int j = 0; j < cantColumnas; j++) {
        sumaFila += m[i][j];
    }
    archivoTexto << "  Suma fila " << i + 1 << ": " << std::fixed << std::setprecision(2) << sumaFila;

    archivoTexto << std::endl;
    }

    // Imprimir línea separadora
    for (int j = 0; j < cantColumnas; j++) {
        archivoTexto << "-------";
    }
    archivoTexto << std::endl;

    // Imprimir sumas de columnas debajo de cada columna
    for (int j = 0; j < cantColumnas; j++) {
        double sumaColumna = 0.0;
        for (int i = 0; i < cantFilas; i++) {
            sumaColumna += m[i][j];
        }
        archivoTexto << std::fixed << std::setprecision(2) << std::setw(7) << sumaColumna << " ";
    }

    archivoTexto << std::endl;
    // Imprimir suma total de todas las columnas
    double sumaTotalColumnas = 0.0;
    for (int j = 0; j < cantColumnas; j++) {
        sumaTotalColumnas += sumasColumnas[j];
    }
    archivoTexto << "                 : " << std::fixed << std::setprecision(2) << sumaTotalColumnas;

    archivoTexto << std::endl;
    archivoTexto.close();
    std::cout << "Resultados escritos en el archivo de texto." << std::endl;
}
