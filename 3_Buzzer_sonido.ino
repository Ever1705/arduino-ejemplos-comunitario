// Definición de pines
const int pinBoton = 13;
const int pinBuzzer = 2;

void setup() {
  // Configura el botón con resistencia interna (ahorra cableado)
  pinMode(pinBoton, INPUT_PULLUP);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  // Leer el estado del botón (LOW significa que está presionado)
  int estadoBoton = digitalRead(pinBoton);

  if (estadoBoton == LOW) {
    // Frecuencia de 440Hz
    tone(pinBuzzer, 440); 
  } else {
    // Si no se presiona se apaga el sonido inmediatamente
    noTone(pinBuzzer);
  }
}