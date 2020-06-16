# Recomendaciones LAB 06

Se sugiere fuertemente seguir el orden del Task, hará más sencillo su desarrollo.

## Task 1
### Task 1.1
+ Un ejemplo de ADC en AVR se encuentra en el código de la clase "Introducción a Microcontroladores"
+ Para las funciones de UART, recuerden que está lo desarrollado en las ayudantías de UART. Pueden utilizar esas y rellenar las librerías mostradas acá. 

+ En esta función no está implementado la función USART_transmit_string ni USART_receive_string, les agregamos una idea de estas estructuras, para que lo puedan rellenar y no perder tiempo con esto.

+ BaudRate de 57600 en AVR se cálcula de forma automática.

+ Recuerden agregar la interrupción de Rx. En Atmel Studio las interrupciones se habilitan y deshabilitan con `sei()`, `cli()` respectivamente. 

+ El vector de interrupción de Rx es ->  `ISR(USART_RX_vect)`
+ Denle un vistazo a las variables `volatile` y `static`, pueden ser útiles para controlar variables globales desde interrupciones.
### Task 1.2
+ Para el modo automático, pueden reutilizar la función del botón del LAB 05.
+ Una interrupción de Timer, que cambien variables globales que condicionan el envío, es una forma de implementar el modo automático. 
+ Para el Timer pueden usar una frecuencia que ustedes decidan. Reutilicen Ayudantía Timer o LAB 05.

## Task 2 MSP

+ Reutilicen la implementación de botones del LAB 05 
+ Para las funciones de UART, recuerden que está lo desarrollado en las ayudantías de UART. Pueden utilizar esas y rellenar las librerías mostradas acá. 
+ BaudRate 57600 **no** se calcula automáticamente. Les recomendamos usar el clock SMCLK, que se configura como `UCA1CTL1 |= UCSSEL_3;`y mirando la tabla 36-4 del User Guide MSP.
+ En esta función no está implementado la función USART_transmit_string ni USART_receive_string, les agregamos una idea de estas estructuras, para que lo puedan rellenar y no perder tiempo con esto. (**HINT: estas funciones siguen prácticamente la misma estructura que AVR, solo con registros distintos** )
+ Librerías del LCD hay muchas disponibles. Les recomendamos usar alguna que utilice el modo de 4 bits, así ahorrarán pines para la comunicación. (Pueden compartir esta información en las Issues sin problemas)
+ El mensaje a recibir tiene un largo fijo, por lo que un buffer lineal puede ser la mejor opción en este caso.

## Task 3 AVR - MSP
+ Para ahora poder enviar le valor de 10  bit de ADC, es necesario separarlo en dos paquetes y luego unirlo en MSP. Pueden revisar las lineas `49` a `70` del `main.c` de archivo de I2C subido en esa ayudantía.
+ Reutilicen lo hecho en el Task 1 y Task 2, las estructuras para mandar mensajes deberían estar implementadas y habría que cambiar lo que se identifica.
+ De ser útiles, las funciones `itoa(...)` y `atoi(...)` sirven para convertir de int a string y viceversa.