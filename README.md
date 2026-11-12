# Piezas impresas en 3D: dedo mecánico y brazalete

Esta carpeta contiene el diseño mecánico del proyecto: un **dedo articulado** movido por cuerdas y un **brazalete** con contenedores para la electrónica (Arduino, protoboard, sensor IR y motor). La parte electrónica y el código están en el [README principal](../README.md).

![Vista general de las piezas](img/01_vista_general.png)

> **Estado del diseño:** etapa 2. Las piezas del dedo y los contenedores están modeladas. El **sistema de cuerdas todavía no está bien resuelto**; por eso este documento incluye una sección con [ideas para hacerlo funcionar](#ideas-para-el-sistema-de-cuerdas).

## Contenido de la carpeta

```
piezas-3d/
├── README.md
├── img/
│   ├── bocetos/                 # Bocetos a mano de la idea
│   ├── prototipos/              # Fotos de los prototipos físicos
│   └── ...                      # Capturas del modelo y fotos de las piezas impresas
└── modelo/
    └── modelo_etapa_2.3dm       # Modelo original (Rhinoceros 7)
```

## Fuente y créditos

El diseño del dedo **parte de un modelo existente**, tomado de este video de YouTube:

- [Video del modelo original](https://www.youtube.com/watch?v=2EEjio4TvL8&t=4s)

Este proyecto usa ese modelo como base y le hace **cambios leves** para adaptarlo al brazalete, a los contenedores y a la electrónica propuesta en este repositorio. El mérito del diseño original es de su autor.

> Si vas a redistribuir los archivos del modelo (por ejemplo, el `.3dm` de la carpeta `modelo/`), revisa en la descripción del video bajo qué licencia comparte el autor su trabajo y respétala.

## Bocetaje

Antes de modelar y construir se hicieron bocetos a mano para definir cómo iba a funcionar el conjunto.

| Idea general | Mecanismo de cuerda |
|:--:|:--:|
| <img src="img/bocetos/01_brazalete_y_dedo.jpg" width="300" alt="Boceto de la mano con el brazalete en la muñeca y el dedo mecánico"> | <img src="img/bocetos/02_carrete_y_cuerda.jpg" width="300" alt="Boceto del carrete en el brazalete y la cuerda hacia el dedo"> |

- **Idea general (izquierda):** el brazalete va en la muñeca, con un módulo marcado en rojo sobre él, y el dedo mecánico, dividido en segmentos y marcado en morado, se dibujó sobre un dedo de la mano.
- **Mecanismo de cuerda (derecha):** en el brazalete se dibujó un carrete con flechas de giro en los dos sentidos, y una línea morada que baja por la mano hasta el dedo, que sería la cuerda. Arriba a la derecha hay un detalle del dedo con sus articulaciones y la cuerda recorriendo su costado.

Estos bocetos encajan con lo descrito en las [ideas para el sistema de cuerdas](#ideas-para-el-sistema-de-cuerdas): un motor que gira en ambos sentidos (opciones A y B) y un recorrido largo de cuerda desde la muñeca hasta el dedo, donde ayuda una funda tipo Bowden (opción D).

## Prototipos

Se hicieron dos prototipos del dedo para probar el diseño antes de pasar a la versión final:

- **Prototipo de madera:** tallado a mano. Sirvió para probar de forma rápida y barata el tamaño, las proporciones y cómo se doblan las articulaciones.
- **Prototipo impreso en 3D (blanco):** hecho a partir del modelo de esta carpeta, con falange base, falange media y punta. Sirve para probar las bisagras reales y el paso de la cuerda.

| Los dos prototipos juntos | Comparación vista desde arriba |
|:--:|:--:|
| <img src="img/prototipos/01_madera_y_3d.jpg" width="400" alt="Prototipo de madera y prototipo impreso en 3D"> | <img src="img/prototipos/02_comparacion.jpg" width="400" alt="Comparación de los dos prototipos"> |

| Prototipo de madera doblado | Prototipo impreso en 3D |
|:--:|:--:|
| <img src="img/prototipos/03_madera_doblado.jpg" width="400" alt="Prototipo de madera con las articulaciones dobladas"> | <img src="img/prototipos/04_impreso_3d.jpg" width="400" alt="Prototipo impreso en 3D con la cuerda"> |

Primeras pruebas, con piezas impresas reforzadas con cartón y cinta de enmascarar:

<img src="img/prototipos/05_primeras_pruebas_carton_cinta.jpg" width="300" alt="Primeras pruebas del dedo con piezas impresas, cartón y cinta">

En las fotos se ve también una cuerda junto a los prototipos, que es el sistema que aún falta resolver (ver [ideas para el sistema de cuerdas](#ideas-para-el-sistema-de-cuerdas)).

## Cómo se ve el conjunto

```
            BRAZALETE (sobre el antebrazo)
   +-----------------------------------------+
   |  [Sensor IR]   [Arduino] [Protoboard]   |
   |  [Motor + carrete]                      |
   +----------------------|------------------+
                          | cuerdas
                          v
                    DEDO MECÁNICO
         (base) --o-- (media) --o-- (punta)
```

Puedes ver cómo se imaginó el conjunto en los [bocetos](#bocetaje).

El sensor detecta el objeto, el Arduino activa el motor, el motor enrolla o suelta la cuerda en un carrete, y la cuerda dobla o estira el dedo.

## Piezas del dedo

El dedo tiene tres piezas y dos articulaciones tipo bisagra.

| Pieza | Imagen | Qué se ve en el modelo |
|---|:--:|---|
| **Falange base** | ![Base](img/10_dedo_falange_base.png) | Cuerpo cilíndrico con una horquilla de dos discos con orificio central (la bisagra) y un orificio pequeño en la cara plana. |
| **Falange media** | ![Media](img/09_dedo_falange_media.png) | Dos extremos cilíndricos con disco y orificio central, unidos por un bloque. Tiene una ranura lateral y un orificio pequeño en uno de los cilindros. |
| **Punta** | ![Punta](img/08_dedo_punta.png) | Cuerpo cilíndrico de extremo redondeado con horquilla de dos discos y un orificio diminuto en la punta. |

Los orificios pequeños y la ranura de la falange media ya sirven como **puntos de paso y anclaje de la cuerda**: entrada en la base, guía en la falange media y anclaje (nudo) en la punta.

## Brazalete y contenedores

| Pieza | Imagen | Qué se ve en el modelo | Función probable |
|---|:--:|---|---|
| **Brazalete** | ![Vista general](img/01_vista_general.png) | Media caña abierta, que se abraza al antebrazo. | Soporte de todo el conjunto |
| **Caja con orificio circular** | ![Caja](img/02_caja_orificio_vista1.png) ![Caja 2](img/03_caja_orificio_vista2.png) | Caja cúbica con un orificio redondo en una cara. | Sensor IR (el orificio es la ventana del sensor) |
| **Caja con orificio lateral** | ![Caja lateral](img/05_caja_orificio_lateral.png) | Caja alta y delgada con un orificio en un costado. | Contenedor con salida de cable o eje |
| **Bloque con dos orificios** | ![Bloque](img/04_bloque_dos_orificios.png) | Bloque pequeño con dos orificios grandes en un extremo. | Salida de las dos cuerdas hacia el dedo |
| **Placas con dos orificios (2)** | ![Placas frente](img/06_placas_frente.png) ![Placas lateral](img/07_placas_lateral.png) | Dos placas altas y delgadas, cada una con un orificio pequeño y uno grande con muesca. | Arduino y protoboard (planos, con salida de cables en la parte baja) |

Así se ven algunas de estas piezas ya impresas: el semicilindro del brazalete, piezas de las articulaciones y otras piezas pequeñas.

<img src="img/11_piezas_impresas.jpg" width="400" alt="Piezas impresas en 3D: brazalete, articulaciones y otras piezas">

> **Nota:** la columna "Función probable" se dedujo de la forma de cada pieza. Si en tu diseño una caja guarda otra cosa, corrígela aquí.

## Lista de materiales (parte mecánica)

| Material | Para qué |
|---|---|
| Filamento PLA o PETG | Piezas del dedo y cajas. PETG resiste mejor el desgaste. |
| Filamento TPU (opcional) | Almohadilla entre el brazalete y la piel, o brazalete flexible. |
| Cuerda trenzada delgada (hilo de pesca trenzado de 0,2 a 0,5 mm) | Tendones. Debe estirarse lo mínimo posible. |
| Cordón elástico fino o banda elástica | Retorno del dedo (opciones A y B). |
| 2 ejes pequeños: varilla, tornillo con tuerca o trozo de filamento | Bisagras del dedo. Usa el diámetro del orificio central de los discos. |
| Tubo de PTFE de 2 a 4 mm (opcional) | Funda para guiar la cuerda (opción D). |
| Banda de velcro o elástico ancho | Sujetar el brazalete al antebrazo. |
| Tornillos de 3 mm con tuerca, cinta de doble cara o pegamento | Fijar las cajas al brazalete. |

## Impresión

### Ajustes recomendados

| Parámetro | Valor sugerido |
|---|---|
| Altura de capa | 0,2 mm |
| Perímetros (paredes) | 3 o 4 en el dedo, 2 o 3 en las cajas |
| Relleno | 30 a 40 % en el dedo, 15 a 20 % en cajas y brazalete |
| Soportes | Sí en las horquillas y en los orificios horizontales. Quítalos con cuidado de los orificios de la cuerda. |
| Tolerancia de orificios | Agrega unos 0,2 a 0,3 mm de holgura a los ejes de las bisagras si giran duras |

### Orientación

- Imprime las **horquillas con los discos apoyados en la cama**, para que las capas no queden paralelas al eje de la bisagra y no se partan.
- Imprime las cajas con la cara de la tapa o del fondo contra la cama.
- Después de imprimir, pasa una broca del diámetro nominal por los orificios de ejes y cuerdas para quitar rebabas.

### Antes de exportar el modelo

Abre `modelo/modelo_etapa_2.3dm` en Rhinoceros 7 o superior y revisa:

1. **Unidades en milímetros.**
2. **Sólidos cerrados.** Cada pieza debe ser un polisuperficie cerrado. Usa el comando `Check` en cada pieza y `SelOpenPolysrf` para ubicar las abiertas.
3. **El brazalete.** En la captura de Rhino parece una superficie, pero el brazalete impreso de las fotos sí tiene espesor. Confirma que el archivo `.3dm` actual ya lo tenga; si no, dale grosor antes de exportar (por ejemplo, `OffsetSrf` con la opción *Sólido* activada).
4. **Exporta cada pieza por separado:** selecciónala y usa *Archivo > Exportar seleccionados* con formato **STL**. Así puedes orientar e imprimir cada una por su cuenta.

## Armado

1. **Imprime y limpia** todas las piezas. Verifica que los ejes pasen por los orificios de las horquillas sin forzar.
2. **Arma el dedo.** Une base y falange media con un eje, y falange media y punta con otro. Cada articulación debe girar libre y sin juego excesivo.
3. **Pasa la cuerda** por los orificios del dedo según la opción que elijas en la sección siguiente. Anuda la cuerda en el orificio de la punta.
4. **Prueba el dedo a mano.** Tira de la cuerda: el dedo debe doblarse de forma pareja y volver al soltarla. No sigas hasta que esto funcione sin motor.
5. **Monta el motor y el carrete** en su caja y fíjalos al brazalete.
6. **Coloca las cajas** del sensor, Arduino y protoboard en el brazalete. El sensor debe quedar con su ventana apuntando hacia afuera.
7. **Conecta la electrónica** siguiendo el [README principal](../README.md).
8. **Calibra** el movimiento ajustando `TIEMPO_MOV` en el código (ver [sección de calibración](#calibración-con-el-código)).

## Ideas para el sistema de cuerdas

La cuerda convierte el giro del motor en el doblez del dedo (ver el [boceto del mecanismo](#bocetaje)). Como el motor puede girar en los dos sentidos (puente H), hay varias formas de aprovecharlo.

### Cómo funciona un dedo de tendones

```
  Base           Media          Punta
 +------+o     o+------+o     o+-----+
 |      |  eje 1 |      | eje 2 |     \
 +------+       +------+       +------(.)  <- anclaje de la cuerda (nudo)
  ===== cuerda de flexión (lado de la palma) ======> al carrete
  ~~~~~ elástico o 2.ª cuerda (lado del dorso) ~~~~~
```

- La cuerda pasa por el **lado de la palma**, a cierta distancia de los ejes. Al tirar de ella, el dedo se dobla.
- Para estirar el dedo hace falta una **fuerza de retorno**: un elástico o una segunda cuerda en el lado del dorso.

### Las cuatro opciones

| Opción | Cómo funciona | Ventajas | Desventajas |
|---|---|---|---|
| **A. Una cuerda y retorno elástico** | El motor enrolla la cuerda para doblar. Al girar al revés la suelta y un elástico del lado del dorso estira el dedo. | La más simple de imprimir y probar. | El elástico resta fuerza a la flexión. |
| **B. Dos cuerdas antagónicas en un carrete** | Una cuerda va al lado de la palma y otra al del dorso, enrolladas en sentidos opuestos en el mismo carrete. Al girar, una se enrolla y la otra se suelta. | Flexión y extensión activas, sin elástico. Aprovecha el giro en ambos sentidos. | Las dos cuerdas deben tener el mismo recorrido, o una queda floja. |
| **C. Bucle cerrado** | Una sola cuerda continua pasa por el carrete y por una polea en la punta del dedo, y forma un lazo. | Tensión siempre pareja. | Necesita una polea extra en el dedo. |
| **D. Funda tipo Bowden** | La cuerda viaja dentro de un tubo de PTFE entre el motor y el dedo. | Permite poner el motor lejos del dedo y mover el brazo sin que cambie el recorrido. | Agrega fricción. |

**Recomendación:** empieza con **A + D** para tener un primer prototipo que funcione, y pasa a **B** cuando quieras fuerza en las dos direcciones. El bloque con dos orificios del brazalete encaja bien con la opción B, porque da una salida para cada cuerda.

### Cómo dimensionar el carrete

Cuánta cuerda hay que mover depende de la distancia entre el eje de cada articulación y el camino de la cuerda (el brazo de palanca, `r`) y del ángulo que quieres doblar (`θ`, en radianes):

```
Recorrido de cuerda  ≈  r × θ  (sumado para cada articulación)
Vueltas del carrete  =  recorrido ÷ (π × diámetro del carrete)
```

**Ejemplo** (valores ilustrativos, mide los tuyos en el modelo): con `r` = 5 mm y 90° (1,57 rad) en cada una de las dos articulaciones:

- Recorrido: 5 × 1,57 × 2 ≈ 15,7 mm
- Carrete de 10 mm de diámetro: 15,7 ÷ (π × 10) ≈ 0,5 vueltas

Un carrete más grueso enrolla más cuerda por vuelta, pero hace menos fuerza. Uno más delgado hace más fuerza, pero necesita más vueltas.

### Diseño del carrete

- Una **ranura** para la cuerda y **bridas** a los lados para que no se salga.
- Un **orificio** para amarrar la cuerda al carrete.
- Un cubo que encaje en el eje del motor, con un **tornillo prisionero** o un ajuste con eje en forma de D.
- Para la opción B, dos ranuras separadas, enrolladas en sentidos opuestos.

### Fuerza del motor

Un motor DC pequeño gira rápido pero con poca fuerza. Para mover un dedo con cuerdas conviene un **motorreductor** (por ejemplo, tipo N20 de 50 a 100 rpm de salida). Si no tienes uno, un carrete delgado compensa en parte la falta de fuerza. Recuerda que el L293D alimentado desde el Arduino entrega unos 3,5 V al motor; consulta en el README principal cómo darle más potencia con una fuente externa.

### Problemas típicos y cómo evitarlos

| Problema | Causa probable | Solución |
|---|---|---|
| El dedo se atasca o se dobla a tirones | Fricción en los orificios | Redondea los bordes, usa tubo de PTFE y evita ángulos bruscos en el camino de la cuerda |
| El dedo no vuelve del todo | Retorno débil o cuerda floja | Aumenta la tensión del elástico o usa la opción B |
| Cuerda floja tras varios ciclos | La cuerda se estira o el nudo se corre | Usa cuerda trenzada que no se estire y asegura el nudo con una gota de pegamento |
| El carrete suelta más cuerda de la que enrolla | Desfase entre ida y vuelta | Calibra `TIEMPO_MOV` y usa un tope mecánico o un final de carrera |
| Las bisagras giran duras | Falta de holgura al imprimir | Pasa una broca por los orificios o amplía 0,2 a 0,3 mm su diámetro en el modelo |
| La cuerda cambia de tensión al mover el brazo | Camino libre de la cuerda | Usa la funda del Bowden (opción D) |

### Tensor ajustable

Prever en el modelo una forma de **regular la tensión** facilita mucho el ajuste: por ejemplo, un tornillo con tuerca por donde pasa la cuerda, o una ranura en la caja del motor donde pueda deslizarse el carrete.

### Calibración con el código

El código del proyecto mueve el motor un tiempo fijo en cada sentido (`TIEMPO_MOV`). Con un carrete, ese tiempo debe corresponder a las vueltas necesarias:

```
TIEMPO_MOV (ms)  =  vueltas necesarias ÷ rpm del carrete × 60 000
```

Por ejemplo, 0,5 vueltas con un carrete a 60 rpm: 0,5 ÷ 60 × 60 000 = **500 ms**. Las rpm reales cambian con la carga y el voltaje, así que ajusta el valor probando hasta que el dedo se doble y estire por completo.

### Posición de reposo con final de carrera (opcional)

Como un motor DC no sabe en qué posición está, con el tiempo el dedo puede desfasarse. Una solución simple es agregar un **microinterruptor** que se presiona cuando el dedo está en reposo y llevar el dedo hasta él al encender. Conecta un lado del microinterruptor al pin D3 y el otro a GND, y añade esto al final de `setup()`:

```cpp
const int FINAL_CARRERA = 3;   // microinterruptor entre D3 y GND

// Dentro de setup(), después de detener();
pinMode(FINAL_CARRERA, INPUT_PULLUP);
retroceder();                                   // dirección que suelta la cuerda
unsigned long t0 = millis();
while (digitalRead(FINAL_CARRERA) == HIGH && millis() - t0 < 3000) { }
detener();
```

El límite de 3000 ms evita que el motor quede girando si el interruptor falla. Si el motor gira hacia el lado contrario, intercambia sus dos cables.

### Alternativas si las cuerdas no dan resultado

- **Servomotor:** da un ángulo preciso sin calibrar tiempos y se controla con una librería estándar de Arduino.
- **Motor paso a paso:** permite contar pasos y repetir el recorrido con exactitud.

## Seguridad al usarlo en el brazo

- Redondea los bordes del brazalete y coloca una almohadilla (TPU o espuma) entre la pieza y la piel.
- Evita puntos de pellizco en las bisagras del dedo y entre las cajas y el brazalete.
- El L293D puede calentarse con cargas altas: deja ventilación en su caja y revisa que no queme al tacto.
- Prueba todo primero sobre la mesa antes de ponerlo en el antebrazo.

## Próximos pasos

- [ ] Verificar que todas las piezas del modelo sean sólidos cerrados, incluido el espesor del brazalete.
- [ ] Imprimir el dedo y probar las bisagras a mano.
- [ ] Probar la opción A con cuerda y elástico.
- [ ] Diseñar el carrete e imprimirlo.
- [ ] Definir el método de tensado de la cuerda.
- [ ] Agregar el final de carrera y calibrar `TIEMPO_MOV`.
- [ ] Montar todo en el brazalete y probar con el sensor.
