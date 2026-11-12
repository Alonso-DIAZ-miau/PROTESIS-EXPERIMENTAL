# Motor con puente H y sensor infrarrojo (Arduino)

Mecanismo controlado con Arduino: cuando el sensor infrarrojo detecta un objeto cercano, el motor gira una cantidad fija en un sentido; cuando el objeto se aleja, gira la misma cantidad en el sentido contrario y el mecanismo vuelve a su posición inicial.

![Esquema del montaje](img/circuito.png)

## Contenido del repositorio

```
.
├── README.md
├── img/
│   └── circuito.png              # Esquema del montaje
└── motor_puente_H/
    └── motor_puente_H.ino        # Código para el Arduino
```

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

---

## Mecanismo impreso en 3D

El motor mueve un **dedo mecánico** mediante un sistema de cuerdas, y toda la electrónica se guarda en contenedores montados sobre un **brazalete**. El detalle completo (piezas, ajustes de impresión, armado e ideas para mejorar el sistema de cuerdas) está en [`piezas-3d/`](piezas-3d/README.md).

[![Vista general de las piezas](piezas-3d/img/01_vista_general.png)](piezas-3d/README.md)

### Fuente y créditos

El diseño del dedo **parte de un modelo existente**, tomado de este video de YouTube:

- [Video del modelo original](https://www.youtube.com/watch?v=2EEjio4TvL8&t=4s)

Este proyecto usa ese modelo como base y le hace **cambios leves** para adaptarlo al brazalete, a los contenedores y a la electrónica de este repositorio. El mérito del diseño original es de su autor.

> Si vas a redistribuir los archivos del modelo (por ejemplo, el `.3dm` de la carpeta `piezas-3d/modelo/`), revisa en la descripción del video bajo qué licencia comparte el autor su trabajo y respétala.

### Bocetaje

Antes de modelar y construir se hicieron bocetos a mano para definir cómo iba a funcionar el conjunto.

| Idea general | Mecanismo de cuerda |
|:--:|:--:|
| <img src="piezas-3d/img/bocetos/01_brazalete_y_dedo.jpg" width="300" alt="Boceto de la mano con el brazalete en la muñeca y el dedo mecánico"> | <img src="piezas-3d/img/bocetos/02_carrete_y_cuerda.jpg" width="300" alt="Boceto del carrete en el brazalete y la cuerda hacia el dedo"> |

- **Idea general (izquierda):** el brazalete va en la muñeca, con un módulo marcado en rojo sobre él, y el dedo mecánico, dividido en segmentos y marcado en morado, se dibujó sobre un dedo de la mano.
- **Mecanismo de cuerda (derecha):** en el brazalete se dibujó un carrete con flechas de giro en los dos sentidos, y una línea morada que baja por la mano hasta el dedo, que sería la cuerda. Arriba a la derecha hay un detalle del dedo con sus articulaciones y la cuerda recorriendo su costado.

### Prototipos

Se hicieron dos prototipos del dedo para probar el diseño antes de pasar a la versión final:

- **Prototipo de madera:** tallado a mano. Sirvió para probar de forma rápida y barata el tamaño, las proporciones y cómo se doblan las articulaciones.
- **Prototipo impreso en 3D (blanco):** hecho a partir del modelo de la carpeta `piezas-3d/`, con falange base, falange media y punta. Sirve para probar las bisagras reales y el paso de la cuerda.

| Los dos prototipos juntos | Comparación vista desde arriba |
|:--:|:--:|
| <img src="piezas-3d/img/prototipos/01_madera_y_3d.jpg" width="400" alt="Prototipo de madera y prototipo impreso en 3D"> | <img src="piezas-3d/img/prototipos/02_comparacion.jpg" width="400" alt="Comparación de los dos prototipos"> |

| Prototipo de madera doblado | Prototipo impreso en 3D |
|:--:|:--:|
| <img src="piezas-3d/img/prototipos/03_madera_doblado.jpg" width="400" alt="Prototipo de madera con las articulaciones dobladas"> | <img src="piezas-3d/img/prototipos/04_impreso_3d.jpg" width="400" alt="Prototipo impreso en 3D con la cuerda"> |

Primeras pruebas, con piezas impresas reforzadas con cartón y cinta de enmascarar:

<img src="piezas-3d/img/prototipos/05_primeras_pruebas_carton_cinta.jpg" width="300" alt="Primeras pruebas del dedo con piezas impresas, cartón y cinta">

### Piezas impresas

Algunas de las piezas ya impresas: el semicilindro del brazalete, piezas de las articulaciones y otras piezas pequeñas.

<img src="piezas-3d/img/11_piezas_impresas.jpg" width="400" alt="Piezas impresas en 3D: brazalete, articulaciones y otras piezas">

Las piezas del dedo, los contenedores, la lista de materiales, los ajustes de impresión, el armado y las ideas para el sistema de cuerdas están en [`piezas-3d/README.md`](piezas-3d/README.md).

### Contenido de la carpeta `piezas-3d/`

```
piezas-3d/
├── README.md
├── img/
│   ├── bocetos/                 # Bocetos a mano de la idea
│   ├── prototipos/              # Fotos de los prototipos físicos
│   └── ...                      # Capturas del modelo y fotos de las piezas impresas
└── modelo/
    └── modelo_etapa_2.3dm       # Modelo 3D (Rhinoceros 7)
```
