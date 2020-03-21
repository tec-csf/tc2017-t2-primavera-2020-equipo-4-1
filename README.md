# Tarea *2*. *Análisis de Algoritmos*

---

##### Integrantes:
1. *Francisco Acuña Franco* - *A01027294* - *CSF*
2. *Isaac Garza Strimlingas* - *A01025798* - *CSF*
3. *Sebastián Gómez Gutiérrez* - *A01374843* - *CSF*
4. *Sergio Hernández Castillo* - *A01025210* - *CSF*
5. *Rodrigo Sibaja Villarreal* - *A01023121* - *CSF*

---
## 1. Aspectos generales

Las orientaciones de la tarea se encuentran disponibles en la plataforma **Canvas**.

Este documento es una guía sobre qué información debe entregar como parte de la tarea, qué requerimientos técnicos debe cumplir y la estructura que debe seguir para organizar su entrega.


### 1.1 Requerimientos técnicos

A continuación se mencionan los requerimientos técnicos mínimos de la tarea, favor de tenerlos presente para que cumpla con todos.

* El código debe desarrollarse en C++, cumpliendo con el último estándar [C++17](https://isocpp.org/std/the-standard).
* Toda la programación debe realizarse utilizando Programación Genérica.
* Deben utilizarse las [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md).
* Todo el código debe estar correctamente documentado, siguiendo los lineamientos que aparecen en [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html).
* Todo el código de la tarea debe alojarse en este repositorio de GitHub.
* Debe configurar su repositorio para que utilice el sistema de Integración Continua [Travis CI](https://travis-ci.org/).

### 1.2 Estructura del repositorio

El proyecto debe seguir la siguiente estructura de carpetas:
```
- / 			        # Raíz del repositorio
    - README.md			# Archivo con la información general de la actividad (este archivo)
    - sources  			# Códigos fuente con la solución
    - examples			# Archivos de ejemplo que pueden utilizarse para verificar que la solución funciona.
```

## 2. Solución

*Dependiendo de qué tipo de árbol se quiera utilizar en  la carpeta sources se deberá seleccionar el archivo adecuado. En ambos casos se le solicita al usuario que introduzca que cantidad de elementos deberá contener el árbol. las opciones son 10, 100, 1000, 10000, 100000, 1000000. Se llenará el árbol con números aleatoríos según el tamaño de elementos que se haya seleccionado. Esto se hace en un arreglo llamado arr1 y se hace con la función scramble_array() que usa la función rand(). Después de que al árbol fue llenado, se imprime el tiempo de ejecución de la creación del árbol. Al terminar eso. se llena un arreglo de siempre 10 elementos sin importar la cantidad de elementos que se escoja al inicio del programa, estos también se imprimen en pantalla. Este arreglo también será llenado con números aletoríos con la función scramble_array(). Posteriormente se realizara una búsqueda de esos elementos en el arreglo existan o no, esto se hace con la función search(), para esta operación también se miden los tiempos de búsqueda. Todas las mediciones de tiempos se realizan con la función high resolution clock que permite medir en microsegundos. Al terminar con la búsqueda de los elementos en el árbol se imprime el resultado de la búsqueda y si estaban presentes o no. Una vez terminada la búsqueda realizan las mediciones de tiempo pertinentes y posteriormente la eliminación de los 10 elementos generados al azar con la función deleteNode(). Para la eliminación también se miden los tiempos de ejecución y como todos los demás también se imprimen en pantalla. Finalmente se eliminan los dos arreglos y termina el programa.*

### 2.1 Pasos a seguir para utilizar la aplicación

*1.- Abrir la terminal.*

*2.- Acceder al directorio donde vas a clonar el repositorio. Ej: cd desktop.*

*3.- Usar el comando "git clone" seguido del link del repositorio, que es  el siguiente: https://github.com/tec-csf/tc2017-t2-primavera-2020-equipo-4-1.git . Quedaria de la siguente manera: "git clone https://github.com/tec-csf/tc2017-t2-primavera-2020-equipo-4-1.git.*

*4.- Acceder al clon/carpeta del repositorio desde la terminal, el cuál se guardó donde se hizo el "git clone". Ej: "cd tc2017-t2-primavera-2020-equipo-4-1".*

*5.- Una vez que estés dentro de la carpeta del repositorio tendras que acceder a la carpeta de sources con el siguente comando: "cd sources".*

*6.- Para poder utilizar el primer programa primero deberas compilar con el siguiente comando: "g++ ArbolAVL.cpp -o ArbolAVL".*

*7.- El siguiente paso, para poder correrlo, es ingresar el siguiente comando: "./ArbolAVL. Despues se pedira que se ingrese un número para seleccionar la cantidad de elementos que se van a usar.*

*8.- 

## 3. Referencias

*[Benchoff, B. (2016, February 29). Introducing The Raspberry Pi 3. Retrieved March 19, 2020, from https://hackaday.com/2016/02/28/introducing-the-raspberry-pi-3/]*

*[GeeksforGeeks. (2017, May 29). Chrono in C . Retrieved March 19, 2020, from https://www.geeksforgeeks.org/chrono-in-c/]*
