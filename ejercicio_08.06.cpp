// Materia: Programación I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creación: 26/11/2023
// Fecha modificación: 29/11/2023
// Número de ejericio: 6
// Problema planteado: Escriba un programa que tome como entrada el fichero del ejercicio 4 y una condición sobre el
//campo Precio. La condición podrá ser:
//Precio mayo o igual a 100 o cualquier otro dato ingresado por teclado.
//Este programa debe generar como salida un fichero llamado "salida.dat" que contenga todos
//aquellos artículos para los que se cumple la condición de entrada.
//Mostrar el archivo de salida “salida.dat”
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const char* ARCHIVO = "ALMACEN.bin";
const char* TEMPORAL = "ARCHIVOTEMPORAL.bin";
const char* SALIDA = "salida.dat";
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
void filtrarPorPrecio(float precioLimite);
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
    ofstream archivoTemporal(TEMPORAL, ios::binary);
    for (const auto &item : datos) {
        archivoTemporal.write((char*)&item, sizeof(structalmacen));
    }
    archivoTemporal.close();
    leerarchivobinario();
    float precioLimite;
    cout << "\nIngrese el limite de precio para filtrar: ";
    cin >> precioLimite;
    filtrarPorPrecio(precioLimite);
    cout << "\nLos artículos que cumplen la condicion se han guardado en el archivo 'salida.dat'" << endl;
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
void filtrarPorPrecio(float precioLimite) {
    ifstream archivoLectura(TEMPORAL, ios::in | ios::binary);
    ofstream archivoSalida(SALIDA, ios::binary);

    if (!archivoLectura || !archivoSalida) {
        cerr << "Error al abrir archivos para filtrar." << endl;
        return;
    }
    structalmacen almacen;
    while (archivoLectura.read((char*)&almacen, sizeof(structalmacen))) {
        if (almacen.precio >= precioLimite) {
            archivoSalida.write((char*)&almacen, sizeof(structalmacen));
        }
    }
    archivoLectura.close();
    archivoSalida.close();
}

