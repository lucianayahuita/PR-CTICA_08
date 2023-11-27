// Materia: Programación I, Paralelo 1
// Autor: Luciana Yahuita
// Fecha creación: 27/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 3
// Problema planteado:Amplíe el programa anterior que procesa clientes de una agencia matrimonial para que tome
//los datos de todos los candidatos a estudiar del fichero PERSONAS.DAT del ejercicio anterior,
//lea el cliente del teclado y finalmente genere como resultado un listado por pantalla con los
//nombres de los candidatos aceptados y un fichero llamado ACEPTADOS.DAT con toda la
//información correspondiente a los candidatos aceptados.
//Una persona del fichero PERSONAS.DAT se considerará aceptable como candidato si tiene
//diferente sexo y que haya nacido en el mes y año (El programa debe ser capaz de trabajar con
//cualquier número de personas en el fichero PERSONAS.DAT).
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const char *MIARCHIVO = "PERSONAS.bin";
const char *ARCHIVO1 = "ACEPTADOS.dat";
struct structpersona {
    char nombre[30];
    char sexo[2];
    char fechadenacimiento[10];
    int edad;
};

void datosActualesArchivo(const char *MIARCHIVO);
void encontrarAceptados(const char *MIARCHIVO, const char *ARCHIVO1);

int main() {
    datosActualesArchivo(MIARCHIVO);
    encontrarAceptados(MIARCHIVO, ARCHIVO1);

    return 0;
}

void datosActualesArchivo(const char *MIARCHIVO) {
    cout << "*************DATOS ACTUALES DEL ARCHIVO****************" << endl;
    ifstream archivo(MIARCHIVO, ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    structpersona persona;
    while (archivo.read(reinterpret_cast<char *>(&persona), sizeof(structpersona))) {
        cout << "Nombre: " << persona.nombre << endl;
        cout << "Edad: " << persona.edad << endl;
        cout << "Sexo: " << persona.sexo << endl;
        cout << "Fecha de Nacimiento: " << persona.fechadenacimiento << endl;
        cout << endl;
    }

    archivo.close();
}

void encontrarAceptados(const char *MIARCHIVO, const char *ARCHIVO1) {
    ifstream archivoEntrada(MIARCHIVO, ios::binary);
    if (!archivoEntrada) {
        cerr << "Error al abrir el archivo de entrada." << endl;
        exit(1);
    }

    ofstream archivoSalida(ARCHIVO1, ios::binary | ios::app);
    if (!archivoSalida) {
        cerr << "Error al abrir o crear el archivo de salida." << endl;
        exit(1);
    }
    structpersona persona;
    while (archivoEntrada.read(reinterpret_cast<char *>(&persona), sizeof(structpersona))) {
        // Verificar condiciones para seleccionar la persona
        if (strcmp(persona.sexo, "M") == 0 && strncmp(persona.fechadenacimiento + 3, "mm/yyyy", 7) == 0) {
            cout << "Nombre: " << persona.nombre << endl;
            cout << "Edad: " << persona.edad << endl;
            cout << "Sexo: " << persona.sexo << endl;
            cout << "Fecha de Nacimiento: " << persona.fechadenacimiento << endl;
            cout << endl;
            // Guardar la persona en el archivo de salida
            archivoSalida.write(reinterpret_cast<const char *>(&persona), sizeof(structpersona));
        }
    }
    archivoEntrada.close();
    archivoSalida.close();
}



