## Compilación:
Para compilar el tp, estando parado en este mismo directorio, correr make en una terminal.
Esto va a crear un binario llamado tp1.

## Ejecución:
El binario espera (devuelve) un input (output) tal y como está especificado en el enunciado
del Trabajo Práctico. 
### Ejemplo:

```shell
# Correr TP con cierto input
$ ./tp1 $HOME/TP1/tests/test_15_segundos.txt 0.76

# Verificar que se haya escrito
$ cat $HOME/TP1/tests/test_15_segundos.txt | head
0.76
0.000385628
0.000630973
0.000365617
0.000706523
0.000314517
0.00038582
0.000286803
0.000340517
0.000678639
```


## Tests:
Los tests provistos originalmente, con sus respectivos .out,
se encuentra en ./tests_catedra_original.

La carpeta ./tests contiene los tests de la cátedra, pero
con los .out de nuestro programa.

Para correr los tests, se provee un archivo de Jupyter notebook
con las funciones que usamos para create tests, correr los tests
provistos y graficar resultados.

Los tests en sí consisten de 2 archivos:
- helper.py, encargado de generar tests y correr los de la cátedra.
- tester.py, encargado de correr los tests que generamos.

El código que proveen es usado directa e indirectamente en
la notebook.
