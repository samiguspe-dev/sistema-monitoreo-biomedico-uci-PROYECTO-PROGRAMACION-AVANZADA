#ifndef LEER_BSF_H  
#define LEER_BSF_H  

#include <fstream>  
#include <iostream>  
#include "../libs/MEDICION.H"  
#include "../libs/CONFIGURACION.H"  
#include "../libs/LECTURA.H"  
#include "../libs/MAQUINA_UCI.H"  
#include "../libs/SALA_UCI.H"  

#include <iostream>  
#include <fstream>  
#include <cstring>  


/**
 * Lee el archivo binario con las mediciones de pacientes y construye
 * en memoria la estructura jerárquica de salas, máquinas, mediciones
 * y lecturas. Retorna la cantidad total de salas cargadas.
 */
int leer_binario(salaUCI*& salas){

    const char nombrearchivo[] = "data/patient_readings_simulation.bsf";  
    // Nombre del archivo binario que contiene las mediciones

    fstream archivo;  
    // Objeto para manejar la lectura del archivo

    archivo.open(nombrearchivo, ios::in | ios::binary);  
    // Abre el archivo en modo lectura binaria

    if (archivo.fail()){  
        // Verifica si el archivo no pudo abrirse
        cout << "No se pudo abrir el archivo\n";
        return 0;  
        // Si falla, no se cargan salas
    }

    int capacidad = 10;  
    // Capacidad inicial del arreglo dinámico de salas

    salas = new salaUCI[capacidad];  
    // Reserva memoria para almacenar las salas leídas

    int contador = 0;  
    // Número de salas cargadas

    while (true) {  
        // Bucle de lectura continua hasta alcanzar el final del archivo
       
        if (!archivo) {  
            // Verifica si ocurrió error o se alcanzó el fin del archivo
            cout << "Fin de archivo alcanzado o error de lectura\n";
            break;
        }

        if (contador == capacidad) {  
            // Si el arreglo de salas se llena se aumenta su tamaño

            capacidad *= 2;  
            // Duplica la capacidad del arreglo

            salaUCI* temp = new salaUCI[capacidad];  
            // Crea un nuevo arreglo más grande

            for (int i = 0; i < contador; i++)  
                temp[i] = salas[i];  
                // Copia las salas existentes al nuevo arreglo

            delete[] salas;  
            // Libera el arreglo antiguo

            salas = temp;  
            // Apunta al nuevo arreglo
        }
        
        if (!archivo.read(&salas[contador].IdSala, sizeof(char))) {  
            // Lee el identificador de la sala desde el archivo
            break;  
            // Si falla la lectura se termina el proceso
        }
        
        if (!archivo.read((char*)&salas[contador].NumeroMaquinas, sizeof(char))) {  
            // Lee el número de máquinas que tiene la sala
            cout << "Error al leer num_maquinas\n";
            break;
        }

        salas[contador].maquinas =
            new maquinaUCI[(unsigned char)salas[contador].NumeroMaquinas];
        // Reserva memoria para las máquinas pertenecientes a la sala
        
        for (unsigned int i = 0; i < (unsigned char)salas[contador].NumeroMaquinas; i++) {
            // Recorre cada máquina de la sala
            
            if (!archivo.read(&salas[contador].maquinas[i].Idmaquina, sizeof(char))) {
                // Lee el identificador de la máquina
                cout << "Error al leer id_maquina\n";
                break;
            }
            
            if (!archivo.read((char*)&salas[contador].maquinas[i].NumeroMediciones, sizeof(unsigned int))) {
                // Lee la cantidad de mediciones registradas en la máquina
                cout << "Error al leer num_mediciones\n";
                break;
            }

            salas[contador].maquinas[i].Mediciones =
                new medicion[salas[contador].maquinas[i].NumeroMediciones];
            // Reserva memoria para las mediciones de la máquina
            
            for (unsigned int j = 0; j < salas[contador].maquinas[i].NumeroMediciones; j++) {
                // Recorre cada medición registrada
                
                if (!archivo.read(
                        salas[contador].maquinas[i].Mediciones[j].Idpaciente,11)) {
                    // Lee el ID del paciente asociado a la medición
                    cout << "Error al leer id_paciente\n";
                    break;
                }
            
                if (!archivo.read(
                        salas[contador].maquinas[i].Mediciones[j].FechaHora,24)) {
                    // Lee la fecha y hora en que se realizó la medición
                    cout << "Error al leer fecha_y_hora\n";
                    break;
                }
                
                if (!archivo.read(
                        (char*)&salas[contador].maquinas[i].Mediciones[j].NumeroLecturas,
                        sizeof(unsigned int))) {
                    // Lee la cantidad de lecturas registradas en la medición
                    cout << "Error al leer numlecturas\n";
                    break;
                }

                salas[contador].maquinas[i].Mediciones[j].lecturas =
                    new lectura[salas[contador].maquinas[i].Mediciones[j].NumeroLecturas];
                // Reserva memoria para las lecturas de sensores
                
                for (unsigned int k = 0;
                     k < salas[contador].maquinas[i].Mediciones[j].NumeroLecturas;
                     k++) {
                // Recorre todas las lecturas registradas
                
                    if (!archivo.read(
                            &salas[contador].maquinas[i].Mediciones[j].lecturas[k].TipoSensor,
                            sizeof(char))) {
                        // Lee el tipo de sensor de la lectura
                        cout << "Error al leer tipo de lectura\n";
                        break;
                    }
                    
                    if (salas[contador].maquinas[i].Mediciones[j].lecturas[k].TipoSensor == 'P') {
                        // Si el sensor es de presión arterial

                        archivo.read(
                            (char*)&salas[contador].maquinas[i].Mediciones[j].lecturas[k].sistolica,
                            sizeof(unsigned int));
                        // Lee el valor de presión sistólica

                        archivo.read(
                            (char*)&salas[contador].maquinas[i].Mediciones[j].lecturas[k].diastolica,
                            sizeof(unsigned int));
                        // Lee el valor de presión diastólica

                    } else {
                        // Para otros sensores (temperatura, oxígeno, etc.)

                        archivo.read(
                            (char*)&salas[contador].maquinas[i].Mediciones[j].lecturas[k].valor,
                            sizeof(double));
                        // Lee el valor numérico de la lectura
                    }
                }
            }
        }
        
        contador++;  
        // Incrementa el número de salas cargadas
    }

    archivo.close();  
    // Cierra el archivo binario

    return contador;  
    // Retorna la cantidad total de salas leídas
}

#endif  