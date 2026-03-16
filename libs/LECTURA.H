#ifndef LECTURA_H
#define LECTURA_H

struct lectura {

    // Representa una lectura individual tomada por un sensor médico.

    char TipoSensor;       
    // Tipo de sensor que generó la lectura.

    double valor;          
    // Valor medido por el sensor (temperatura, frecuencia, etc).

    unsigned int sistolica; 
    // Presión sistólica (usada en sensores de presión arterial).

    unsigned int diastolica;
    // Presión diastólica (usada en sensores de presión arterial).

};

#endif