// Materia: Programación I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creación: 26/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 2
// Problema planteado: Escriba un programa que cree un fichero de texto llamado "PERSONAS.BIN" en el que se
//guarde la información de un número indeterminado de personas.
//La información que se guardará por cada persona será:
//• Nombre: De 1 a 30 caracteres.
//• Edad numérico (>= 1 y <=100)
//• Sexo CHAR (M/F).
//• FechaNacimiento CHAR(10) (formato dd/mm/yyyy)
//La información correspondiente a cada persona se leerá del teclado.
//El proceso finalizará cuando se teclee un campo "Nombre" que esté solamente con el carácter
//de espacio.
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const char* ARCHIVO = "PERSONAS.bin";
struct structpersona {
    char nombre[30];
    char sexo[2];
    char fechadenacimiento[11];
    int edad;
};
structpersona ingresardatospersona();
void escribirarchivobinario(structpersona);
void leerarchivobinario();
int main() {
    while(true){
        structpersona persona = ingresardatospersona();
        // Verificar si el nombre contiene solo espacios para salir
        if(strlen(persona.nombre)==0||strspn(persona.nombre," ")==strlen(persona.nombre)){
            break;
        }
        escribirarchivobinario(persona);
    }
    leerarchivobinario();
    return 0;
}
structpersona ingresardatospersona() {
    structpersona persona;
    cout<<"Ingreso de datos"<<endl;
    cout<<"Ingrese su nombre (o espacio para salir): ";
    cin.getline(persona.nombre, 30);
    // Verificar si el nombre contiene solo espacios para salir
    if (strlen(persona.nombre)==0||strspn(persona.nombre, " ")==strlen(persona.nombre)){
        return persona;
    }
    cout << "Ingrese su sexo: ";
    cin.getline(persona.sexo, 2);
    do{
        cout<<"Ingrese su edad: ";
        cin>>persona.edad;
        if (persona.edad>=1 && persona.edad<=100){
            break;
        }
    }while(true);
    cin.ignore();
    cout<<"Ingrese su fecha de nacimiento (DD/MM/YYYY): ";
    cin.getline(persona.fechadenacimiento, 11);
    return persona;
}

void escribirarchivobinario(structpersona persona) {
    ofstream archivoEscritura;
    archivoEscritura.open(ARCHIVO, ios::app | ios::binary);
    archivoEscritura.write((char*)&persona, sizeof(structpersona));
    archivoEscritura.close();
}
void leerarchivobinario() {
    ifstream archivoLectura;
    archivoLectura.open(ARCHIVO, ios::in | ios::binary);
    if (!archivoLectura) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }
    structpersona persona;
    cout << "\nLISTADO DE DATOS" << endl;
    cout << "================" << endl;
    while (archivoLectura.read((char*)&persona, sizeof(structpersona))) {
        cout << "\tNombre: " << persona.nombre << endl;
        cout << "\tEdad: " << persona.edad << endl;
        cout << "\tSexo: " << persona.sexo << endl;
        cout << "\tFecha de nacimiento: " << persona.fechadenacimiento << endl;
        cout << "----------------------" << endl;
    }
    archivoLectura.close();
}

