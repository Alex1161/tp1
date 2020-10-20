# **TP1**
**Nombre** : Arbieto Benites Gabriel Alexander \
**Padron** : 102219\
**Link** : https://github.com/Alex1161/tp1

## **Introducción**
En este tp se pidió desarrollar dos programas:
1. Un emisor (cliente).
2. Un receptor (servidor).

Implementados a través de sockets bloqueantes. Ambos con tres métodos de cifrado posible:

1. Cesar (Extendido para un desplazamiento K).
2. Vigenere.
3. ARC4.

El flujo del programa fue a través de entrada estándar para el cliente y salida estándar para el servidor.

## **Resolución del trabajo**

Para este trabajo práctico se optó por una solución lo mas orientada a objetos posible. Dividiendo el problema en entidades encargadas de resolver una parte aislada del problema. En el siguiente diagrama de clases se puede observar la estructura general del tp:

![DC general](Diagramas/Png/DC.png?raw=true "Diagrama de clases")

Ahora se explicará la responsabilidad de cada entidad.

![DC main](Diagramas/Png/processor_superior.png?raw=true "Diagrama de clases main")

### **Client_main y Server_main**
Ambas son responsables de parsear sus entradas de comando e inicializar correctamente la entidad **Procesor** con alguno de los algoritmos de encriptado, también son los encargados de pasarle lo que necesita para establecer la conexión (IP y Port si es client o solo Port si es server).

### **Processor**
Esta entidad tiene un comportamiento distinto dependiendo de quien la use.
1. Para client: Es el encargado de cargar todo el mensaje que recive por entrada estandar a traves de la entidad **File_processor**, codificarlo a través de alguno de los algoritmos de cifrado mediante la entidad **Encryptor** y delegar su envío a la entidad **Socket** .
2. Para server: Es el encargado de dar la orden a la entidad **Socket** de recibir todo el mensaje, decodificarlo a través de la entidad **Encryptor** y mostrarlo por salida estándar a través de la entidad **File_processor**.

![DC Procesor](Diagramas/Png/Processor_inferior.png?raw=true "Diagrama de clases Processor")

### **Socket**
Esta entidad es la encargada de resolver los nombres de las direcciones IP y puertos disponibles, establecer las conexiones, bien del cliente o del servidor y recibir o enviar mensajes mediante el protocolo TCP usando IPV4.

### **File_processor**
Es el responsable de las operaciones con archivos; leer o escribir (para este tp en stdin y stdout respectivamente).

### **Encryptor**
Es el responsable de a través del nombre recibido por el **Processor**, resolver que método de encriptado usar y decodificar o codificar un mensaje.

![DC Encrypro](Diagramas/Png/Encryptor.png?raw=true "Diagrama de clases Encrypro")

### **Cesar**
Es el responsable de codificar o decodificar un mensaje a través del algoritmo de **Cesar** generalizado para "k" desplazamientos.

### **Vigenere**
Es el responsable de codificar o decodificar un mensaje a través del algoritmo de **Vigenere**, el cual consta de transformar la clave en una serie de bytes del tamaño del mensaje, sumarlos o restarlos (encode o decode), y pasarlos a caracteres de vuelta.

### **ARC4**
Es el responsable de codificar o decodificar un mensaje a través del algoritmo **RC4**, el cual consta de a través de dos algoritmos (KSA y PRGA) y la clave formar un un Stream pseudo aleatorio con el cual se obtiene un key_stream del mismo tamañano que el mensaje y por ultimo operarlos con XOR byte a byte, dado que para este método se genera el mismo key_stream si se usa la misma clave y la operacion XOR es una función involutiva (f(f(x)) = x) para la decodificación se codifica de vuelta el valor codificado.

Estas dos últimas entidades usaban muchas operaciones entre arreglos las cuales fueron encapsuladas en la biblioteca Op_vec.

![DC Op_vec](Diagramas/Png/Op_vec.png?raw=true "Diagrama de clases Op_vec")

### **Op_vec**
Es la responsable de todas las operaciones entre vectores que se necesitaron en este tp.

## **Ejecución de pruebas**
Para este tp también se implemento un pequeño test unit para poder probar el correcto funcionamiento de los encryptors. Para eso se le agrego dos funciones mas a la biblioteca Op_vec para poder probar las codificaciones.

~~~
// Transforma un valor entero en un string con su representacion en la base
// especificada.
char* itoa(int value, char* result, int base);

// Transforma de unsigned char a un string de su valor numerico en hexadecimal
size_t un_char_to_hexa(unsigned char *element, char *hexa, size_t size_element);
~~~

Para correr las pruebas seguir los siguientes pasos:
1. Moverte a la carpeta tests en la terminal.
2. Ejecutar el comando:

~~~
    make test
~~~

