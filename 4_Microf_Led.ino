int MIC = 2;      // Pin digital D0 del módulo de sonido conectado al pin 2
int LED = 3;      // Ánodo del LED conectado al pin 3
int VALOR;        // Almacena el valor leído desde D0 (HIGH o LOW)
int ESTADO;       // Almacena el estado actual del LED

void setup() {
  // Configura el pin del micrófono como entrada digital
  pinMode(MIC, INPUT);

  // Configura el pin del LED como salida
  pinMode(LED, OUTPUT);
}

void loop() {
  // Lee el estado digital del módulo de sonido
  VALOR = digitalRead(MIC);

  // Si se detecta un sonido (salida digital en HIGH)
  if (VALOR == HIGH) {

    // Obtiene el estado actual del LED
    ESTADO = digitalRead(LED);

    // Cambia el estado del LED (encendido ↔ apagado)
    digitalWrite(LED, !ESTADO);

    // Retardo de 500 ms para evitar múltiples activaciones por un mismo sonido
    delay(500);
  }
}
