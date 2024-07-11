# Trabajo Práctico 1 - Intérprete de Código Morse

Autor: Diego Vilca Palma

Email: dlavp02@gmail.com

Este programa corresponde a la base de un sistema de apoyo al aprendizaje de código Morse. 

El sistema cuenta con las siguientes entradas y salidas:
- BUTTON1: Llave para marcado de los símbolos (*dots* y *dashes*).
- LED1: Indicador luminoso de activación de la llave.
- D2/PA_10: Pin para activación del buzzer activo.
- CONSOLE(UART): Canal de comunicación con la computadora

El programa funciona de la siguiente manera:
1. Se inicializa el puerto serial.
2. Se inicia un *super loop* (ejecución secuencial).
3. Si se detecta que se presiona la llave, se prende el LED y se activa el buzzer. Además, se inicia el conteo del tiempo.
4. Al soltarse la llave, se apaga el LED y se desactiva el buzzer. Además se termina el conteo del tiempo.
5. Si la diferencia de tiempo es menor a 240 ms, se considera que se marcó un *dot*. De no ser el caso, si la diferencia fue menor a 720 ms, se considera que se marcó un *dash*. Caso contrario no se considera nada.
6. Se imprime el caracter correspondiente al tiempo de duración del marcado en el terminal serial.
7. De no escribirse nada por 720 ms, se imprime un salto de línea en el terminal serial.