#include <iostream>
#include <stdlib.h> 
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

#include "libs/LECTURA.H"
#include "libs/MEDICION.H"
#include "libs/MAQUINA_UCI.H"
#include "libs/SALA_UCI.H"
#include "libs/CONFIGURACION.H"
#include "libs/PACIENTE.H"
#include "libs/ARCHIVO_PACIENTES.H"
#include "libs/MEDICIONES_PACIENTES.H"
#include "functions/separarConfig.H"
#include "functions/separarPacientes.H"
#include "functions/cadena_struct.H"
#include "functions/comparar_fechas.H"
#include "functions/cargarArchivos.H"
#include "functions/detectarAnomalia.H"
#include "functions/generarReporte.H"
#include "functions/Leer_bsf.H"
#include "functions/Reporte_anomalias.H"
#include "functions/ECG.H"
#include "functions\ecg_anomalos.H"
#include "libs/MEDICIONES_PACIENTES.H"

// Variables globales utilizadas por el sistema
salaUCI* salas = nullptr;        // Arreglo dinámico de salas cargadas desde el archivo BSF
int cantidadSalas = 0;           // Número de salas cargadas

ConfigSensor* configs = nullptr; // Arreglo dinámico de configuraciones de sensores
Paciente* pacientes = nullptr;   // Arreglo dinámico de pacientes

int cantidadConfigs = 0;         // Cantidad de configuraciones cargadas
int cantidadPacientes = 0;       // Cantidad de pacientes cargados

archivoPacien archivoPacientes;  // Estructura auxiliar para manejo de pacientes

// --- MAIN ---

int main() {

    int opcion = 0;  // Variable que almacena la opción seleccionada por el usuario

    do {

        // Muestra el menú principal del sistema
        cout << "\n========================================" << endl;
        cout << "   SISTEMA DE MONITOREO BIOMEDICO UCI   " << endl;
        cout << "========================================" << endl;
        cout << " 1. Cargar archivo de configuracion y datos de pacientes" << endl;
        cout << " 2. Leer archivo .bsf" << endl;
        cout << " 3. Generar reporte de anomalias" << endl;
        cout << " 4. Calcular estadisticas" << endl;
        cout << " 5. Exportar datos procesados" << endl;
        cout << " 6. Salir" << endl;

        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";

        // Validación de entrada para evitar errores si el usuario escribe texto
        if(!(cin >> opcion)){

            cin.clear();            // Limpia el estado de error del flujo de entrada
            cin.ignore(1000,'\n');  // Descarta la entrada inválida

            cout << "Entrada invalida. Intente nuevamente.\n";

            continue;               // Regresa al inicio del menú
        }

        switch (opcion) {

            case 1: {

                // Carga el archivo de configuraciones y el archivo de pacientes

                if (configs != nullptr)
                    delete[] configs;  // Libera memoria si ya existían configuraciones cargadas

                if (pacientes != nullptr)
                    delete[] pacientes;  // Libera memoria si ya existían pacientes cargados

                // Se cuentan las líneas del archivo para dimensionar el arreglo
                cantidadConfigs = contarLineas("data/configuracion.txt");
                configs = new ConfigSensor[cantidadConfigs];

                // Se cargan las configuraciones desde el archivo
                cargarConfiguraciones("data/configuracion.txt", configs);

                // Se cuentan los pacientes en el archivo
                cantidadPacientes = contarLineas("data/pacientes.csv");
                pacientes = new Paciente[cantidadPacientes];

                // Se cargan los datos de pacientes
                cargarPacientes("data/pacientes.csv", pacientes);

                // Verificación de posibles errores en la carga
                if (cantidadConfigs == 0) {
                    cout << "Error cargando configuracion.txt" << endl;
                }

                if (cantidadPacientes == 0) {
                    cout << "Error cargando pacientes.csv" << endl;
                }

                // Muestra cuántos registros fueron cargados
                cout << "Configuraciones cargadas: "
                     << cantidadConfigs << endl;

                cout << "Pacientes cargados: "
                     << cantidadPacientes << endl;
            
                cin.ignore();
                cin.get();

                break;
            }

            case 2: {

                // Permite cargar el archivo binario con las mediciones biomédicas

                if (cantidadPacientes == 0) {
                    cout << "Debe cargar primero las configuraciones y pacientes (opcion 1).\n";
                    break;
                }

                // Si ya se había cargado información previamente, se libera la memoria
                if (salas != nullptr) {

                    for (int s = 0; s < cantidadSalas; s++) {

                        for (int m = 0; m < (unsigned char)salas[s].NumeroMaquinas; m++) {

                            for (unsigned int j = 0; j < salas[s].maquinas[m].NumeroMediciones; j++) {

                                delete[] salas[s].maquinas[m].Mediciones[j].lecturas;

                            }

                            delete[] salas[s].maquinas[m].Mediciones;

                        }

                        delete[] salas[s].maquinas;
                    }

                    delete[] salas;

                    salas = nullptr;
                }

                // Se lee el archivo binario BSF
                cantidadSalas = leer_binario(salas);

                cout << "\n===== ARCHIVO BSF CARGADO =====\n";
                cout << "Cantidad de salas: "
                     << cantidadSalas << endl;

                // Arreglo auxiliar para mostrar pacientes detectados sin repetirlos
                char** pacientesMostrados = new char*[cantidadPacientes];
                int cantidadPacientesMostrados = 0;

                for(int i = 0; i < cantidadPacientes; i++)
                    pacientesMostrados[i] = new char[11];

                // Recorre todas las salas cargadas
                for (int s = 0; s < cantidadSalas; s++) {

                    cout << "\nSala ID: "
                         << (unsigned int)(unsigned char)salas[s].IdSala
                         << endl;

                    cout << "Numero de maquinas: "
                         << (unsigned int)(unsigned char)salas[s].NumeroMaquinas
                         << endl;

                    cout << "Pacientes detectados:\n";

                    for (int m = 0; m < (unsigned char)salas[s].NumeroMaquinas; m++) {

                        for (int j = 0; j < salas[s].maquinas[m].NumeroMediciones; j++){

                            medicion& med = salas[s].maquinas[m].Mediciones[j];

                            bool yaExiste = false;

                            // Verifica si el paciente ya fue mostrado anteriormente
                            for (int p = 0; p < cantidadPacientesMostrados; p++) {

                                if (strncmp(pacientesMostrados[p], med.Idpaciente, 11) == 0) {
                                    yaExiste = true;
                                    break;
                                }
                            }

                            if (!yaExiste) {

                                strncpy(pacientesMostrados[cantidadPacientesMostrados],
                                        med.Idpaciente,
                                        11);
                                    
                                pacientesMostrados[cantidadPacientesMostrados][10] = '\0';

                                cantidadPacientesMostrados++;

                                cout << "  Paciente ID: "
                                     << med.Idpaciente << endl;
                            }
                        }
                    }
                }

                // Libera memoria auxiliar
                for(int i = 0; i < cantidadPacientesMostrados; i++)
                    delete[] pacientesMostrados[i];

                delete[] pacientesMostrados;

                cin.ignore();
                cin.get();
                break;
            }

            case 3: {

                // Genera un reporte con todas las anomalías detectadas

                if (cantidadSalas == 0) {
                    cout << "Primero debe cargar el archivo BSF." << endl;
                    break;
                }

                generarReporteAnomalias(salas,cantidadSalas,configs,cantidadConfigs);

                cin.ignore();
                cin.get();
                break;
            }

            case 4: {

                // Submenú para realizar análisis estadístico de mediciones

                int opcion;

                do{

                    cout << "\n------ CALCULO DE ESTADISTICAS ------\n";
                    cout << "1. Detectar anomalia en lectura\n";
                    cout << "2. Detectar ECG anomalo de un paciente\n";
                    cout << "3. Volver\n";

                    cout << "Seleccione una opcion: ";

                    cin >> opcion;

                    switch(opcion) {

                        case 1: {

                            // Busca lecturas anómalas de un paciente específico

                            if (cantidadSalas == 0) {
                                cout << "Primero debe cargar el archivo BSF.\n";
                                break;
                            }

                            if (cantidadConfigs == 0) {
                                cout << "Primero debe cargar configuraciones.\n";
                                break;
                            }

                            char idPaciente[11];

                            cout << "Ingrese ID del paciente: ";
                            cin >> idPaciente;

                            cout << "\nLecturas anomalas encontradas:\n";

                            bool encontrado = false;

                            // Recorre todas las mediciones del sistema
                            for (int s = 0; s < cantidadSalas; s++) {

                                for (int m = 0; m < (unsigned char)salas[s].NumeroMaquinas; m++) {

                                    for (unsigned int j = 0; j < salas[s].maquinas[m].NumeroMediciones; j++) {

                                        medicion* med =&salas[s].maquinas[m].Mediciones[j];  // Puntero medición

                                        if (strncmp(med->Idpaciente, idPaciente, 11) != 0)
                                            continue;

                                        for (unsigned int k = 0; k < med->NumeroLecturas; k++) {

                                            lectura* l = &med->lecturas[k];  // Puntero lectura

                                            if (esAnomalia(*l, configs, cantidadConfigs)) {

                                                encontrado = true;

                                                cout << med->FechaHora << " | "
                                                     << l->TipoSensor << " | ";

                                                if (l->TipoSensor == 'P') {

                                                    cout << l->sistolica
                                                         << "-"
                                                         << l->diastolica;

                                                } else {

                                                    cout << l->valor;
                                                }

                                                cout << endl;
                                            }
                                        }
                                    }
                                }
                            }

                            if (!encontrado) {
                                cout << "No se encontraron anomalías para este paciente.\n";
                            }

                            cin.ignore();
                            cin.get();
                            break;
                        }

                        case 2: {

                            // Verifica si el paciente presenta anomalía en ECG

                            if (cantidadSalas == 0) {
                                cout << "Primero debe cargar el archivo BSF.\n";
                                break;
                            }
                                        
                            if (cantidadConfigs == 0) {
                                cout << "Primero debe cargar el archivo de configuracion.\n";
                                break;
                            }

                            char idPaciente[11];  // Buffer ID

                            cout << "Ingrese ID del paciente: ";
                            cin >> idPaciente;

                            bool anomalia = detectarAnomaliaECG(  // Llama función
                                salas,
                                cantidadSalas,
                                idPaciente,
                                configs,
                                cantidadConfigs,
                                true);

                            if (anomalia)
                                cout << "\n>>> El paciente presenta ANOMALIA en ECG.\n";
                            else
                                cout << "\n>>> No se detectaron anomalias en ECG.\n";

                            cin.ignore();
                            cin.get();
                            break;
                        }

                    }

                } while (opcion !=3);

                break;
            }

            case 5: {

                // Submenú para exportar información procesada

                int opcion;

                do{

                    cout << "\n------ EXPORTACION DE DATOS ------\n";
                    cout << "1. Generar reporte de paciente\n";
                    cout << "2. Exportar pacientes con ECG anomalo\n";
                    cout << "3. Volver\n";

                    cout << "Seleccione una opcion: ";

                    cin >> opcion;

                    switch(opcion) {

                        case 1: {

                            // Genera un reporte detallado de un paciente

                            if (cantidadSalas == 0) {
                                cout << "Debe cargar primero el archivo BSF\n";
                                break;
                            }

                            char idPaciente[11];  // Buffer ID

                            cout << "Ingrese ID del paciente: ";
                            cin >> idPaciente;

                            reportePaciente(
                                salas,
                                cantidadSalas,
                                configs,
                                cantidadConfigs,
                                idPaciente);  // Genera reporte

                            cin.ignore();
                            cin.get();
                            break;
                        }

                        case 2: {

                            // Exporta pacientes que presentan ECG anómalo

                            if (cantidadSalas == 0) {
                                cout << "Primero debe cargar el archivo BSF.\n";
                                break;
                            }

                            if (cantidadConfigs == 0) {
                                cout << "Primero debe cargar configuraciones.\n";
                                break;
                            }

                            exportarPacientesECGAnomalo(  // Llama función
                                salas,
                                cantidadSalas,
                                configs,
                                cantidadConfigs);
                            
                            cin.ignore();
                            cin.get();
                            break;
                        }

                    }

                } while (opcion != 3);

                break;  // Sale del case principal
            }

            case 6:
                cout << "\nSaliendo del sistema..." << endl;
                break;
            
            default:
                cout << "Opcion invalida.\n";
                break;
        }

    } while (opcion != 6);  // Repite hasta salir

    // Liberación final de memoria dinámica utilizada por las salas
    if (salas != nullptr) {  // Si salas existe

        for (int s = 0; s < cantidadSalas; s++) {  // Bucle salas

            for (int m = 0; m < (unsigned char)salas[s].NumeroMaquinas; m++) {  // Bucle máquinas

                for (unsigned int j = 0; j < salas[s].maquinas[m].NumeroMediciones; j++) {  // Bucle mediciones

                    delete[] salas[s].maquinas[m].Mediciones[j].lecturas;  // Libera lecturas

                }

                delete[] salas[s].maquinas[m].Mediciones;  // Libera mediciones

            }

            delete[] salas[s].maquinas;  // Libera máquinas
        }

        delete[] salas;  // Libera salas
    }

    // Libera memoria de configuraciones y pacientes
    delete[] configs;  // Libera configs
    delete[] pacientes;  // Libera pacientes

    return 0;  // Finaliza el programa
}



