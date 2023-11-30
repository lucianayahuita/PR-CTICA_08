// Materia: Programaci�n I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creaci�n: 27/11/2023
// Fecha modificaci�n: 29/11/2023
// N�mero de ejericio: 1
// Problema planteado: Escribir un programa con la opci�n de encriptar y de desencriptar un fichero de texto.
//La encriptaci�n consiste en que dado un fichero de texto de entrada genere otro fichero de
//salida de extensi�n <nombre>.COD donde el texto estar� codificado (encriptado).
//Esta codificaci�n consiste en reemplazar cada car�cter por el tercero siguiente seg�n la tabla
//ASCII.
//La opci�n de desencriptado consiste en leer un fichero <nombre>.COD y recuperar la
//informaci�n original.
#include<iostream>
#include<fstream>
#include<wchar.h>
#include<cstring>
using namespace std;
const char* archivoTexto = "mensaje.txt";
const char* archivoCodigo = "codigo.COD";
void ingresarPalabra();
void encriptar();
void desencriptar();
int menu();
int main() {
    do {
        switch(menu()) {
            case 1:
            ingresarPalabra();
            break;
            case 2:
            desencriptar();
            break;
            case 3:
            exit(3);
            break;
        }
    } while(menu() != 3);

    return 0;
}
int menu() {
    int opcion;
    cout << "***********************MENU DE OPCIONES******************************+" << endl;
    cout << "\t 1. Encriptar un mensaje" << endl;
    cout << "\t 2. Desencriptar un archivo codificado" << endl;
    cout << "\t 3. Salir del sistema" << endl;
    cin >> opcion;
    return opcion;
}
void ingresarPalabra() {
    string mensaje;
    ofstream archivoTextoSalida;
    cout << "Ingrese la palabra: ";
    cin.ignore();
    getline(cin, mensaje);
    archivoTextoSalida.open(archivoTexto, ios::app);
    archivoTextoSalida << mensaje;
    archivoTextoSalida.close();
    encriptar();
}
void encriptar() {
    ifstream archivoTextoEntrada;
    ofstream archivoCodigoSalida;
    char caracter;
    archivoTextoEntrada.open(archivoTexto);
    archivoCodigoSalida.open(archivoCodigo, ios::app);
    while (archivoTextoEntrada.get(caracter)) {
        caracter = caracter + 3;
        archivoCodigoSalida.put(caracter);
    }
    archivoTextoEntrada.close();
    archivoCodigoSalida.close();
    cout << "Archivo encriptado" << endl;
}
void desencriptar() {
    ifstream archivoCodigoEntrada;
    archivoCodigoEntrada.open(archivoCodigo);
    string mensaje;
    char caracter;
    while (archivoCodigoEntrada.get(caracter)) {
        caracter = caracter - 3;
        mensaje += caracter;
    }
    archivoCodigoEntrada.close();
    cout << "El c�digo desencriptado es: " << mensaje << endl;
}

