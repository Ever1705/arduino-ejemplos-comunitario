/* 
  Este número representa el pin digital del Arduino
  al que se debe conectar el polo positivo (ánodo) del LED.
  Se recomienda usar una resistencia de 220Ω o 330Ω
  para evitar dañar el LED.
*/
int led = 7;

void setup() {
  // Configura el pin del LED como salida
  pinMode(led, OUTPUT);
}

void loop() {
  // Enciende el LED
  digitalWrite(led, HIGH);

  // Mantiene el LED encendido durante 1000 milisegundos (1 segundo)
  delay(1000);

  // Apaga el LED
  digitalWrite(led, LOW);

  // Mantiene el LED apagado durante 1000 milisegundos (1 segundo)
  delay(1000);
}

