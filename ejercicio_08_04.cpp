// Materia: Programación I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creación: 26/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 4
// Problema planteado: Codifique un programa que cree un fichero para contener los datos relativos a los artículos de
//un almacén.
//Para cada artículo habrá de guardar la siguiente información:
//• Código del artículo (Numérico)
//• Nombre del artículo (Cadena de caracteres)
//• Existencias actuales (Numérico)
//• Precio (Numérico decimal).
//Se deberán pedir datos de cada artículo por teclado hasta que como código se teclee el código
//0.
//El fichero se habrá de crear ordenado por el código del artículo.
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
    cout << "\nLISTADO DE DATOS ORDENADOS POR CÓDIGO" << endl;
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


