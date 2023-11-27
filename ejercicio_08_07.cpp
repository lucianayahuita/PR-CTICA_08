// Materia: Programación I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creación: 27/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 7
// Problema planteado: Escriba un programa que tenga como entrada un fichero que contenga un texto y dé como
//resultado una estadística del número de palabras
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
const char* ARCHIVO="Texto.txt";
void escribirArchivo(const char*ARCHIVO);
void contadorPalabras(const char*ARCHIVO);
int main(){
    escribirArchivo(ARCHIVO);
    contadorPalabras(ARCHIVO);
}
void escribirArchivo(const char*ARCHIVO){
    ofstream archivoSalida(ARCHIVO);
    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo para escritura."<<endl;
        return;
    }
    string linea;
    while (true) {
        cout << "Ingrese una linea de texto (ingrese '0' para salir): ";
        getline(cin,linea);
        if (linea == "0") {
            break;
        }
        archivoSalida << linea << endl;
    }
    archivoSalida.close();
    cout << "Se ha completado la escritura en el archivo." <<endl;
}
void contadorPalabras(const char*ARCHIVO){
    ifstream archivoEntrada(ARCHIVO);
    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }
    string palabra;
    int contadorPalabras = 0;
    while (archivoEntrada >> palabra) {
        contadorPalabras++;
    }
    archivoEntrada.close();
    cout << "Estadisticas del archivo '" << ARCHIVO << "':" << endl;
    cout << "Número total de palabras: " << contadorPalabras << endl;
}
