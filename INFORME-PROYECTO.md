# INFORME DEL PROYECTO

## Sistema de Monitoreo Biomédico en UCI

---

## 1. Introducción

El presente proyecto implementa un sistema en lenguaje C++ orientado al procesamiento y análisis de datos biomédicos en un entorno simulado de Unidad de Cuidados Intensivos (UCI).

El sistema permite manejar información proveniente de múltiples sensores médicos, procesar grandes volúmenes de datos almacenados en archivos de diferentes formatos y generar reportes útiles para la detección de anomalías.

Se hace uso intensivo de estructuras dinámicas, manejo de memoria, lectura de archivos binarios y organización jerárquica de datos.

---

## 2. Librerías estándar utilizadas

### 2.1 iostream

Esta librería se utiliza para la entrada y salida de datos en consola.

Funciones utilizadas:

* `cout` para mostrar información al usuario
* `cin` para capturar entradas del usuario
* `endl` para saltos de línea

Uso en el proyecto:

* Menú interactivo
* Mensajes de error
* Visualización de resultados

---

### 2.2 fstream

Permite el manejo de archivos.

Clases utilizadas:

* `ifstream` → lectura de archivos de texto
* `ofstream` → escritura de archivos
* `fstream` → lectura/escritura binaria

Funciones clave:

* `open()` → abrir archivo
* `read()` → lectura binaria
* `write()` → escritura binaria
* `getline()` → lectura de líneas
* `close()` → cerrar archivo

Uso en el proyecto:

* Lectura de configuraciones
* Lectura de pacientes
* Lectura de archivo binario (.bsf)
* Generación de reportes

---

### 2.3 cstring

Permite manipulación de cadenas tipo `char[]`.

Funciones utilizadas:

* `strcpy()` → copiar cadenas
* `strcmp()` → comparar cadenas
* `strncmp()` → comparar parcialmente
* `strlen()` → longitud de cadena
* `memmove()` → mover datos en memoria

Uso:

* Manejo de IDs
* Procesamiento de datos CSV
* Comparaciones de pacientes

---

### 2.4 cmath

Permite operaciones matemáticas.

Funciones utilizadas:

* `fabs()` → valor absoluto

Uso:

* Cálculo de anomalías en ECG

---

### 2.5 cstdlib

Funciones utilizadas:

* `atoi()` → convertir texto a entero
* `atof()` → convertir texto a decimal

Uso:

* Conversión de datos leídos desde archivos

---

## 3. Estructuras implementadas

### 3.1 ConfigSensor

Define los rangos permitidos para cada sensor.

Campos:

* TipoSensor
* minimo
* maximo

Función:
Permite validar si una lectura está dentro de valores normales.

---

### 3.2 lectura

Representa una lectura individual de un sensor.

Campos:

* TipoSensor
* valor
* sistolica
* diastolica

Función:
Almacena el valor medido por un sensor.

---

### 3.3 medicion

Agrupa varias lecturas realizadas en un instante.

Campos:

* Idpaciente
* FechaHora
* NumeroLecturas
* lecturas

Función:
Representa una medición completa en el tiempo.

---

### 3.4 maquinaUCI

Representa un dispositivo médico.

Campos:

* Idmaquina
* NumeroMediciones
* Mediciones

Función:
Agrupa mediciones realizadas por una máquina.

---

### 3.5 salaUCI

Representa una sala hospitalaria.

Campos:

* IdSala
* NumeroMaquinas
* maquinas

Función:
Agrupa máquinas dentro de una sala.

---

### 3.6 Paciente

Almacena información del paciente.

Campos:

* Identificación
* Nombre
* Datos personales

Función:
Relacionar mediciones con pacientes reales.

---

### 3.7 MedicionesPaciente

Estructura auxiliar para agrupar mediciones por paciente.

Función:
Facilitar generación de reportes.

---

## 4. Descripción de funciones implementadas

### separarPaciente

Divide una línea CSV en campos.

Uso:
Procesar archivo de pacientes.

---

### separarConfig

Divide una línea de configuración.

Uso:
Procesar archivo de sensores.

---

### leer_binario

Lee el archivo `.bsf`.

Proceso:

* Lee salas
* Lee máquinas
* Lee mediciones
* Lee lecturas

Uso:
Construir toda la estructura del sistema.

---

### generarReporteAnomalias

Recorre todas las lecturas y detecta anomalías.

Genera:

* archivo `anomalias.txt`

---

### esAnomalia

Evalúa si una lectura está fuera de rango.

Uso:
Comparación con configuración.

---

### detectarAnomaliaECG

Evalúa anomalías en ECG.

Método:

* calcula extremos
* compara con límites

---

### reportePaciente

Genera reporte detallado por paciente.

Incluye:

* mediciones
* estadísticas
* anomalías

---

### exportarPacientesECGAnomalo

Exporta pacientes con ECG anómalo.

Formato:

* archivo binario

---

### cargarConfiguraciones

Lee archivo de configuraciones.

---

### cargarPacientes

Lee archivo CSV de pacientes.

---

### contarLineas

Cuenta líneas de un archivo.

Uso:
dimensionar memoria.

---

## 5. Manejo de buffers y datos irrelevantes

Durante la lectura de archivos se utilizan buffers (`char[]`) que pueden contener datos adicionales.

Para evitar errores:

* se limita el tamaño de lectura
* se asegura terminador `\0`
* se ignoran datos fuera de formato

Esto evita procesar información inválida.

---

## 6. Gestión de memoria

El sistema utiliza memoria dinámica para:

* salas
* máquinas
* mediciones
* lecturas
* pacientes

Se implementa:

* liberación manual (`delete[]`)
* redimensionamiento dinámico
* control de punteros

Esto evita fugas de memoria.

---

## 7. Validaciones implementadas

* Verificación de apertura de archivos
* Control de entrada del usuario
* Validación de datos leídos
* Control de duplicados
* Validación de sensores

---

## 8. Uso de inteligencia artificial

Durante el desarrollo del proyecto se utilizó ChatGPT como herramienta de apoyo en:

* Corrección de errores en código
* Explicación de funciones
* Mejora de estructura del programa
* Documentación detallada
* Organización del repositorio
* Optimización del manejo de memoria
* Clarificación de lógica en lectura de archivos binarios

Las recomendaciones obtenidas fueron aplicadas de forma crítica para mejorar la calidad del sistema.

---

## 9. Conclusión

El proyecto demuestra el uso de estructuras complejas, manejo de memoria dinámica, lectura de archivos binarios y procesamiento de datos en C++.

Se logró implementar un sistema robusto capaz de analizar información biomédica y generar resultados útiles para el monitoreo de pacientes.
