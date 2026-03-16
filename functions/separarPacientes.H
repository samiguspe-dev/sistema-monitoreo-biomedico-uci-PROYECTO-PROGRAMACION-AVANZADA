#ifndef SEPARAR_PACIENTES_H  
#define SEPARAR_PACIENTES_H  

/**
 * Separa una línea de texto en campos usando ';' como delimitador.
 * 
 * Recorre la cadena recibida y divide su contenido cada vez que encuentra
 * el carácter ';'. Cada campo obtenido se almacena como una cadena en la
 * matriz `valores` y se retorna el número total de campos encontrados.
 */
int separarPaciente(const char linea[], char valores[][110]){ 

    int i = 0;  // Índice para recorrer carácter por carácter la línea original
    int f = 0;  // Índice de fila en la matriz 'valores' (cada fila es un campo)
    int c = 0;  // Índice de columna dentro del campo actual

    while (linea[i] != '\0'){  // Recorre la cadena hasta encontrar el final

        if (linea[i] != ';'){  // Si el carácter actual no es un separador

            valores[f][c] = linea[i];  // Copia el carácter en el campo actual
            c++;  // Avanza a la siguiente posición dentro del campo

        } 
        else{  // Si se encuentra el separador ';' significa fin de un campo

            valores[f][c] = '\0';  // Finaliza la cadena actual con terminador nulo

            // Verifica si el campo inicia con un espacio en blanco
            if(valores[f][0] == ' '){

                // Desplaza la cadena una posición a la izquierda eliminando el espacio
                memmove(valores[f], valores[f] + 1, strlen(valores[f]));
            }

            f++;  // Pasa a la siguiente fila de la matriz (nuevo campo)
            c = 0;  // Reinicia la columna para comenzar a llenar el nuevo campo
        }

        i++;  // Avanza al siguiente carácter de la línea
    }

    valores[f][c] = '\0';  // Finaliza el último campo de la línea

    // Verifica si el último campo también tiene un espacio inicial
    if(valores[f][0] == ' '){

        // Elimina el espacio inicial desplazando el contenido
        memmove(valores[f], valores[f] + 1, strlen(valores[f]));
    }

    return f + 1;  // Retorna el número total de campos encontrados
}

#endif  