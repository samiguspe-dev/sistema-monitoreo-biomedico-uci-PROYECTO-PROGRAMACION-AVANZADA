#ifndef SALAUCI_H
#define SALAUCI_H

struct salaUCI {

    // Representa una sala de la Unidad de Cuidados Intensivos (UCI)
    // que contiene un conjunto de máquinas de monitoreo.

    char IdSala;            
    // Identificador de la sala UCI.

    char NumeroMaquinas;    
    // Número de máquinas UCI instaladas en la sala.

    maquinaUCI* maquinas;   
    // Arreglo dinámico de máquinas UCI pertenecientes a la sala.

};

#endif