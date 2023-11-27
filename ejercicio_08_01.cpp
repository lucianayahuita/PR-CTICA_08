// Materia: Programaci�n I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creaci�n: 27/11/2023
// Fecha modificaci�n: 27/11/2023
// N�mero de ejericio: 1
// Problema planteado: Escribir un programa con la opci�n de encriptar y de desencriptar un fichero de texto.
//La encriptaci�n consiste en que dado un fichero de texto de entrada genere otro fichero de
//salida de extensi�n <nombre>.COD donde el texto estar� codificado (encriptado).
//Esta codificaci�n consiste en reemplazar cada car�cter por el tercero siguiente seg�n la tabla
//ASCII.
//La opci�n de desencriptado consiste en leer un fichero <nombre>.COD y recuperar la
//informaci�n original.
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const char*ARCHIVO1="ARCHIVOCOD.cod";
const char*ARCHIVO2="ARCHIVODECOD.cod";
int menuop();
void encriptar(const char*ARCHIVO1);
void desencriptar(const char*ARCHIVO1);
int main(){
    do{
        switch(menuop()){
            case 1:encriptar(ARCHIVO1);
            break;
            case 2:desencriptar(ARCHIVO2);
            break;
            case 3:exit(3);
            break;
        }
    }while(menuop()!=3);
}
int menuop(){
    int op;
    cout<<"****************MENU DE OPCIONES*******************"<<endl;
	cout<<"\t\t 1. Encriptar "<<endl;
	cout<<"\t\t 2. Desencriptar"<<endl;
	cout<<"\t\t 3. Salir"<<endl;
	cin>>op;
    return op;
}
void encriptar(const char* ARCHIVO1) {
    std::string mensaje;
    std::cout << "Ingrese el mensaje a encriptar: ";
    std::cin.ignore();
    std::getline(std::cin, mensaje);

    std::ofstream archivoSalida(ARCHIVO1, std::ios::binary);
    if (!archivoSalida.is_open()) {
        std::cerr << "Error al abrir el archivo de salida para encriptar." << std::endl;
        return;
    }
    for (char caracter : mensaje) {
        archivoSalida << std::setw(3) << static_cast<int>(caracter+3);
    }

    std::cout << "Encriptaci�n completada. El mensaje encriptado se encuentra en " << ARCHIVO1 << std::endl;

    archivoSalida.close();
}
void desencriptar(const char *ARCHIVO2)
{
    std::ifstream archivoEntrada(ARCHIVO2, std::ios::binary);
    if (!archivoEntrada.is_open())
    {
        std::cerr << "Error al abrir el archivo de entrada para desencriptar." << std::endl;
        return;
    }
    std::ofstream archivoSalida("ARCHIVODECOD.cod", std::ios::binary);
    if (!archivoSalida.is_open())
    {
        std::cerr << "Error al abrir el archivo de salida para desencriptar." << std::endl;
        archivoEntrada.close();
        return;
    }
    int valorASCII;
    while (archivoEntrada >> valorASCII)
    {
        archivoSalida.put(static_cast<char>(valorASCII - 3));
    }
    std::cout << "\nDesencriptaci�n completada." << std::endl;
    archivoEntrada.close();
    archivoSalida.close();
}
