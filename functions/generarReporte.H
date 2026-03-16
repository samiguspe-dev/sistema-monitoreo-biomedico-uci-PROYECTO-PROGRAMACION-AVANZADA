#ifndef GENERAR_REPORTE_H  
#define GENERAR_REPORTE_H  

#include "../libs/MEDICION.H"  
#include "../libs/CONFIGURACION.H"  
#include "../functions/comparar_fechas.H"  
#include "../functions/detectarAnomalia.H"  

#include <fstream>  
#include <cstring>  
#include <iostream>  

/**
 * Genera un reporte detallado de todas las mediciones de un paciente específico.
 * Busca las mediciones en todas las salas y máquinas, agrupa las lecturas por tipo
 * de sensor y calcula estadísticas básicas (mínimo, máximo y promedio).
 */
void reportePaciente(const salaUCI salas[],
                     int cantidadSalas,
                     const ConfigSensor configs[],
                     int cantidadConfigs,
                     const char idPaciente[11])
{

    // ===== 1. Contar cuántas mediciones existen para el paciente =====

    int total = 0;  // Número total de mediciones encontradas

    for (int s = 0; s < cantidadSalas; s++)  // Recorre todas las salas
        for (int m = 0; m < (unsigned char)salas[s].NumeroMaquinas; m++)  // Recorre máquinas de cada sala
            for (unsigned int j = 0; j < salas[s].maquinas[m].NumeroMediciones; j++)  // Recorre mediciones
                if (strncmp(salas[s].maquinas[m].Mediciones[j].Idpaciente,idPaciente,11) == 0)  
                    // Verifica si la medición pertenece al paciente solicitado
                    total++;  // Incrementa el contador de mediciones

    if (total == 0) {  // Si no se encontraron mediciones para el paciente
        cout << "No existen mediciones para ese paciente\n";
        return;  // Termina la función
    }

    // ===== 2. Crear arreglo dinámico para almacenar las mediciones del paciente =====

    medicion** listaPaciente = new medicion*[total];  
    // Arreglo de punteros que almacenará las mediciones del paciente

    int contador = 0;  // Índice para llenar el arreglo

    for (int s = 0; s < cantidadSalas; s++)
        for (int m = 0; m < (unsigned char)salas[s].NumeroMaquinas; m++)
            for (unsigned int j = 0; j < salas[s].maquinas[m].NumeroMediciones; j++)
                if (strcmp(salas[s].maquinas[m].Mediciones[j].Idpaciente,idPaciente) == 0)
                    // Verifica nuevamente si la medición corresponde al paciente
                    listaPaciente[contador++] =
                        &salas[s].maquinas[m].Mediciones[j];
                    // Guarda la dirección de la medición encontrada

    // ===== 3. Crear el archivo de salida =====

    char nombreArchivo[50];  // Buffer para construir el nombre del archivo

    sprintf(nombreArchivo,"mediciones_paciente_%.11s.txt",idPaciente);  
    // Genera un nombre de archivo que incluye el ID del paciente
    
    ofstream archivo(nombreArchivo);  // Abre el archivo para escribir el reporte

    archivo << "====================================\n";
    archivo << "REPORTE MEDICO PACIENTE " << idPaciente << "\n";
    archivo << "====================================\n";

    // ===== 4. Inicializar variables para estadísticas =====

    double minT = 9999, maxT = -9999, sumT = 0;  // Temperatura
    double minO = 9999, maxO = -9999, sumO = 0;  // Oxígeno
    double minE = 9999, maxE = -9999, sumE = 0;  // ECG

    double minPSis = 9999, maxPSis = -9999, sumPSis = 0;  // Presión sistólica
    double minPDia = 9999, maxPDia = -9999, sumPDia = 0;  // Presión diastólica

    int countT = 0, countO = 0, countE = 0;  // Contadores de lecturas
    int countPSis = 0, countPDia = 0;

    // ================= TEMPERATURA =================

    archivo << "\n--- TEMPERATURA ---\n";

    for (int i = 0; i < contador; i++) {  // Recorre mediciones del paciente

        for (unsigned int j = 0; j < listaPaciente[i]->NumeroLecturas; j++) {  // Recorre lecturas

            lectura* l = &listaPaciente[i]->lecturas[j];  // Obtiene la lectura actual

            if (l->TipoSensor == 'T') {  // Verifica si la lectura corresponde a temperatura

                archivo << listaPaciente[i]->FechaHora
                        << " | " << l->valor;

                if (esAnomalia(*l, configs, cantidadConfigs))  
                    // Determina si la lectura está fuera del rango permitido
                    archivo << " (ANOMALIA)";
                else
                    archivo << " (Normal)";

                archivo << "\n";

                if (l->valor < minT) minT = l->valor;  // Actualiza mínimo
                if (l->valor > maxT) maxT = l->valor;  // Actualiza máximo

                sumT += l->valor;  // Acumula valores para calcular promedio
                countT++;  // Cuenta lecturas
            }
        }
    }

    // ================= OXIGENO =================

    archivo << "\n--- OXIGENO ---\n";

    for (int i = 0; i < contador; i++) {

        for (unsigned int j = 0; j < listaPaciente[i]->NumeroLecturas; j++) {

            lectura* l = &listaPaciente[i]->lecturas[j];

            if (l->TipoSensor == 'O') {  // Verifica sensor de oxígeno

                archivo << listaPaciente[i]->FechaHora
                        << " | " << l->valor;

                if (esAnomalia(*l, configs, cantidadConfigs))
                    archivo << " (ANOMALIA)";
                else
                    archivo << " (Normal)";

                archivo << "\n";

                if (l->valor < minO) minO = l->valor;
                if (l->valor > maxO) maxO = l->valor;

                sumO += l->valor;
                countO++;
            }
        }
    }

    // ================= PRESION =================

    archivo << "\n--- PRESION ---\n";

    for (int i = 0; i < contador; i++) {

        for (unsigned int j = 0; j < listaPaciente[i]->NumeroLecturas; j++) {

            lectura* l = &listaPaciente[i]->lecturas[j];

            if (l->TipoSensor == 'P') {  // Verifica sensor de presión arterial

                archivo << listaPaciente[i]->FechaHora
                        << " | "
                        << l->sistolica
                        << "-"
                        << l->diastolica;

                if (esAnomalia(*l, configs, cantidadConfigs))
                    archivo << " (ANOMALIA)";
                else
                    archivo << " (Normal)";

                archivo << "\n";

                // Actualiza estadísticas de presión sistólica
                if (l->sistolica < minPSis) minPSis = l->sistolica;
                if (l->sistolica > maxPSis) maxPSis = l->sistolica;

                // Actualiza estadísticas de presión diastólica
                if (l->diastolica < minPDia) minPDia = l->diastolica;
                if (l->diastolica > maxPDia) maxPDia = l->diastolica;

                sumPSis += l->sistolica;
                sumPDia += l->diastolica;

                countPSis++;
                countPDia++;
            }
        }
    }

    // ================= ECG =================

    archivo << "\n--- ECG ---\n";

    for (int i = 0; i < contador; i++) {

        for (unsigned int j = 0; j < listaPaciente[i]->NumeroLecturas; j++) {

            lectura* l = &listaPaciente[i]->lecturas[j];

            if (l->TipoSensor == 'E') {  // Verifica sensor ECG

                archivo << listaPaciente[i]->FechaHora
                        << " | "
                        << l->valor
                        << "\n";

                if (l->valor < minE) minE = l->valor;
                if (l->valor > maxE) maxE = l->valor;

                sumE += l->valor;
                countE++;
            }
        }
    }

    // ================= ESTADISTICAS =================

    archivo << "\n===== ESTADISTICAS =====\n";

    if (countT > 0)
        archivo << "T -> Min: " << minT
                << " Max: " << maxT
                << " Prom: " << sumT / countT << "\n";

    if (countO > 0)
        archivo << "O -> Min: " << minO
                << " Max: " << maxO
                << " Prom: " << sumO / countO << "\n";

    if (countPSis > 0)
        archivo << "P_SIS -> Min: " << minPSis
                << " Max: " << maxPSis
                << " Prom: " << sumPSis / countPSis << "\n";

    if (countPDia > 0)
        archivo << "P_DIA -> Min: " << minPDia
                << " Max: " << maxPDia
                << " Prom: " << sumPDia / countPDia << "\n";

    if (countE > 0)
        archivo << "ECG -> Min: " << minE
                << " Max: " << maxE
                << " Prom: " << sumE / countE << "\n";

    archivo.close();  // Cierra el archivo de reporte

    delete[] listaPaciente;  // Libera memoria del arreglo dinámico

    cout << "Reporte generado correctamente\n";
}

#endif  