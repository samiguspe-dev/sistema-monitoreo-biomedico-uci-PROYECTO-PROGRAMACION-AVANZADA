#ifndef SEPARARCONFIG_H  
#define SEPARARCONFIG_H  

/**
 * Separa una línea de texto usando ',' como delimitador.
 * 
 * Recorre la cadena recibida y divide su contenido cada vez que encuentra
 * una coma. Cada campo obtenido se almacena en la matriz `valores` y la
 * función retorna la cantidad total de campos encontrados.
 */
int separarConfig(char linea[], char valores[][20]){

    int i = 0;  // Índice para recorrer la cadena original
    int f = 0;  // Índice de fila en la matriz 'valores' (cada fila es un campo)
    int c = 0;  // Índice de columna dentro del campo actual

    while (linea[i] != '\0'){  // Recorre la línea hasta el final de la cadena

        if (linea[i] != ','){  // Si el carácter no es una coma

            valores[f][c] = linea[i];  // Copia el carácter en el campo actual
            c++;  // Avanza a la siguiente posición del campo

        } 
        else{  // Si encuentra ',' significa que terminó un campo

            valores[f][c] = '\0';  // Finaliza la cadena actual
            f++;  // Pasa a la siguiente fila (nuevo campo)
            c = 0;  // Reinicia la columna para el nuevo campo
        }

        i++;  // Avanza al siguiente carácter de la línea
    }

    valores[f][c] = '\0';  // Finaliza el último campo de la línea

    return f + 1;  // Retorna la cantidad total de campos separados
}

#endif  