// Materia: Programaci�n I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creaci�n: 26/11/2023
// Fecha modificaci�n: 27/11/2023
// N�mero de ejericio: 4
// Problema planteado: Codifique un programa que cree un fichero para contener los datos relativos a los art�culos de
//un almac�n.
//Para cada art�culo habr� de guardar la siguiente informaci�n:
//� C�digo del art�culo (Num�rico)
//� Nombre del art�culo (Cadena de caracteres)
//� Existencias actuales (Num�rico)
//� Precio (Num�rico decimal).
//Se deber�n pedir datos de cada art�culo por teclado hasta que como c�digo se teclee el c�digo
//0.
//El fichero se habr� de crear ordenado por el c�digo del art�culo.
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const char* ARCHIVO = "ALMACEN.bin";
const char* TEMPORAL = "ARCHIVOTEMPORAL.bin";
struct structalmacen {
    int codigo;
    char nombrearticulo[20];
    int existenciasactuales;
    float precio;
};
structalmacen ingresardatosalmacen();
void escribirarchivobinario(structalmacen);
void leerarchivobinario();
bool compararPorCodigo(const structalmacen &a, const structalmacen &b);
int main() {
    vector<structalmacen> datos;
    while (true) {
        structalmacen almacen = ingresardatosalmacen();
        if (almacen.codigo == 0) {
            break;
        }
        datos.push_back(almacen);
    }
    sort(datos.begin(), datos.end(), compararPorCodigo);
    // Escribir los datos ordenados en un archivo temporal
    ofstream archivoTemporal(TEMPORAL, ios::binary);
    for (const auto &item : datos) {
        archivoTemporal.write((char*)&item, sizeof(structalmacen));
    }
    archivoTemporal.close();
    leerarchivobinario();
    return 0;
}
structalmacen ingresardatosalmacen() {
    structalmacen almacen;
    cout << "***************INGRESO DE DATOS**********************" << endl;
    cout << "Ingrese el codigo del articulo (Ingrese 0 si desea salir): ";
    cin >> almacen.codigo;
    if (almacen.codigo == 0) {
        return almacen;
    }
    cin.ignore();
    cout << "Ingrese el nombre del articulo: ";
    cin.getline(almacen.nombrearticulo, 20);
    cout << "Ingrese las existencias actuales del articulo: ";
    cin >> almacen.existenciasactuales;
    cout << "Ingrese el precio del articulo: ";
    cin >> almacen.precio;
    return almacen;
}

void escribirarchivobinario(structalmacen almacen) {
    ofstream archivoEscritura(ARCHIVO, ios::app | ios::binary);
    archivoEscritura.write((char*)&almacen, sizeof(structalmacen));
    archivoEscritura.close();
}
bool compararPorCodigo(const structalmacen &a, const structalmacen &b) {
    return a.codigo < b.codigo;
}
void leerarchivobinario() {
    ifstream archivoLectura(TEMPORAL, ios::in | ios::binary);
    if (!archivoLectura) {
        cerr << "Error al abrir el archivo temporal." << endl;
        return;
    }
    structalmacen almacen;
    cout << "\nLISTADO DE DATOS ORDENADOS POR C�DIGO" << endl;
    cout << "=====================================" << endl;
    while (archivoLectura.read((char*)&almacen, sizeof(structalmacen))) {
        cout << "\tCodigo del articulo: " << almacen.codigo << endl;
        cout << "\tNombre del articulo: " << almacen.nombrearticulo << endl;
        cout << "\tExistencias actuales: " << almacen.existenciasactuales << endl;
        cout << "\tPrecio: " << almacen.precio << endl;
        cout << "----------------------" << endl;
    }
    archivoLectura.close();
}


