#ifndef MEDICION_H
#define MEDICION_H

struct medicion {

    // Representa una medición médica realizada a un paciente.

    char Idpaciente[11];       
    // Identificador del paciente al que pertenece la medición.

    char FechaHora[24];        
    // Fecha y hora en que se realizó la medición.

    unsigned int NumeroLecturas; 
    // Cantidad de lecturas registradas en la medición.

    lectura* lecturas;         
    // Arreglo dinámico de lecturas obtenidas por los sensores.

};

#endif