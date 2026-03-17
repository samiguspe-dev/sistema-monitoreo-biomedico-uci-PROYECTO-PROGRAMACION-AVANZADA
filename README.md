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

# Compilación y ejecución del programa

El proyecto fue desarrollado en **C++** y puede ejecutarse utilizando **Visual Studio Code** o cualquier compilador compatible (como g++).

El sistema utiliza rutas relativas, por lo que es importante no modificar la estructura del proyecto para garantizar el acceso correcto a los archivos.

---

## 1. Descargar y preparar el proyecto

El proyecto puede descargarse como archivo `.zip`.

Pasos:

1. Descargar el repositorio
2. Descomprimir el archivo en cualquier carpeta
3. Verificar que la estructura del proyecto sea la siguiente:

```
sistema-monitoreo-biomedico-uci
│
├── datos
│   ├── configuracion.txt
│   ├── pacientes_small.csv
│   └── patient_readings_simulation.bsf
│
├── funciones
│   ├── separar_pacientes.h
│   ├── separar_config.h
│   ├── leer_binario.h
│   ├── generar_reporte_anomalias.h
│   ├── reporte_paciente.h
│   ├── detectar_anomalia_ecg.h
│   ├── exportar_ecg_anomalo.h
│   ├── es_anomalia.h
│   ├── comparar_fechas.h
│   ├── cargar_configuraciones.h
│   ├── cargar_pacientes.h
│   └── contar_lineas.h
│
├── bibliotecas
│   ├── SALAUCI.h
│   ├── MAQUINAUCI.h
│   ├── MEDICION.h
│   ├── LECTURA.h
│   ├── PACIENTE.h
│   ├── MEDICIONES_PACIENTE.h
│   ├── CONFIGURACION.h
│   └── ARCHIVOPA.h
│
├── main.cpp
├── programa.exe
└── README.md
```
La carpeta `funciones/` contiene la implementación de la lógica del sistema, mientras que `bibliotecas/` define las estructuras utilizadas para organizar los datos.

La carpeta `datos/` contiene todos los archivos necesarios para la ejecución del sistema.

---

## 2. Abrir el proyecto

1. Abrir Visual Studio Code
2. Seleccionar **Open Folder**
3. Elegir la carpeta:

```
sistema-monitoreo-biomedico-uci
```

Esto cargará todos los archivos del sistema.

---

## 3. Compilar el programa

Si no deseas usar el ejecutable incluido, puedes compilar manualmente.

Abrir una terminal en la carpeta del proyecto y ejecutar:

```
g++ main.cpp -o programa.exe
```

Si el proyecto tiene múltiples archivos `.cpp`, usar:

```
g++ *.cpp -o programa
```

Esto generará el archivo ejecutable del programa.

---

## 4. Ejecutar el programa

Desde la carpeta principal del proyecto:

En Windows:

```
programa.exe
```

En Linux o Mac:

```
./programa
```

Es importante ejecutar el programa desde la carpeta raíz, ya que los archivos en la carpeta `datos/` se cargan mediante rutas relativas.

---

## 5. Ubicación de los componentes del sistema

* `main.cpp` contiene el menú principal y el flujo del programa
* `bibliotecas/` contiene las estructuras del sistema
* `funciones/` contiene la implementación de la lógica del programa
* `datos/` contiene los archivos de entrada

---

## 6. Funcionamiento del programa

Al ejecutarse, el sistema muestra un menú con las siguientes opciones:

1. Cargar archivo de configuracion y datos de pacientes
2. Leer archivo .bsf
3. Generar reporte de anomalias
4. Calcular estadisticas
5. Exportar datos procesados
6. Salir

Cada opción ejecuta una funcionalidad específica dentro del sistema.

---

## 7. Flujo recomendado de ejecución

Para evitar errores, se recomienda seguir este orden:

**Paso 1: Cargar configuración y pacientes (Opción 1)**

* Lee `datos/configuracion.txt`
* Carga los rangos permitidos
* Lee `datos/pacientes_small.csv`
* Guarda los pacientes en memoria

**Paso 2: Leer archivo binario (Opción 2)**

* Abre `datos/patient_readings_simulation.bsf`
* Lee las salas, máquinas, mediciones y lecturas
* Carga toda la información en memoria


**Paso 3: Generar reporte de anomalías (Opción 3)**

* Analiza las lecturas
* Detecta valores fuera de rango
* Genera el archivo `anomalias.txt`

**Paso 4: Análisis de datos (Opción 4)**

Al escoger la opcion 4 se abrira un sub-menu en la terminal que mostrara 

* Detecta lecturas anómalas
* Evalúa anomalías en ECG

**Paso 5: Exportación de datos (Opción 5)**

* Genera reportes individuales
* Exporta pacientes con ECG anómalo al archivo `pacientes_ecg_anomalos.dat`

---

## 8. Consideraciones importantes

* Ejecutar siempre desde la carpeta raíz del proyecto
* No mover la carpeta `datos/`
* Los archivos de salida se generan automáticamente
* El sistema incluye validaciones para evitar errores durante la ejecución

