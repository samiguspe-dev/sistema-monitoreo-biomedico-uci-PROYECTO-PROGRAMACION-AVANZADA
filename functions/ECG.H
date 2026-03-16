#ifndef ECG_H  
#define ECG_H  

#include <cmath>  
#include "../libs/MEDICION.H"  
#include "../libs/CONFIGURACION.H"  
#include "../libs/LECTURA.H"  

/**
 * Determina si un paciente presenta una anomalía en las lecturas de ECG.
 * Para ello busca todas las lecturas ECG del paciente, obtiene el valor
 * mínimo y máximo registrados y los compara con los límites definidos
 * en la configuración de sensores.
 */
bool detectarAnomaliaECG(const salaUCI salas[], int cantidadSalas,
                         const char idPaciente[11],
                         const ConfigSensor configs[], int cantidadConfigs,
                         bool debug){

    double minECG = 0;  // Valor mínimo de ECG encontrado para el paciente
    double maxECG = 0;  // Valor máximo de ECG encontrado para el paciente
    bool encontrado = false;  // Indica si se encontró al menos una lectura ECG

    // ===== 1. Buscar todas las lecturas ECG del paciente =====
    for (int s = 0; s < cantidadSalas; s++) {  // Recorre todas las salas

        for (int m = 0; m < (unsigned char)salas[s].NumeroMaquinas; m++) {  
        // Recorre todas las máquinas de cada sala

            for (unsigned int j = 0; j < salas[s].maquinas[m].NumeroMediciones; j++) {  
            // Recorre todas las mediciones registradas

                medicion* med =&salas[s].maquinas[m].Mediciones[j];  
                // Obtiene un puntero a la medición actual

                if (strncmp(med->Idpaciente,idPaciente, 11) != 0)  
                    // Verifica si la medición pertenece al paciente buscado
                    continue;  // Si no coincide, pasa a la siguiente medición

                for (unsigned int k = 0; k < med->NumeroLecturas; k++) {  
                // Recorre todas las lecturas dentro de la medición

                    lectura* l = &med->lecturas[k];  
                    // Obtiene la lectura actual

                    if (l->TipoSensor != 'E')  
                        // Verifica si la lectura corresponde a un sensor ECG
                        continue;  // Si no es ECG se ignora

                    if (!encontrado) {  
                        // Si es la primera lectura ECG encontrada

                        minECG = maxECG = l->valor;  
                        // Inicializa los valores mínimo y máximo con esta lectura

                        encontrado = true;  
                        // Marca que ya se encontró al menos una lectura ECG

                    } else {  
                        // Si ya existían lecturas ECG previas

                        if (l->valor < minECG)  
                            // Actualiza el mínimo si el valor actual es menor
                            minECG = l->valor;

                        if (l->valor > maxECG)  
                            // Actualiza el máximo si el valor actual es mayor
                            maxECG = l->valor;
                    }
                }
            }
        }
    }

    if (!encontrado)  
        // Si no se encontró ninguna lectura ECG para el paciente
        return false;  // No se puede evaluar anomalía

    // ===== 2. Buscar los límites configurados para ECG =====

    double limiteInferior = 0;  // Límite inferior permitido
    double limiteSuperior = 0;  // Límite superior permitido
    bool configEncontrada = false;  // Indica si se encontró la configuración ECG

    for (int i = 0; i < cantidadConfigs; i++) {  
    // Recorre todas las configuraciones de sensores

        if (strcmp(configs[i].TipoSensor, "E") == 0) {  
        // Verifica si la configuración corresponde al sensor ECG

            limiteInferior = configs[i].minimo;  
            // Guarda el valor mínimo permitido

            limiteSuperior = configs[i].maximo;  
            // Guarda el valor máximo permitido

            configEncontrada = true;  
            // Marca que la configuración fue encontrada

            break;  // Termina la búsqueda
        }
    }

    if (!configEncontrada){  
        // Si no existe configuración para ECG
        cout << "ERROR: No se encontro configuracion para ECG.\n";
        return false;
    }

    // 3. Aplicar fórmula para detectar anomalía 

    double sumaPaciente = fabs(minECG) + fabs(maxECG);  
    // Calcula la suma de los valores absolutos del mínimo y máximo del paciente

    double sumaLimites = fabs(limiteInferior) + fabs(limiteSuperior);  
    // Calcula la suma de los valores absolutos de los límites permitidos

    if(debug){  
    // Si el modo debug está activo, muestra los valores usados en el cálculo

        cout << "minECG = " << minECG << endl;
        cout << "maxECG = " << maxECG << endl;

        cout << "sumaPaciente = "
             << fabs(minECG) + fabs(maxECG) << endl;

        cout << "sumaLimites = "
             << fabs(limiteInferior) + fabs(limiteSuperior) << endl;
    }

    return (sumaPaciente > sumaLimites);  
    // Retorna true si la suma del paciente supera los límites permitidos
}

#endif  