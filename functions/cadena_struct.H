#ifndef CADENA_A_STRUCT_H  
#define CADENA_A_STRUCT_H  

#include "../libs/CONFIGURACION.H"  
#include "../functions/separarConfig.H"  
#include "../libs/PACIENTE.H"  
#include <cstdlib>  
#include <cstring>  


/**
 * Construye una estructura ConfigSensor a partir de los valores
 * obtenidos al separar una línea del archivo de configuraciones.
 * Los datos recibidos como texto se convierten a los tipos adecuados.
 */
ConfigSensor cargarConfig(char valores[][20]) {

    ConfigSensor config;  
    // Estructura donde se almacenará la configuración del sensor

    strcpy(config.TipoSensor, valores[0]);  
    // Copia el tipo de sensor (por ejemplo T, O, P_SIS, P_DIA)

    config.minimo = atof(valores[1]);  
    // Convierte el valor mínimo desde texto a número decimal

    config.maximo = atof(valores[2]);  
    // Convierte el valor máximo desde texto a número decimal

    return config;  
    // Retorna la estructura ya inicializada
}

/**
 * Construye una estructura Paciente utilizando los campos
 * obtenidos al separar una línea del archivo de pacientes.
 * Convierte los datos necesarios y copia la información textual.
 */
Paciente cargarPaciente(char valores[][110], int cantidad) {

    Paciente p;  
    // Estructura donde se almacenará la información del paciente

    p.Idpaciente = atoi(valores[0]);  
    // Convierte el identificador del paciente de texto a entero

    strcpy(p.TipoDocumento, valores[1]);  
    // Copia el tipo de documento

    strcpy(p.Documento, valores[2]);  
    // Copia el número de documento

    strcpy(p.Nombres, valores[3]);  
    // Copia los nombres del paciente

    strcpy(p.Apellidos, valores[4]);  
    // Copia los apellidos del paciente

    strcpy(p.FechaNacimiento, valores[5]);  
    // Copia la fecha de nacimiento

    strcpy(p.Telefono, valores[6]);  
    // Copia el número de teléfono

    strcpy(p.Email, valores[7]);  
    // Copia la dirección de correo electrónico

    strcpy(p.TipoSangre, valores[8]);  
    // Copia el tipo de sangre

    strcpy(p.EntidadSalud, valores[9]);  
    // Copia la entidad de salud del paciente

    if(cantidad > 10)  
        // Verifica si existe el campo de medicina prepagada
        strcpy(p.MedicinaPrepagada, valores[10]);
    else
        // Si el archivo no contiene ese campo se deja vacío
        strcpy(p.MedicinaPrepagada, "");

    return p;  
    // Retorna la estructura con todos los datos cargados
}

#endif  