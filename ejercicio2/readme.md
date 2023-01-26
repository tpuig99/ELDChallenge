# Ejercicio 2
## Consideraciones

* Se añaden ciertas validaciones con sus mensajes de error correspondiente a partir del enunciado del escenario.
* Se modifica la interfaz para hacer las conexiones con el host de manera que en vez de recibir milisegundos en la función socketRead(...) reciba segundos.
* Se incluyeron algunos archivos ejemplos en la carpeta "archivos" para la validación de las tarjetas. En caso de querer suplantarlos se deben dejar en esta carpeta. A futuro esto debería ser un parámetro modificable.
* Se generó un host para probar el envío de mensajes

## Compilación y ejecución
Para compilar el cliente se debe ejecutar:

``` 
gcc transaction_check.c card_recognizer.c card_recognizer.h socket_handler.c socket_handler.h -o main.o
```
Para ejecutar el cliente se debe correr:

``` 
./main.o
```

Para compilar el host se debe ejecutar:

``` 
gcc host.c -o host.o
```
Para ejecutar el host se debe correr:

``` 
./host.o
```