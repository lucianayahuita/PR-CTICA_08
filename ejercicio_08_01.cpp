// Materia: Programación I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creación: 27/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 1
// Problema planteado: Escribir un programa con la opción de encriptar y de desencriptar un fichero de texto.
//La encriptación consiste en que dado un fichero de texto de entrada genere otro fichero de
//salida de extensión <nombre>.COD donde el texto estará codificado (encriptado).
//Esta codificación consiste en reemplazar cada carácter por el tercero siguiente según la tabla
//ASCII.
//La opción de desencriptado consiste en leer un fichero <nombre>.COD y recuperar la
//información original.
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

    std::cout << "Encriptación completada. El mensaje encriptado se encuentra en " << ARCHIVO1 << std::endl;

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
    std::cout << "\nDesencriptación completada." << std::endl;
    archivoEntrada.close();
    archivoSalida.close();
}
