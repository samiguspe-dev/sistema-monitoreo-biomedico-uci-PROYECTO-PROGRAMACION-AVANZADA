# INFORME DEL PROYECTO

## Sistema de Monitoreo Biomédico en UCI

---

## Descripción general del sistema

El presente proyecto consiste en el desarrollo de un sistema en lenguaje C++ orientado al procesamiento, análisis y gestión de mediciones biomédicas simuladas dentro de un entorno de Unidad de Cuidados Intensivos (UCI).

El sistema permite trabajar con múltiples fuentes de datos, incluyendo archivos de configuración, archivos de pacientes en formato CSV y archivos binarios que contienen mediciones médicas generadas por máquinas de monitoreo.

A partir de estos datos, el programa es capaz de:

* Organizar la información en estructuras jerárquicas.
* Analizar lecturas fisiológicas.
* Detectar anomalías en los valores registrados.
* Generar reportes detallados.
* Exportar información relevante a archivos binarios.

El sistema está diseñado bajo un enfoque modular, donde cada componente cumple una función específica dentro del flujo general del programa.

---

## Librerías utilizadas en el proyecto

El correcto funcionamiento del sistema depende del uso de diversas librerías estándar de C++, las cuales permiten manejar entrada/salida, procesamiento de texto, operaciones matemáticas y manipulación de memoria.

A continuación se describen cada una de ellas en detalle.

---

### <iostream>

Esta librería permite manejar la entrada y salida estándar del programa.

Se utilizaron principalmente los siguientes elementos:

* `cout`
  Permite imprimir información en la consola. Se utiliza para mostrar menús, resultados, mensajes de error y confirmaciones.

* `cin`
  Permite capturar la entrada del usuario. Es utilizado para seleccionar opciones del menú e ingresar datos como el ID del paciente.

* `endl`
  Inserta un salto de línea y fuerza el vaciado del buffer de salida.

Uso dentro del sistema:

Esta librería es fundamental para la interacción del usuario con el programa, especialmente en el menú principal y en la visualización de resultados.

---

### <fstream>

Esta librería permite el manejo de archivos tanto de texto como binarios.

Clases utilizadas:

* `ifstream` → lectura de archivos de texto
* `ofstream` → escritura de archivos
* `fstream` → lectura y escritura de archivos binarios

Funciones utilizadas:

* `open()` → abrir archivos
* `close()` → cerrar archivos
* `read()` → lectura binaria
* `write()` → escritura binaria
* `getline()` → lectura de líneas

Modos de apertura utilizados:

* `ios::in` → lectura
* `ios::out` → escritura
* `ios::binary` → manejo de archivos binarios

Uso dentro del sistema:

* Lectura del archivo de configuración
* Lectura del archivo de pacientes
* Lectura del archivo binario `.bsf`
* Generación de archivos de salida (reportes y exportaciones)

---

### <cstring>

Esta librería permite trabajar con cadenas tipo C (`char[]`).

Funciones utilizadas:

* `strcpy()` → copia cadenas de caracteres
* `strcmp()` → compara cadenas
* `strncmp()` → compara parcialmente
* `strlen()` → obtiene la longitud de una cadena
* `memmove()` → mueve bloques de memoria

Uso dentro del sistema:

Se utiliza principalmente en:

* Comparación de identificadores de pacientes
* Copia de datos leídos desde archivos
* Eliminación de espacios en cadenas
* Manipulación de buffers de texto

---

### <cmath>

Esta librería proporciona funciones matemáticas.

Función utilizada:

* `fabs()` → valor absoluto de un número

Uso dentro del sistema:

Se utiliza en la detección de anomalías en señales ECG, donde se requiere trabajar con magnitudes absolutas de valores.

---

### <cstdlib>

Esta librería permite realizar conversiones entre tipos de datos.

Funciones utilizadas:

* `atoi()` → convierte texto a entero
* `atof()` → convierte texto a double

Uso dentro del sistema:

Se utiliza al momento de cargar configuraciones y pacientes desde archivos de texto, donde los datos inicialmente son leídos como cadenas.

---

## Explicación de las estructuras implementadas

El sistema está basado en una estructura jerárquica que permite organizar los datos de manera similar a un entorno hospitalario real.

La jerarquía es la siguiente:

Sala → Maquinas → Mediciones → Lecturas

---

### salaUCI

Representa una sala dentro de la UCI.

Atributos:

* `IdSala`
  Identificador de la sala.

* `NumeroMaquinas`
  Cantidad de máquinas presentes en la sala.

* `maquinas`
  Puntero a un arreglo dinámico de estructuras `maquinaUCI`.

Función dentro del sistema:

Permite agrupar múltiples máquinas dentro de una misma unidad de monitoreo.

---

### maquinaUCI

Representa una máquina de monitoreo médico.

Atributos:

* `Idmaquina`
  Identificador de la máquina.

* `NumeroMediciones`
  Cantidad de mediciones registradas.

* `Mediciones`
  Arreglo dinámico de estructuras `medicion`.

Función:

Almacenar todas las mediciones realizadas por un dispositivo.

---

### medicion

Representa un conjunto de lecturas en un instante determinado.

Atributos:

* `Idpaciente`
  Identificador del paciente.

* `FechaHora`
  Momento en el que se realizó la medición.

* `NumeroLecturas`
  Cantidad de lecturas registradas.

* `lecturas`
  Arreglo dinámico de estructuras `lectura`.

Función:

Agrupar todas las lecturas fisiológicas registradas en un momento específico.

---

### lectura

Representa una lectura individual de un sensor.

Atributos:

* `TipoSensor`
  Tipo de sensor (T, O, P, E).

* `valor`
  Valor numérico (temperatura, oxígeno, ECG).

* `sistolica`
  Presión sistólica.

* `diastolica`
  Presión diastólica.

Función:

Es la unidad básica de información del sistema.

---

### ConfigSensor

Representa la configuración de un sensor.

Atributos:

* `TipoSensor`
* `minimo`
* `maximo`

Función:

Define los rangos permitidos para cada tipo de sensor.

---

### Paciente

Representa la información de un paciente.

Atributos:

Incluyen datos personales como:

* identificación
* nombre
* contacto
* entidad de salud

Función:

Relacionar mediciones con pacientes reales.

---

### MedicionesPaciente

Estructura auxiliar.

Atributos:

* `id`
* `mediciones`
* `cantidad`
* `capacidad`

Función:

Agrupar mediciones por paciente para facilitar reportes.

---

### archivoPacien

Estructura auxiliar para manejar pacientes.

Atributos:

* `pacientes`
* `cantPacientes`

Función:

Gestionar el conjunto de pacientes cargados.

---

## Manejo de buffers y almacenamiento temporal

El sistema utiliza arreglos de tipo `char[]` como buffers para almacenar información leída desde archivos.

Estos buffers tienen un tamaño fijo definido previamente, lo cual permite controlar el uso de memoria y evitar desbordamientos.

Ejemplos:

* `char lineaChar[100]`
* `char valores[3][20]`

Características importantes:

* Siempre se asegura la terminación con `\0`.
* Se controla el tamaño máximo de copia.
* Se eliminan espacios innecesarios.

Esto es importante porque muchos datos provienen de archivos externos, los cuales pueden contener información no estructurada.

El uso de buffers permite manejar esta información de forma segura antes de convertirla en estructuras del sistema.

## Descripción de las funciones implementadas

En esta sección se describe el funcionamiento de las principales funciones desarrolladas dentro del sistema.
Cada función cumple un rol específico dentro del flujo general del programa, permitiendo la carga de datos, procesamiento, análisis y generación de resultados.

---

### separarPaciente

```cpp
int separarPaciente(const char linea[], char valores[][110])
```

Esta función tiene como objetivo dividir una línea de texto proveniente del archivo de pacientes en múltiples campos, utilizando el carácter ';' como delimitador.

Funcionamiento:

1. Se recorre la cadena carácter por carácter.
2. Cada vez que se encuentra un ';', se considera que se ha terminado un campo.
3. Se almacena el campo en el arreglo bidimensional `valores`.
4. Se asegura que cada cadena termine con '\0'.
5. Se eliminan espacios iniciales si existen.
6. Se retorna la cantidad total de campos encontrados.

Uso en el sistema:

Se utiliza al momento de leer el archivo CSV de pacientes para separar cada atributo antes de cargarlo en la estructura `Paciente`.

---

### separarConfig

```cpp
int separarConfig(char linea[], char valores[][20])
```

Esta función divide una línea del archivo de configuración utilizando ',' como delimitador.

Funcionamiento:

1. Recorre la línea carácter por carácter.
2. Separa los valores en:

   * tipo de sensor
   * valor mínimo
   * valor máximo
3. Almacena cada valor en el arreglo `valores`.
4. Retorna la cantidad de elementos obtenidos.

Uso:

Permite transformar cada línea del archivo de configuración en datos utilizables por el sistema.

---

### cargarConfig

```cpp
ConfigSensor cargarConfig(char valores[][20])
```

Esta función construye una estructura `ConfigSensor` a partir de los valores previamente separados.

Funcionamiento:

1. Copia el tipo de sensor.
2. Convierte los valores mínimo y máximo de texto a tipo `double`.
3. Retorna la estructura completamente inicializada.

Uso:

Se utiliza dentro de la carga de configuraciones.

---

### cargarPaciente

```cpp
Paciente cargarPaciente(char valores[][110], int cantidad)
```

Esta función construye una estructura `Paciente` a partir de los datos separados del archivo CSV.

Funcionamiento:

1. Convierte el ID del paciente a entero.
2. Copia cada campo del paciente utilizando `strcpy`.
3. Maneja el caso en que no exista el campo de medicina prepagada.
4. Retorna la estructura cargada.

Uso:

Se utiliza al cargar el archivo de pacientes en memoria.

---

### contarLineas

```cpp
int contarLineas(const char nombreArchivo[])
```

Esta función cuenta la cantidad de líneas de un archivo.

Funcionamiento:

1. Abre el archivo en modo lectura.
2. Lee cada línea utilizando `getline`.
3. Incrementa un contador.
4. Retorna la cantidad total de líneas.

Uso:

Permite dimensionar arreglos dinámicos antes de cargar datos.

---

### cargarConfiguraciones

```cpp
int cargarConfiguraciones(const char nombreArchivo[], ConfigSensor configs[])
```

Esta función carga todas las configuraciones desde un archivo.

Funcionamiento:

1. Abre el archivo.
2. Lee cada línea.
3. La convierte a `char[]`.
4. Llama a `separarConfig`.
5. Llama a `cargarConfig`.
6. Almacena el resultado en el arreglo.

Retorna:

Cantidad total de configuraciones cargadas.

---

### cargarPacientes

```cpp
int cargarPacientes(const char nombreArchivo[], Paciente pacientes[])
```

Esta función carga todos los pacientes desde un archivo CSV.

Funcionamiento:

1. Abre el archivo.
2. Lee cada línea.
3. Convierte la línea a `char[]`.
4. Llama a `separarPaciente`.
5. Llama a `cargarPaciente`.
6. Almacena el resultado.

Retorna:

Cantidad total de pacientes cargados.

---

### leer_binario

```cpp
int leer_binario(salaUCI*& salas)
```

Esta es una de las funciones más importantes del sistema.

Su objetivo es leer el archivo binario `.bsf` y construir toda la estructura jerárquica del sistema.

Funcionamiento:

1. Abre el archivo en modo binario.
2. Reserva memoria dinámica para salas.
3. Lee:

   * ID de sala
   * número de máquinas
4. Para cada máquina:

   * lee ID
   * número de mediciones
5. Para cada medición:

   * lee ID paciente
   * fecha
   * número de lecturas
6. Para cada lectura:

   * lee tipo de sensor
   * lee valores correspondientes

Además:

* Redimensiona dinámicamente el arreglo de salas.
* Maneja errores de lectura.
* Retorna la cantidad de salas cargadas.

---

### esAnomalia

```cpp
bool esAnomalia(const lectura& l, const ConfigSensor configs[], int cantidadConfigs)
```

Esta función determina si una lectura es anómala.

Funcionamiento:

1. Si el sensor es ECG, no se evalúa.
2. Para cada configuración:

   * compara el tipo de sensor
   * verifica si el valor está fuera del rango
3. Retorna `true` si hay anomalía.

---

### generarReporteAnomalias

```cpp
void generarReporteAnomalias(...)
```

Esta función analiza todas las lecturas del sistema y genera un reporte de anomalías.

Funcionamiento:

1. Agrupa mediciones por paciente.
2. Detecta si existe al menos una anomalía.
3. Si existe:

   * imprime información del paciente
   * imprime cada anomalía detectada
4. Escribe el resultado en un archivo de texto.

Características importantes:

* Manejo dinámico de memoria.
* Filtrado de datos por tipo de sensor.
* Evaluación con configuraciones.

---

### compararFechas

```cpp
bool compararFechas(const char f1[], const char f2[])
```

Compara dos fechas en formato texto.

Funcionamiento:

1. Compara año, mes, día, hora, minutos y segundos.
2. Retorna `true` si f1 es mayor que f2.

Uso:

Ordenamiento o comparación temporal.

---

### reportePaciente

```cpp
void reportePaciente(...)
```

Genera un reporte completo de un paciente.

Incluye:

* Lecturas organizadas por tipo
* Identificación de anomalías
* Cálculo de estadísticas (min, max, promedio)

Funcionamiento:

1. Busca todas las mediciones del paciente.
2. Agrupa en un arreglo dinámico.
3. Recorre cada lectura.
4. Calcula estadísticas.
5. Genera archivo de salida.

---

### detectarAnomaliaECG

```cpp
bool detectarAnomaliaECG(...)
```

Detecta anomalías en señales ECG.

Funcionamiento:

1. Encuentra mínimo y máximo del paciente.
2. Obtiene límites desde configuración.
3. Calcula suma de valores absolutos.
4. Compara con límites.
5. Retorna resultado.

---

### exportarPacientesECGAnomalo

```cpp
void exportarPacientesECGAnomalo(...)
```

Exporta pacientes con ECG anómalo a archivo binario.

Funcionamiento:

1. Evita duplicados.
2. Detecta anomalías.
3. Cuenta lecturas ECG.
4. Escribe:

   * ID paciente
   * cantidad de lecturas
   * datos de cada lectura

---

## Observaciones importantes del diseño

* Se utilizan estructuras dinámicas para adaptarse al tamaño de los datos.
* Se evita duplicación de información mediante validaciones.
* Se implementa separación clara entre lectura, procesamiento y salida.
* Se prioriza el uso de punteros para eficiencia en memoria.

## Descripción del flujo principal del programa (main)

La función `main()` es el punto de entrada del sistema y se encarga de controlar todo el flujo de ejecución mediante un menú interactivo.

El programa está diseñado para ejecutarse de forma secuencial guiada, donde el usuario selecciona distintas opciones que habilitan funcionalidades específicas.

---

### Inicialización de variables

Antes de iniciar el menú, se definen las variables principales del sistema:

* `salaUCI* salas`
  Arreglo dinámico que almacenará todas las salas leídas desde el archivo binario.

* `ConfigSensor* configs`
  Arreglo dinámico de configuraciones.

* `Paciente* pacientes`
  Arreglo dinámico de pacientes.

* Variables auxiliares:

  * `cantidadSalas`
  * `cantidadConfigs`
  * `cantidadPacientes`

Estas variables permiten mantener el estado del sistema durante la ejecución.

---

### Estructura del menú principal

El programa utiliza un ciclo `do-while` que mantiene activo el sistema hasta que el usuario decide salir.

El menú contiene las siguientes opciones:

1. Cargar configuraciones y pacientes
2. Leer archivo binario
3. Generar reporte de anomalías
4. Calcular estadísticas
5. Exportar datos
6. Salir

---

### Validación de entrada del usuario

Antes de procesar la opción, se valida que la entrada sea correcta:

* Si el usuario ingresa un valor inválido:

  * Se limpia el buffer con `cin.clear()`
  * Se descarta la entrada con `cin.ignore()`
  * Se solicita nuevamente la opción

Esto evita fallos en la ejecución del programa.

---

### Opción 1: Carga de configuraciones y pacientes

En esta opción se realiza:

1. Liberación de memoria previa si ya existen datos cargados.
2. Conteo de líneas del archivo de configuración.
3. Reserva de memoria dinámica para configuraciones.
4. Carga de configuraciones desde archivo.
5. Conteo de pacientes.
6. Reserva de memoria dinámica para pacientes.
7. Carga de pacientes desde archivo CSV.

Además, se muestran mensajes indicando la cantidad de datos cargados.

---

### Opción 2: Lectura del archivo binario

Esta opción carga toda la estructura de salas, máquinas, mediciones y lecturas.

Proceso:

1. Se valida que los pacientes estén cargados previamente.
2. Se libera memoria si ya existen datos cargados.
3. Se llama a `leer_binario`.
4. Se imprime:

   * número de salas
   * número de máquinas por sala
   * pacientes detectados

También se evita mostrar pacientes duplicados mediante un arreglo auxiliar.

---

### Opción 3: Generación de reporte de anomalías

Proceso:

1. Se valida que existan salas cargadas.
2. Se llama a `generarReporteAnomalias`.
3. Se genera un archivo de texto con todas las anomalías detectadas.

---

### Opción 4: Cálculo de estadísticas

Se presenta un submenú con dos opciones:

#### Detectar anomalías en lecturas

* Se solicita ID del paciente.
* Se recorren todas las mediciones.
* Se muestran en consola las lecturas anómalas.

#### Detectar anomalía ECG

* Se solicita ID del paciente.
* Se llama a `detectarAnomaliaECG`.
* Se muestra el resultado.

---

### Opción 5: Exportación de datos

Submenú:

#### Generar reporte de paciente

* Se solicita ID del paciente.
* Se genera un archivo con todas sus mediciones.

#### Exportar pacientes con ECG anómalo

* Se llama a `exportarPacientesECGAnomalo`.
* Se genera un archivo binario.

---

### Opción 6: Salir

Finaliza la ejecución del programa.

---

### Liberación final de memoria

Al terminar el programa se libera toda la memoria dinámica:

* Lecturas
* Mediciones
* Máquinas
* Salas
* Configuraciones
* Pacientes

Esto garantiza que no existan fugas de memoria.

---

## Flujo correcto de ejecución del sistema

Para que el programa funcione correctamente, se debe seguir el siguiente orden:

1. Cargar configuraciones y pacientes
2. Leer archivo binario
3. Ejecutar análisis (reportes o estadísticas)
4. Exportar resultados

Si se altera este orden, el sistema puede no funcionar correctamente debido a dependencias entre datos.

---

## Consideraciones técnicas importantes

### Manejo de memoria dinámica

El sistema utiliza memoria dinámica en múltiples niveles:

* Arreglos de estructuras
* Arreglos de punteros
* Redimensionamiento dinámico

Se implementan estrategias como:

* duplicación de capacidad
* liberación manual
* reasignación de memoria

---

### Uso de punteros

El uso de punteros permite:

* evitar copias innecesarias
* mejorar eficiencia
* manejar estructuras complejas

---

### Procesamiento de archivos binarios

El archivo `.bsf` es leído de forma secuencial respetando el formato de escritura.

Esto requiere:

* lectura ordenada
* conocimiento exacto de tamaños
* control de errores

---

### Control de datos duplicados

Se implementan mecanismos para:

* evitar repetir pacientes
* evitar reprocesar información

---

## Uso de Inteligencia Artificial en el desarrollo

Durante el desarrollo del proyecto se utilizó ChatGPT como herramienta de apoyo.

El uso de IA se centró en:

* Corrección de errores en el código
* Explicación de conceptos complejos
* Mejora en la estructura del programa
* Optimización de funciones
* Apoyo en la documentación del proyecto
* Validación de lógica de implementación
* Resolución de dudas sobre memoria dinámica y punteros

Es importante destacar que:

* El diseño del sistema fue realizado por los estudiantes
* La lógica principal fue desarrollada manualmente
* La IA fue utilizada como herramienta de apoyo y aprendizaje

---

## Conclusión

El sistema desarrollado cumple con los objetivos planteados, permitiendo procesar datos biomédicos, detectar anomalías y generar reportes estructurados.

Se implementaron correctamente conceptos fundamentales de programación en C++ como:

* uso de estructuras
* manejo de memoria dinámica
* lectura de archivos binarios
* procesamiento de datos

El proyecto demuestra una correcta organización modular, así como una adecuada separación de responsabilidades entre funciones y estructuras.

Además, el sistema es escalable y puede ser extendido para incluir nuevas funcionalidades o tipos de sensores en el futuro.

