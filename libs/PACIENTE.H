#ifndef PACIENTES_H
#define PACIENTES_H

struct Paciente{

    // Estructura que almacena la información personal y administrativa
    // de un paciente registrado en el sistema.

    int Idpaciente;              
    // Identificador único del paciente en el sistema.

    char TipoDocumento[5];       
    // Tipo de documento (CC, TI, CE, etc).

    char Documento[15];          
    // Número de documento del paciente.

    char Nombres[50];            
    // Nombres del paciente.

    char Apellidos[50];          
    // Apellidos del paciente.

    char FechaNacimiento[20];    
    // Fecha de nacimiento del paciente.

    char Telefono[15];           
    // Número de teléfono de contacto.

    char Email[50];              
    // Correo electrónico del paciente.

    char TipoSangre[5];          
    // Tipo de sangre del paciente (O+, A-, etc).

    char EntidadSalud[50];       
    // Entidad de salud o EPS a la que pertenece.

    char MedicinaPrepagada[30];  
    // Medicina prepagada asociada al paciente.

};

#endif