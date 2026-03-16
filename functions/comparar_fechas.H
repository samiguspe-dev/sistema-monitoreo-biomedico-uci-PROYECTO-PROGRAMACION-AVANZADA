#ifndef COMPARAR_FECHAS_H 
#define COMPARAR_FECHAS_H 
 
/**
 * Compara dos fechas representadas como cadenas de caracteres.
 * Retorna true si la fecha f1 es posterior a f2. La comparación
 * se realiza evaluando año, mes, día, hora, minutos, segundos y milisegundos.
 */
bool compararFechas(const char f1[], const char f2[]) {

    // Primero se compara el año (posiciones 6 a 9 de la cadena)
    for (int i = 6; i <= 9; i++) {
        if (f1[i] > f2[i]) {
            return true;   // f1 tiene un año mayor
        }
        if (f1[i] < f2[i]) {
            return false;  // f1 tiene un año menor
        }
    }

    // Si el año es igual, se compara el mes (posiciones 3 y 4)
    for (int i = 3; i <= 4; i++) {
        if (f1[i] > f2[i]) {
            return true;   // f1 tiene un mes posterior
        }
        if (f1[i] < f2[i]) {
            return false;  // f1 tiene un mes anterior
        }
    }

    // Si el mes también es igual, se compara el día (posiciones 0 y 1)
    for (int i = 0; i <= 1; i++) {
        if (f1[i] > f2[i]) {
            return true;   // f1 corresponde a un día posterior
        }
        if (f1[i] < f2[i]) {
            return false;  // f1 corresponde a un día anterior
        }
    }

    // Si el día es igual, se compara la hora (posiciones 11 y 12)
    for (int i = 11; i <= 12; i++) {
        if (f1[i] > f2[i]) {
            return true;   // f1 tiene una hora posterior
        }
        if (f1[i] < f2[i]) {
            return false;  // f1 tiene una hora anterior
        }
    }

    // Si la hora es igual, se comparan los minutos (posiciones 14 y 15)
    for (int i = 14; i <= 15; i++) {
        if (f1[i] > f2[i]) {
            return true;   // f1 tiene minutos posteriores
        }
        if (f1[i] < f2[i]) {
            return false;  // f1 tiene minutos anteriores
        }
    }

    // Si los minutos coinciden, se comparan los segundos (posiciones 17 y 18)
    for (int i = 17; i <= 18; i++) {
        if (f1[i] > f2[i]) {
            return true;   // f1 tiene segundos posteriores
        }
        if (f1[i] < f2[i]) {
            return false;  // f1 tiene segundos anteriores
        }
    }

    // Finalmente se comparan los milisegundos (posiciones 20 a 22)
    for (int i = 20; i <= 22; i++) {
        if (f1[i] > f2[i]) {
            return true;   // f1 tiene milisegundos mayores
        }
        if (f1[i] < f2[i]) {
            return false;  // f1 tiene milisegundos menores
        }
    }

    // Si todas las partes son iguales, las fechas son idénticas
    return false;
} 
        
#endif