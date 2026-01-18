/* 
  Este programa permite encender un LED cuando se presiona un botón.
  El botón utiliza la resistencia pull-up interna del Arduino,
  por lo que se conecta entre el pin y GND.
*/

int led = 2;     // Pin digital donde se conecta el LED
int boton = 3;   // Pin digital donde se conecta el botón

void setup() {
  // Configura el pin del LED como salida
  pinMode(led, OUTPUT);

  // Configura el pin del botón como entrada con resistencia pull-up
  pinMode(boton, INPUT_PULLUP);
}

void loop() {
  // Si el botón está presionado, el valor leído será HIGH
  if (digitalRead(boton) == HIGH) {
    // Enciende el LED
    digitalWrite(led, HIGH);
  } else {
    // Apaga el LED
    digitalWrite(led, LOW);
  }
}
