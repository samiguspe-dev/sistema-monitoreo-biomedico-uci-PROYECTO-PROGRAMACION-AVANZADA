#ifndef DETECTAR_ANOMALIA_H  
#define DETECTAR_ANOMALIA_H  

#include <cstring>  
#include "../libs/CONFIGURACION.H"  

/**
 * Verifica si una lectura de sensor se encuentra fuera de los rangos
 * definidos en la configuración. Si el valor supera los límites mínimo
 * o máximo establecidos para el sensor, se considera una anomalía.
 */
bool esAnomalia(const lectura& l, const ConfigSensor configs[], int cantidadConfigs) {

    // Las lecturas de ECG no se evalúan en esta función
    if (l.TipoSensor == 'E')
        return false;

    // Recorre todas las configuraciones de sensores
    for (int i = 0; i < cantidadConfigs; i++) {

        // Verificación para sensor de temperatura
        if (l.TipoSensor == 'T' &&
            strcmp(configs[i].TipoSensor, "T") == 0) {

            // Comprueba si el valor de temperatura está fuera del rango permitido
            if (l.valor < configs[i].minimo ||
                l.valor > configs[i].maximo)
                return true;

            // Si está dentro del rango se considera normal
            return false;
        }

        // Verificación para sensor de oxígeno
        if (l.TipoSensor == 'O' &&
            strcmp(configs[i].TipoSensor, "O") == 0) {

            // Comprueba si el valor de oxígeno está fuera del rango permitido
            if (l.valor < configs[i].minimo ||
                l.valor > configs[i].maximo)
                return true;

            return false;
        }

        // Verificación para presión sistólica
        if (l.TipoSensor == 'P' &&
            strcmp(configs[i].TipoSensor, "P_SIS") == 0) {

            // Evalúa si la presión sistólica supera los límites establecidos
            if (l.sistolica < configs[i].minimo ||
                l.sistolica > configs[i].maximo)
                return true;
        }

        // Verificación para presión diastólica
        if (l.TipoSensor == 'P' &&
            strcmp(configs[i].TipoSensor, "P_DIA") == 0) {

            // Evalúa si la presión diastólica está fuera del rango permitido
            if (l.diastolica < configs[i].minimo ||
                l.diastolica > configs[i].maximo)
                return true;
        }
    }

    // Si ninguna condición de anomalía se cumple, la lectura se considera normal
    return false;
}

#endif  
