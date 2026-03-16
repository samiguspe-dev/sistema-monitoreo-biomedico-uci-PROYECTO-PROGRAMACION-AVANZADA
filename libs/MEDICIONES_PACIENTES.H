#ifndef MEDICIONES_PACIENTES_H
#define MEDICIONES_PACIENTES_H

#include "../libs/MEDICION.H"

struct MedicionesPaciente {

    // Agrupa todas las mediciones asociadas a un paciente específico.

    char id[11];           
    // Identificador del paciente al que pertenecen las mediciones.

    medicion** mediciones; 
    // Arreglo dinámico de punteros a mediciones del paciente.

    int cantidad;          
    // Número actual de mediciones almacenadas.

    int capacidad;         
    // Capacidad máxima del arreglo de mediciones.

};

#endif