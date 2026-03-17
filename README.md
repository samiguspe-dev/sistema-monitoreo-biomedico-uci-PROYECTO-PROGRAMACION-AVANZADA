# sistema-monitoreo-biomedico-uci-PROYECTO-PROGRAMACION-AVANZADA
Sistema de monitoreo biomédico para análisis de mediciones UCI y detección de anomalías en sensores médicos.

## Autores
*Samuel Gustavo Pedraza Martinez

*Andrés Felipe Rodríguez Coronado

---

# Sistema de Monitoreo Biomédico UCI

## Descripción del proyecto

Este proyecto implementa un sistema en C++ para el análisis de mediciones biomédicas en una Unidad de Cuidados Intensivos (UCI).  
El programa permite procesar información proveniente de sensores médicos, detectar anomalías en las lecturas y generar reportes útiles para el análisis clínico.

Se trabajan datos como temperatura, oxígeno en sangre, presión arterial y señales ECG, permitiendo identificar valores fuera de rangos normales definidos en un archivo de configuración.

---

## Estructura general del sistema

El sistema está organizado en varias carpetas para facilitar su lectura y mantenimiento:

- `datos/`  
  Contiene los archivos de entrada utilizados por el programa.

- `funciones/`  
  Implementación de las funciones principales del sistema (lectura de archivos, procesamiento, reportes).

- `bibliotecas/`  
  Definición de estructuras como paciente, medición, lectura, etc.

- `main.cpp`  
  Punto de entrada del programa. Contiene el menú principal y controla el flujo del sistema.

- `programa.exe`  
  Ejecutable del sistema (puede generarse nuevamente mediante compilación).

---

## Archivos utilizados

Los archivos de entrada se encuentran en la carpeta `datos/`:

- `configuracion.txt`  
  Contiene los rangos mínimos y máximos permitidos para cada sensor.

- `pacientes_small.csv`  
  Contiene la información de los pacientes.

- `patient_readings_simulation.bsf`  
  Archivo binario con las mediciones biomédicas.

---

## Archivos generados por el programa

Durante la ejecución, el sistema puede generar:

- `anomalias.txt`  
  Reporte general de anomalías detectadas.

- `mediciones_paciente_<ID>.txt`  
  Reporte detallado de un paciente específico.

- `pacientes_ecg_anomalos.dat`  
  Archivo binario con pacientes que presentan anomalías en ECG.

---

## Funcionalidades del sistema

El programa permite:

1. Cargar configuraciones de sensores.
2. Cargar datos de pacientes.
3. Leer archivo binario con mediciones biomédicas.
4. Detectar anomalías en:
   - Temperatura
   - Oxígeno
   - Presión arterial
5. Detectar anomalías en señales ECG.
6. Generar reportes de anomalías.
7. Generar reportes individuales por paciente.
8. Exportar pacientes con ECG anómalo a archivo binario.

---

## Flujo de uso del programa

Para un funcionamiento correcto, el usuario debe seguir este orden:

1. Ejecutar el programa.
2. Seleccionar opción 1:
   - Cargar configuraciones y pacientes.
3. Seleccionar opción 2:
   - Leer archivo BSF.
4. A partir de aquí se pueden usar:
   - Opción 3 → generar reporte de anomalías
   - Opción 4 → análisis y estadísticas
   - Opción 5 → exportación de datos

Si no se sigue este orden, el programa mostrará mensajes de error.

---

## Compilación del programa

### Requisitos

- Compilador C++ (g++ recomendado)
- Sistema operativo Windows, Linux o similar

### Pasos

1. Descargar el repositorio (ZIP o clonar):

```bash
git clone https://github.com/TU_USUARIO/sistema-monitoreo-biomedico-uci.git

