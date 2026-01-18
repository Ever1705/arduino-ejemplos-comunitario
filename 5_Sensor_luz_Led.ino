/*
  Luz nocturna automática con Arduino

  Este programa enciende un LED automáticamente cuando el nivel
  de luz ambiental es bajo, utilizando un sensor de luz (LDR)
  conectado a una entrada analógica.
*/

const int LED = 8;          // Pin digital donde se conecta el LED
const int SENSOR_LUZ = A0;  // Pin analógico donde se conecta el sensor de luz
int valorSensor;            // Almacena el valor leído del sensor
const int UMBRAL = 500;     // Nivel de luz mínimo para encender el LED

void setup() {
  // Configura el pin del LED como salida
  pinMode(LED, OUTPUT);

  // Inicializa la comunicación serial para monitorear valores
  Serial.begin(9600);
}

void loop() {
  // Lee el valor analógico del sensor de luz (0 a 1023)
  valorSensor = analogRead(SENSOR_LUZ);

  // Muestra el valor del sensor en el monitor serial
  Serial.println(valorSensor);

  // Si el nivel de luz es bajo, se enciende el LED
  if (valorSensor < UMBRAL) {
    digitalWrite(LED, HIGH);
  }
  // Si el nivel de luz es alto, se apaga el LED
  else {
    digitalWrite(LED, LOW);
  }
}
