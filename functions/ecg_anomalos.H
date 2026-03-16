#ifndef ECG_ANOMALOS_H  
#define ECG_ANOMALOS_H  

#include "../libs/MEDICION.H" 
#include "../libs/CONFIGURACION.H"  
#include "../libs/LECTURA.H"  
#include "../functions/ECG.H"  
#include <fstream>  
#include <iostream>  
#include <stdlib.h>  
#include <cstdlib>  

/**
 * Exporta a un archivo binario los pacientes que presentan anomalías en ECG.
 * Para cada paciente con ECG anómalo se almacenan su ID, el número de mediciones
 * ECG encontradas y los datos de cada lectura (fecha y valor).
 */
void exportarPacientesECGAnomalo(
    salaUCI salas[],          // Arreglo de salas cargadas en memoria
    int cantidadSalas,        // Número total de salas
    ConfigSensor configs[],   // Configuración de sensores
    int cantidadConfigs)      // Número de configuraciones disponibles
{
    ofstream archivo("pacientes_ecg_anomalos.dat", ios::binary);  
    // Abre el archivo binario donde se guardarán los pacientes con ECG anómalo

    if (!archivo) {  
        // Verifica si el archivo no pudo crearse
        cout << "No se pudo crear el archivo.\n";
        return;
    }

    //  Lista dinámica para evitar procesar el mismo paciente varias veces 

    int capacidadProcesados = 10;  // Capacidad inicial del arreglo
    int cantidadProcesados = 0;    // Número actual de pacientes registrados

    char** pacientesProcesados = new char*[capacidadProcesados];  
    // Arreglo dinámico de strings para almacenar IDs de pacientes procesados

    for (int i = 0; i < capacidadProcesados; i++)  
        pacientesProcesados[i] = new char[11];  
        // Reserva espacio para almacenar cada ID de paciente

    //  Recorrer todas las mediciones del sistema 
    for (int s = 0; s < cantidadSalas; s++) {  

        for (int m = 0; m < (unsigned char)salas[s].NumeroMaquinas; m++) {  

            for (unsigned int j = 0; j < salas[s].maquinas[m].NumeroMediciones; j++) {  

                medicion* med = &salas[s].maquinas[m].Mediciones[j];  
                // Obtiene la medición actual

                //  Verificar si el paciente ya fue procesado 
                bool yaProcesado = false;

                for (int p = 0; p < cantidadProcesados; p++) {  

                    if (strncmp(pacientesProcesados[p], med->Idpaciente, 11) == 0)  
                        // Compara el ID con los pacientes ya registrados

                    {
                        yaProcesado = true;  
                        // Marca que el paciente ya fue procesado
                        break;
                    }
                }

                if (yaProcesado)  
                    // Si el paciente ya fue procesado se ignora
                    continue;

                //  Agregar paciente a la lista de procesados 
                if (cantidadProcesados == capacidadProcesados) {  
                    // Si el arreglo se llena se aumenta su tamaño

                    capacidadProcesados *= 2;  

                    char** nuevo = new char*[capacidadProcesados];  

                    for (int i = 0; i < cantidadProcesados; i++)  
                        nuevo[i] = pacientesProcesados[i];  
                        // Copia los punteros existentes

                    for (int i = cantidadProcesados; i < capacidadProcesados; i++)  
                        nuevo[i] = new char[11];  
                        // Reserva memoria para nuevas posiciones

                    delete[] pacientesProcesados;  
                    // Libera el arreglo anterior

                    pacientesProcesados = nuevo;  
                    // Asigna el nuevo arreglo
                }

                strncpy(pacientesProcesados[cantidadProcesados], med->Idpaciente, 11);  
                // Copia el ID del paciente al arreglo

                pacientesProcesados[cantidadProcesados][10] = '\0';  
                // Asegura el terminador de cadena

                cantidadProcesados++;  

                //  Verificar si el paciente tiene ECG anómalo 
                if (!detectarAnomaliaECG(
                        salas,
                        cantidadSalas,
                        med->Idpaciente,
                        configs,
                        cantidadConfigs,
                        false))
                    // Si la función indica que no hay anomalía
                    continue;

                //  Contar todas las lecturas ECG del paciente 
                int contadorECG = 0;

                for (int ss = 0; ss < cantidadSalas; ss++) {

                    for (int mm = 0; mm < (unsigned char)salas[ss].NumeroMaquinas; mm++) {

                        for (unsigned int jj = 0; jj < salas[ss].maquinas[mm].NumeroMediciones; jj++) {

                            medicion* m2 = &salas[ss].maquinas[mm].Mediciones[jj];

                            if (strncmp(m2->Idpaciente, med->Idpaciente, 11) != 0)
                                // Verifica que la medición corresponda al paciente
                                continue;

                            for (unsigned int k = 0; k < m2->NumeroLecturas; k++) {

                                if (m2->lecturas[k].TipoSensor == 'E')
                                    // Cuenta únicamente las lecturas ECG
                                    contadorECG++;
                            }
                        }
                    }
                }

                //  Escribir el ID del paciente en el archivo 
                archivo.write(med->Idpaciente, 11);

                //  Escribir el número de mediciones ECG 
                archivo.write((char*)&contadorECG, sizeof(int));

                //  Escribir cada lectura ECG del paciente 
                for (int ss = 0; ss < cantidadSalas; ss++) {

                    for (int mm = 0; mm < (unsigned char)salas[ss].NumeroMaquinas; mm++) {

                        for (unsigned int jj = 0; jj < salas[ss].maquinas[mm].NumeroMediciones; jj++) {

                            medicion* m2 = &salas[ss].maquinas[mm].Mediciones[jj];

                            if (strncmp(m2->Idpaciente, med->Idpaciente, 11) != 0)
                                continue;

                            for (unsigned int k = 0; k < m2->NumeroLecturas; k++) {

                                if (m2->lecturas[k].TipoSensor == 'E') {

                                    archivo.write(m2->FechaHora, 24);  
                                    // Guarda la fecha y hora de la medición

                                    double valor = m2->lecturas[k].valor;

                                    archivo.write((char*)&valor, sizeof(double));  
                                    // Guarda el valor de la lectura ECG
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    archivo.close();  // Cierra el archivo binario

    //  Liberar memoria dinámica 
    for (int i = 0; i < capacidadProcesados; i++)
        delete[] pacientesProcesados[i];  // Libera cada string de ID

    delete[] pacientesProcesados;  // Libera el arreglo principal

    cout << "Archivo pacientes_ecg_anomalos.dat generado correctamente.\n";
}

#endif  