#ifndef CARGAR_ARCHIVOS_H  
#define CARGAR_ARCHIVOS_H  

#include <iostream>  
#include <fstream>  
#include <string>  

#include "../libs/CONFIGURACION.H"  
#include "../libs/PACIENTE.H"  
#include "../functions/separarConfig.H"  
#include "../functions/separarPacientes.H"  
#include "../functions/cadena_struct.H"  


/**
 * Lee un archivo de texto con configuraciones de sensores y
 * almacena cada registro en el arreglo de estructuras ConfigSensor.
 * Retorna la cantidad total de configuraciones cargadas.
 */
int cargarConfiguraciones(const char nombreArchivo[], ConfigSensor configs[]) {

    ifstream fileStream;  
    // Objeto que se usará para manejar la lectura del archivo

    fileStream.open(nombreArchivo, ios::in);  
    // Abre el archivo en modo lectura

    if (!fileStream.is_open()) {  
        // Verifica si el archivo no pudo abrirse
        cout << "Error al abrir el archivo." << endl;
        return 0;
    }

    cout << "Archivo de configuraciones abierto correctamente." << endl;

    string line;  
    // Variable para almacenar cada línea leída

    int contador = 0;  
    // Lleva la cuenta de configuraciones cargadas

    while (getline(fileStream, line)) {  
    // Lee el archivo línea por línea

        char lineaChar[100];  
        // Buffer para convertir la línea a arreglo de caracteres

        strncpy(lineaChar, line.c_str(), sizeof(lineaChar)-1);  
        // Copia la cadena del objeto string al arreglo de caracteres

        lineaChar[sizeof(lineaChar)-1] = '\0';  
        // Asegura el terminador de cadena

        char valores[3][20];  
        // Arreglo donde se guardarán los campos separados de la línea

        int cantidad = separarConfig(lineaChar, valores);  
        // Divide la línea usando comas como separador

        configs[contador] = cargarConfig(valores);  
        // Convierte los valores separados en una estructura ConfigSensor

        contador++;  
        // Incrementa el número de configuraciones cargadas
    }

    fileStream.close();  
    // Cierra el archivo

    return contador;  
    // Retorna el número total de configuraciones leídas
}

/**
 * Lee un archivo de texto con información de pacientes y
 * carga cada registro en el arreglo de estructuras Paciente.
 * Retorna la cantidad total de pacientes cargados.
 */
int cargarPacientes(const char nombreArchivo[], Paciente pacientes[]) {

    ifstream fileStream;  
    // Objeto para manejar la lectura del archivo

    fileStream.open(nombreArchivo, ios::in);  
    // Abre el archivo en modo lectura

    if (!fileStream.is_open()) {  
        // Verifica si el archivo no pudo abrirse
        cout << "Error al abrir el archivo de pacientes." << endl;
        return 0;
    }

    cout << "Archivo de pacientes abierto correctamente." << endl;

    string line;  
    // Variable para almacenar cada línea del archivo

    int contador = 0;  
    // Número de pacientes cargados

    while (getline(fileStream, line)) {  
    // Lee cada línea del archivo

        char lineaChar[300];  
        // Buffer para trabajar la línea como arreglo de caracteres

        strncpy(lineaChar, line.c_str(), sizeof(lineaChar)-1);  
        // Copia el contenido del string al arreglo

        lineaChar[sizeof(lineaChar)-1] = '\0';  
        // Asegura el terminador de cadena

        char valores[20][110];  
        // Matriz donde se almacenarán los campos separados

        int cantidad = separarPaciente(lineaChar, valores);  
        // Divide la línea usando ';' como separador

        pacientes[contador] = cargarPaciente(valores, cantidad);  
        // Convierte los campos en una estructura Paciente

        contador++;  
        // Incrementa el contador de pacientes cargados
    }

    fileStream.close();  
    // Cierra el archivo

    return contador;  
    // Retorna la cantidad total de pacientes
}

/**
 * Cuenta cuántas líneas tiene un archivo de texto.
 * Se utiliza para determinar cuántos registros contiene
 * el archivo antes de cargar los datos.
 */
int contarLineas(const char nombreArchivo[])
{
    ifstream archivo(nombreArchivo);  
    // Abre el archivo en modo lectura

    int contador = 0;  
    // Contador de líneas

    char linea[300];  
    // Buffer donde se almacena cada línea leída

    while (archivo.getline(linea,300))  
        // Lee cada línea del archivo hasta llegar al final
        contador++;

    archivo.close();  
    // Cierra el archivo

    return contador;  
    // Retorna la cantidad total de líneas
}


#endif  