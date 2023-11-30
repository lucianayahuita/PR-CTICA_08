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
#include <string>
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
bool encontraraceptadosporsexo(const char encontrar[]);
bool encontraraceptadosporfechadenac(const char buscar[]);
void encontrarAceptados(const char *MIARCHIVO, const char *ARCHIVO1);

int main() {
    datosActualesArchivo(MIARCHIVO);
    encontraraceptadosporsexo("M");
    encontraraceptadosporfechadenac("DD/MM/YYYY");
    encontrarAceptados(MIARCHIVO, ARCHIVO1);
    return 0;
}

void datosActualesArchivo(const char *MIARCHIVO) {
    cout << "*************DATOS ACTUALES DEL ARCHIVO****************" << endl;
    ifstream archivo(MIARCHIVO, ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        exit(1);
    }
    structpersona persona;
    while (archivo.read((char*)&persona, sizeof(structpersona))){
        cout << "Nombre: " << persona.nombre << endl;
        cout << "Edad: " << persona.edad << endl;
        cout << "Sexo: " << persona.sexo << endl;
        cout << "Fecha de Nacimiento: " << persona.fechadenacimiento << endl;
        cout << endl;
    }
    archivo.close();
}

bool encontraraceptadosporsexo(const char encontrar[2]){
    ifstream archivolectura;
    archivolectura.open(MIARCHIVO, ios::binary);
    if (!archivolectura) {
        cout << "Error al abrir al archivo" <<endl;
        exit(1);
    }
    structpersona persona;
    while (archivolectura.read((char*)&persona, sizeof(structpersona))) {
        if(strcmp(encontrar, persona.sexo)!=0){
            return true;
        }
    }
    archivolectura.close();
    return false;
}

bool encontraraceptadosporfechadenac(const char buscar[10]){
    ifstream archivoLeer;
    archivoLeer.open(MIARCHIVO, ios::binary);
    if(!archivoLeer) {
        cout << "Error al abrir al archivo" << endl;
        exit (1);
    }
    structpersona persona;
    while (archivoLeer.read((char*)&persona, sizeof(structpersona))) {
        string mesAnio = persona.fechadenacimiento;
        mesAnio = mesAnio.substr(3, 7);
        if (mesAnio == buscar) {
            return true;
        }
    }
    archivoLeer.close();
    return false;
}

void encontrarAceptados(const char *MIARCHIVO, const char *ARCHIVO1) {
    ifstream archivoentrada(MIARCHIVO, ios::binary);
    ofstream archivosalida(ARCHIVO1, ios::binary);
    if (!archivoentrada || !archivosalida){
        cout << "No se pudo abrir uno o ambos archivos" << endl;
        exit(1);
    }
    structpersona persona;
    while (archivoentrada.read((char*)&persona, sizeof(structpersona))){
        if(encontraraceptadosporsexo(persona.sexo) && encontraraceptadosporfechadenac(persona.fechadenacimiento + 3)){
            cout <<"MODIFICACION DE DATOS PARA LAS PERSONAS ACEPTADAS: "<< endl;
            archivosalida.write((char*)&persona, sizeof(structpersona));
            cout<<"\tNOMBRE: "<<persona.nombre<<endl;
            cout<<"\tSEXO: "<<persona.sexo<<endl;
            cout<<"\tFECHA DE NACIMIENTO: "<<persona.fechadenacimiento<<endl;
            cout<<"\tEDAD: "<<persona.edad<<endl;
        }
    }
    archivoentrada.close();
    archivosalida.close();
}



