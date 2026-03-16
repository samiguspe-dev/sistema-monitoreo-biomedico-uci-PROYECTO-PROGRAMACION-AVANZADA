#ifndef REPORTE_ANOMALIAS_H  
#define REPORTE_ANOMALIAS_H  

#include <cmath>  
#include <cstring>  
#include "../libs/MEDICION.H"  
#include "../libs/CONFIGURACION.H"  
#include "../libs/MEDICIONES_PACIENTES.H"  


/**
 * Genera un archivo de reporte con las anomalías detectadas en las mediciones.
 *
 * Recorre todas las salas, máquinas y mediciones registradas para agrupar las
 * mediciones por paciente y verificar si alguna lectura está fuera de los rangos
 * definidos en la configuración de sensores. Si se detectan anomalías, se escriben
 * en el archivo "anomalias.txt".
 */
void generarReporteAnomalias(
    const salaUCI salas[],        // Arreglo de salas UCI cargadas en el sistema
    int cantidadSalas,            // Número total de salas
    const ConfigSensor configs[], // Configuración de rangos válidos por sensor
    int cantidadConfigs)          // Número de configuraciones disponibles
{
    int capacidadPacientes = 50;   // Capacidad inicial del arreglo dinámico de pacientes
    int cantidadPacientes = 0;     // Número actual de pacientes almacenados

    // Arreglo dinámico donde se agruparán las mediciones por paciente
    MedicionesPaciente* pacientes =
        new MedicionesPaciente[capacidadPacientes];

    // Recorre todas las salas del sistema
    for (int s = 0; s < cantidadSalas; s++) {

        // Recorre todas las máquinas de la sala actual
        for (int m = 0; m < (unsigned char)salas[s].NumeroMaquinas; m++) {

            // Recorre todas las mediciones registradas por la máquina
            for (unsigned int j = 0; j < salas[s].maquinas[m].NumeroMediciones; j++) {

                // Obtiene un puntero a la medición actual
                medicion* med = &salas[s].maquinas[m].Mediciones[j];

                int posPaciente = -1;  // Índice del paciente dentro del arreglo

                // Busca si el paciente ya fue registrado previamente
                for (int p = 0; p < cantidadPacientes; p++) {
                    if (strcmp(pacientes[p].id, med->Idpaciente) == 0) {  // Si el ID coincide
                        posPaciente = p;  // Guarda su posición
                        break;
                    }
                }

                // Si el paciente aún no existe en el arreglo, se crea un nuevo registro
                if (posPaciente == -1) {

                    posPaciente = cantidadPacientes++;

                    strcpy(pacientes[posPaciente].id, med->Idpaciente);  // Copia el ID del paciente

                    pacientes[posPaciente].capacidad = 10;  // Capacidad inicial del arreglo de mediciones
                    pacientes[posPaciente].cantidad = 0;    // Inicialmente no tiene mediciones

                    // Reserva memoria para almacenar punteros a mediciones
                    pacientes[posPaciente].mediciones =
                        new medicion*[pacientes[posPaciente].capacidad];
                }

                // Guarda el puntero de la medición dentro del paciente correspondiente
                pacientes[posPaciente].mediciones[pacientes[posPaciente].cantidad++] = med;

                // Si el arreglo de mediciones se llena, se amplía dinámicamente
                if (pacientes[posPaciente].cantidad >= pacientes[posPaciente].capacidad) {

                    pacientes[posPaciente].capacidad *= 2;  // Duplica la capacidad

                    medicion** nuevo =
                        new medicion*[pacientes[posPaciente].capacidad];

                    // Copia los punteros existentes al nuevo arreglo
                    for (int i = 0; i < pacientes[posPaciente].cantidad; i++)
                        nuevo[i] = pacientes[posPaciente].mediciones[i];

                    delete[] pacientes[posPaciente].mediciones;  // Libera el arreglo anterior

                    pacientes[posPaciente].mediciones = nuevo;  // Asigna el nuevo arreglo
                }
            }
        }
    }

    ofstream archivo("anomalias.txt");  // Archivo donde se guardará el reporte

    archivo << "===== REPORTE DE ANOMALIAS =====\n\n";

    // Recorre todos los pacientes agrupados
    for (int p = 0; p < cantidadPacientes; p++) {

        bool tieneAnomalia = false;  // Indica si el paciente presenta al menos una anomalía

        // Revisión de todas las mediciones del paciente
        for (int i = 0; i < pacientes[p].cantidad && !tieneAnomalia; i++) {

            medicion* m = pacientes[p].mediciones[i];

            // Recorre las lecturas de sensores en la medición
            for (unsigned int j = 0; j < m->NumeroLecturas && !tieneAnomalia; j++) {

                lectura* l = &m->lecturas[j];

                // Las lecturas ECG no se consideran para el análisis de anomalías
                if (l->TipoSensor == 'E')
                    continue;

                if (esAnomalia(*l, configs, cantidadConfigs))
                    tieneAnomalia = true;
            }
        }

        // Si el paciente no presenta anomalías, no se incluye en el reporte
        if (!tieneAnomalia)
            continue;

        archivo << "\n----------------------------------\n";
        archivo << "Paciente ID: " << pacientes[p].id << "\n";
        archivo << "----------------------------------\n";

        // Recorre nuevamente las mediciones para imprimir las anomalías encontradas
        for (int i = 0; i < pacientes[p].cantidad; i++) {

            medicion* m = pacientes[p].mediciones[i];

            for (unsigned int j = 0; j < m->NumeroLecturas; j++) {

                lectura* l = &m->lecturas[j];

                // Se ignoran nuevamente las lecturas ECG
                if (l->TipoSensor == 'E')
                    continue;

                if (esAnomalia(*l, configs, cantidadConfigs)) {

                    archivo << "Fecha: "
                            << m->FechaHora
                            << " | Sensor "
                            << l->TipoSensor;

                    if (l->TipoSensor == 'P')
                        archivo << " | Valor: " << l->sistolica << "-" << l->diastolica;
                    else
                        archivo << " | Valor: " << l->valor;

                    archivo << " --> ANOMALIA\n";
                }
            }
        }
    }

    archivo.close();  // Cierra el archivo de salida

    // Liberación de memoria dinámica utilizada para las mediciones por paciente
    for (int p = 0; p < cantidadPacientes; p++)
        delete[] pacientes[p].mediciones;

    delete[] pacientes;

    cout << "Reporte generado correctamente.\n";
}

#endif  