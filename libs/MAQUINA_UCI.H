#ifndef MAQUINAUCI_H
#define MAQUINAUCI_H

struct maquinaUCI{

    // Representa una máquina de monitoreo ubicada en una sala UCI.

    char Idmaquina;            
    // Identificador de la máquina.

    unsigned int NumeroMediciones; 
    // Número de mediciones registradas por la máquina.

    medicion* Mediciones;      
    // Arreglo dinámico de mediciones realizadas por la máquina.

};

#endif