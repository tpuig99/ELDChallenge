# Ejercicio 1
Escribir un programa que solicite al usuario el ingreso de números enteros y los guarde en un archivo de acuerdo a los siguientes requerimientos:

* Se solicitará el ingreso de números hasta que se ingrese un valor igual a 0 que no debe ser guardado.
* Al finalizar el ingreso se solicitará ingresar el nombre del archivo en el que se desear guardar los números.
* El formato a utilizar en el archivo sera de cadenas de 10 caracteres. Para los números que tengan menos de 10 caracteres se rellenará con el carácter '0' hasta completar la cadena. Las cadenas deben quedar separadas en el archivo mediante un salto de línea CRLF.
* Se informará si el archivo fue guardado con éxito o si falló y luego terminará la ejecución del programa.

## Consideraciones

* Dado el tercer requerimiento se decidió no permitir al usuario ingresar números con más de 10 dígitos.
* Se incluyeron algunos archivos ejemplos en la carpeta "archivos"

## Compilación y ejecución
Para compilar el programa se debe ejecutar:

``` 
gcc number_writer.c -o main.o
```
Para ejecutar el programa se debe correr:

``` 
./main.o
```
