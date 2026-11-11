
# Motor con puente H y sensor infrarrojo (Arduino)

Mecanismo controlado con Arduino: cuando el sensor infrarrojo detecta un objeto cercano, el motor gira una cantidad fija en un sentido; cuando el objeto se aleja, gira la misma cantidad en el sentido contrario y el mecanismo vuelve a su posición inicial.

## Esquema del montaje
<img width="1501" height="787" alt="Screenshot 2026-11-11 173851" src="https://github.com/user-attachments/assets/8efbe7cc-14f6-41e9-adec-f14e84599bd2" />



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

> **Importante:** arma todo con el Arduino **desconectado** del USB y conéctalo solo al final.

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

Revisa las letras impresas en tu módulo: algunos traen el orden `OUT, GND, VCC` y otros `VCC, GND, OUT`.

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

## Solución de problemas

<details>
<summary><b>El motor gira solo en un sentido</b></summary>

Revisa que D5 llegue al pin 2 del L293D y D6 al pin 7. Si uno de los dos cables no hace contacto, el motor solo gira en una dirección. Si no gira en ningún sentido, revisa los pines 1, 8 y 16 (5V) y los de GND.
</details>

<details>
<summary><b>El motor se activa cuando no hay nada cerca, o al revés</b></summary>

Cambia `ACTIVO_BAJO` a `false` en el código. Si el sensor mantiene siempre la misma lectura, comprueba su alimentación y ajusta el potenciómetro del módulo, si lo tiene.
</details>

<details>
<summary><b>El LED del sensor no enciende</b></summary>

Revisa el orden de sus pines (VCC y GND), que el riel del protoboard esté alimentado y que los rieles no estén cortados a la mitad, algo común en protoboards grandes.
</details>

<details>
<summary><b>El motor gira débil o el Arduino se reinicia</b></summary>

Por el USB solo hay unos 500 mA, y el L293D pierde cerca de 1,4 V, por lo que el motor recibe aproximadamente 3,5 V. Para darle más fuerza, alimenta el **pin 8** del L293D con una fuente externa adecuada para tu motor y une su GND con el GND del Arduino. Mantén los pines 1 y 16 en 5V.
</details>

<details>
<summary><b>El motor avanza apenas enciendo el Arduino</b></summary>

Si hay un objeto frente al sensor al encender, el programa lo detecta y avanza de inmediato. Es el comportamiento esperado: retira el objeto y reinicia el Arduino.
</details>

## Ideas para mejorar

- Usar un driver más potente (L298N o TB6612FNG) para motores más grandes.
- Reemplazar el motor por un motor paso a paso o un servo si se necesita un recorrido preciso, ya que con un motor DC la distancia depende solo del tiempo.
- Agregar finales de carrera para detener el motor en posiciones exactas.
