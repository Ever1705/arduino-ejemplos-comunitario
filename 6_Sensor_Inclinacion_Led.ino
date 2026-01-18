/*
  TILT SENSOR (Interruptor de inclinación)

  Este programa enciende un LED cuando el sensor de inclinación
  detecta un cambio de posición.
*/

const int TILT_PIN = 2;   // Pin digital donde se conecta el sensor de inclinación
const int LED_PIN  = 8;   // Pin digital donde se conecta el LED

int estadoTilt;           // Variable para leer el estado del sensor

void setup() {
  // Configura el LED como salida
  pinMode(LED_PIN, OUTPUT);

  // Configura el sensor de inclinación como entrada con pull-up interna
  pinMode(TILT_PIN, INPUT_PULLUP);
}

void loop() {
  // Lee el estado del sensor de inclinación
  estadoTilt = digitalRead(TILT_PIN);

  // Si está totalmente inclinado, se activa; en caso contrario, se mantiene apagado.
  if (estadoTilt == LOW) {
    // Enciende el LED
    digitalWrite(LED_PIN, HIGH);
  } else {
    // Apaga el LED
    digitalWrite(LED_PIN, LOW);
  }
}
