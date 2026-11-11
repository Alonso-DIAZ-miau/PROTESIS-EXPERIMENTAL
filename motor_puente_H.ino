// Motor con puente H (L293D) y sensor IR
// Sensor cerca  -> el motor avanza TIEMPO_MOV ms
// Sensor lejos  -> el motor retrocede TIEMPO_MOV ms (vuelve a la posicion inicial)

const int SENSOR = 2;   // OUT del sensor IR
const int IN1 = 5;      // L293D pin 2
const int IN2 = 6;      // L293D pin 7
const int VELOCIDAD = 255;   // de 0 (parado) a 255 (máxima potencia)

const bool ACTIVO_BAJO = true;          // false si el sensor funciona al reves
const unsigned long TIEMPO_MOV = 500;  // ms de giro en cada sentido
const unsigned long DEBOUNCE = 250;      // ms para filtrar ruido del sensor

enum Estado { LEJOS, AVANZANDO, CERCA, RETROCEDIENDO };
Estado estado = LEJOS;
unsigned long tInicio = 0;

bool hayObjeto() {
  static bool estable = false;
  static bool ultima = false;
  static unsigned long tCambio = 0;

  bool lectura = digitalRead(SENSOR);
  if (ACTIVO_BAJO) lectura = !lectura;

  if (lectura != ultima) {
    ultima = lectura;
    tCambio = millis();
  }
  if (millis() - tCambio > DEBOUNCE) estable = ultima;
  return estable;
}

void detener()    { analogWrite(IN1, 0);         analogWrite(IN2, 0); }
void avanzar()    { analogWrite(IN1, VELOCIDAD); analogWrite(IN2, 0); }
void retroceder() { analogWrite(IN1, 0);         analogWrite(IN2, VELOCIDAD); }

void setup() {
  pinMode(SENSOR, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  detener();
}

void loop() {
  bool objeto = hayObjeto();

  switch (estado) {
    case LEJOS:
      if (objeto) {
        avanzar();
        tInicio = millis();
        estado = AVANZANDO;
      }
      break;

    case AVANZANDO:
      if (millis() - tInicio >= TIEMPO_MOV) {
        detener();
        estado = CERCA;
      }
      break;

    case CERCA:
      if (!objeto) {
        retroceder();
        tInicio = millis();
        estado = RETROCEDIENDO;
      }
      break;

    case RETROCEDIENDO:
      if (millis() - tInicio >= TIEMPO_MOV) {
        detener();
        estado = LEJOS;
      }
      break;
  }
}
