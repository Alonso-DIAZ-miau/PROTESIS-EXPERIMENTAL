# Motor con puente H y sensor infrarrojo (Arduino)

Mecanismo controlado con Arduino: cuando el sensor infrarrojo detecta un objeto cercano, el motor gira una cantidad fija en un sentido; cuando el objeto se aleja, gira la misma cantidad en el sentido contrario y el mecanismo vuelve a su posición inicial.

## Esquema del montaje
<img width="1501" height="787" alt="Screenshot 2026-11-11 173851" src="https://github.com/user-attachments/assets/f0cb018d-d5db-4ae2-b052-b0937384d58c" />

## Cómo funciona

1. El sensor IR vigila si hay un objeto cerca.
2. Al detectarlo, el Arduino activa el puente H **L293D** para que el motor gire en un sentido durante un tiempo fijo (`TIEMPO_MOV`).
3. Cuando el objeto se aleja, el Arduino invierte la polaridad del motor y lo hace girar el mismo tiempo en sentido contrario.
4. El mecanismo queda de nuevo en su posición inicial y espera al siguiente objeto.

El puente H es la pieza que permite invertir el giro. Con un solo transistor el motor solo podría girar en un sentido.

## Materiales

| Cantidad | Componente |
|:--:|---|
| 1 | Arduino Uno (o compatible) y cable USB |
| 1 | Circuito integrado L293D (puente H) |
| 1 | Motor DC de 5 V |
| 1 | Sensor infrarrojo de obstáculos de 3 pines (VCC, GND, OUT) |
| 1 | Protoboard |
| Varios | Cables jumper |

No hacen falta resistencias, transistores ni diodos: el L293D ya incluye lo necesario.

## Instructivo de armado


### 1. Coloca el L293D en el protoboard

Pon el chip **sobre el canal central** del protoboard, de modo que cada lado de patas quede en una mitad distinta. Ubica la **muesca** del chip como referencia para contar los pines: mirando el chip con la muesca arriba, el pin 1 está arriba a la izquierda y los pines se numeran hacia abajo por la izquierda (1 a 8) y hacia arriba por la derecha (9 a 16).

### 2. Prepara la alimentación

Con dos cables, lleva el **5V** del Arduino al riel **+** del protoboard y el **GND** del Arduino al riel **−**.

### 3. Conecta el L293D

| Pin del L293D | Nombre | Se conecta a |
|:--:|---|---|
| 1 | EN1,2 (habilitación) | Riel + (5V) |
| 2 | IN1 | Pin **D5** del Arduino |
| 3 | OUT1 | Un cable del motor |
| 4 | GND | Riel − (GND) |
| 5 | GND | Riel − (GND) |
| 6 | OUT2 | El otro cable del motor |
| 7 | IN2 | Pin **D6** del Arduino |
| 8 | VS (alimentación del motor) | Riel + (5V) |
| 12 | GND | Riel − (GND) |
| 13 | GND | Riel − (GND) |
| 16 | VCC (alimentación del chip) | Riel + (5V) |

Los pines 9, 10, 11, 14 y 15 se dejan sin conectar.

### 4. Conecta el motor

Un cable del motor va al pin **3** y el otro al pin **6** del L293D. El orden no importa por ahora: si luego gira al revés de lo que quieres, intercambia los dos cables.

### 5. Conecta el sensor IR

| Sensor | Se conecta a |
|---|---|
| VCC | Riel + (5V) |
| GND | Riel − (GND) |
| OUT | Pin **D2** del Arduino |


### 6. Resumen de pines del Arduino

| Pin del Arduino | Función |
|:--:|---|
| D2 | Señal del sensor (OUT) |
| D5 | IN1 del L293D |
| D6 | IN2 del L293D |
| 5V | Alimentación (riel +) |
| GND | Tierra (riel −) |

### 7. Revisión final antes de encender

- [ ] La muesca del L293D está en el lado correcto y el chip no está invertido.
- [ ] Los pines 1, 8 y 16 están en 5V.
- [ ] Los pines 4, 5, 12 y 13 están en GND.
- [ ] D5 llega al pin 2 y D6 al pin 7 del L293D.
- [ ] El sensor está alimentado (su LED de encendido prende al conectar el Arduino).
- [ ] No hay cables sueltos ni tocándose entre rieles.

## Cargar el código

1. Instala el [Arduino IDE](https://www.arduino.cc/en/software).
2. Abre `motor_puente_H/motor_puente_H.ino`.
3. En **Herramientas** elige tu placa (Arduino Uno) y el puerto.
4. Presiona **Subir**.

El código no usa librerías externas, no hay que instalar nada adicional.

## Explicación del código

El programa es una pequeña **máquina de estados** con cuatro estados:

| Estado | Qué está pasando | Pasa al siguiente cuando |
|---|---|---|
| `LEJOS` | No hay objeto. El motor está quieto. | El sensor detecta un objeto |
| `AVANZANDO` | El motor gira en un sentido. | Pasa el tiempo `TIEMPO_MOV` |
| `CERCA` | El objeto sigue ahí. El motor está quieto. | El objeto se aleja |
| `RETROCEDIENDO` | El motor gira en sentido contrario. | Pasa el tiempo `TIEMPO_MOV` |

Las tres partes principales:

- **`hayObjeto()`** lee el sensor y filtra el ruido. Solo acepta un cambio de lectura si se mantiene estable durante `DEBOUNCE` milisegundos, para evitar que el motor se active por lecturas falsas.
- **`avanzar()`, `retroceder()` y `detener()`** controlan el puente H con los pines D5 y D6. Si D5 está activo y D6 apagado, el motor gira en un sentido; si es al revés, gira en el otro; si ambos están apagados, se detiene. Se usa `analogWrite` para poder regular la velocidad.
- **`loop()`** revisa el estado actual y decide si debe cambiar al siguiente. No usa `delay()`, así que el sensor se sigue leyendo mientras el motor gira.

## Ajustes

Estos valores están al inicio del archivo `.ino`:

| Constante | Valor | Para qué sirve |
|---|:--:|---|
| `VELOCIDAD` | `255` | Potencia del motor, de 0 (parado) a 255 (máxima) |
| `TIEMPO_MOV` | `500` | Milisegundos que gira el motor en cada sentido. Súbelo para que recorra más |
| `DEBOUNCE` | `250` | Milisegundos que debe mantenerse una lectura para aceptarla. Súbelo si el sensor es inestable |
| `ACTIVO_BAJO` | `true` | Cámbialo a `false` si el motor se activa cuando **no** hay objeto |


---

## Mecanismo impreso en 3D

El motor mueve un **dedo mecánico** mediante un sistema de cuerdas, y toda la electrónica se guarda en contenedores montados sobre un **brazalete**. El detalle completo (piezas, ajustes de impresión, armado e ideas para mejorar el sistema de cuerdas) está en [`piezas-3d/`](piezas-3d/README.md).

<img width="1240" height="687" alt="01_vista_general" src="https://github.com/user-attachments/assets/2e57a750-15d6-4618-a9c1-d20f915b52b8" />


### Fuente y créditos

El diseño del dedo **parte de un modelo existente**, tomado de este video de YouTube:

- [Video del modelo original](https://www.youtube.com/watch?v=2EEjio4TvL8&t=4s)

Este proyecto usa ese modelo como base y le hace **cambios leves** para adaptarlo al brazalete, a los contenedores y a la electrónica de este repositorio. El mérito del diseño original es de su autor.

> Si vas a redistribuir los archivos del modelo (por ejemplo, el `.3dm` de la carpeta `piezas-3d/modelo/`), revisa en la descripción del video bajo qué licencia comparte el autor su trabajo y respétala.

### Bocetaje

Antes de modelar y construir se hicieron bocetos a mano para definir cómo iba a funcionar el conjunto.

| Idea general | Mecanismo de cuerda |
|:--:|:--:|
| <img width="300" height="300" alt="01_brazalete_y_dedo" src="https://github.com/user-attachments/assets/8063c208-72a6-4da0-bd7d-f1d0a8542cbe" /> | <img width="300" height="300" alt="02_carrete_y_cuerda" src="https://github.com/user-attachments/assets/ac465944-fccb-4d6e-9651-35e9249ba121" />|

- **Idea general (izquierda):** el brazalete va en la muñeca, con un módulo marcado en rojo sobre él, y el dedo mecánico, dividido en segmentos y marcado en morado, se dibujó sobre un dedo de la mano.
- **Mecanismo de cuerda (derecha):** en el brazalete se dibujó un carrete con flechas de giro en los dos sentidos, y una línea morada que baja por la mano hasta el dedo, que sería la cuerda. Arriba a la derecha hay un detalle del dedo con sus articulaciones y la cuerda recorriendo su costado.

### Prototipos

Se hicieron dos prototipos del dedo para probar el diseño antes de pasar a la versión final:

- **Prototipo de madera:** tallado a mano. Sirvió para probar de forma rápida y barata el tamaño, las proporciones y cómo se doblan las articulaciones.
- **Prototipo impreso en 3D (blanco):** hecho a partir del modelo de la carpeta `piezas-3d/`, con falange base, falange media y punta. Sirve para probar las bisagras reales y el paso de la cuerda.

| Los dos prototipos juntos | Comparación vista desde arriba |
|:--:|:--:|
| <img width="400" height="400" alt="01_madera_y_3d" src="https://github.com/user-attachments/assets/8429281e-cf2b-4a1a-9eb4-14828d92d2eb" /> | <img width="400" height="400" alt="02_comparacion" src="https://github.com/user-attachments/assets/ace48c45-bb25-4185-8d81-627ceb85c313" /> |


| Prototipo de madera doblado | Prototipo impreso en 3D |
|:--:|:--:|
| <img width="400" height="400" alt="03_madera_doblado" src="https://github.com/user-attachments/assets/b510440d-6e34-45f7-b735-eb72ec6f409d" /> | <img width="400" height="400" alt="04_impreso_3d" src="https://github.com/user-attachments/assets/8add3cc1-6ac3-4935-a0b4-223aef96276f" /> |


Primeras pruebas, con piezas impresas reforzadas con cartón y cinta de enmascarar:

<img width="300" height="300" alt="05_primeras_pruebas_carton_cinta" src="https://github.com/user-attachments/assets/ea1f05c3-7250-46d6-ad63-5320e889330a" />


### Piezas impresas

Algunas de las piezas ya impresas

<img width="400" height="400" alt="11_piezas_impresas" src="https://github.com/user-attachments/assets/a969e51c-2e62-4c62-966e-abd8db41710b" />

Las piezas del dedo, los contenedores, la lista de materiales, los ajustes de impresión, el armado y las ideas para el sistema de cuerdas están en [`piezas-3d/README.md`](piezas-3d/README.md).


