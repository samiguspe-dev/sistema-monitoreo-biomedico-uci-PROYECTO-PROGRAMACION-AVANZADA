#ifndef CONFIGURACION_H
#define CONFIGURACION_H

struct ConfigSensor {

    // Define los rangos válidos de funcionamiento para un sensor.

    char TipoSensor[10]; 
    // Nombre o tipo de sensor.

    double minimo;       
    // Valor mínimo permitido para el sensor.

    double maximo;       
    // Valor máximo permitido para el sensor.

};

#endif
