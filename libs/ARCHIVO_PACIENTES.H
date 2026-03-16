#ifndef ARCHIVOPA_H
#define ARCHIVOPA_H

#include "../libs/PACIENTE.H"

struct archivoPacien{

    // Estructura que agrupa los pacientes cargados desde un archivo.

    Paciente* pacientes;  
    // Arreglo dinámico de pacientes.

    int cantPacientes;    
    // Cantidad total de pacientes almacenados.

};

#endif
