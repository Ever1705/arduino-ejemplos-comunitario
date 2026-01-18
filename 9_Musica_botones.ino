/*
  =====================================================
  MELODÍAS NAVIDEÑAS CON ARDUINO Y BUZZER
  =====================================================
  
  Este programa reproduce tres canciones navideñas usando un buzzer piezoeléctrico.
*/

// ==================== DEFINICIÓN DE NOTAS MUSICALES ====================
// Cada nota tiene una frecuencia específica en Hz
// Formato: NOTE_[Nota][Octava] = frecuencia en Hz

#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784

// ==================== CONFIGURACIÓN DE PINES ====================
const int PIN_BUZZER = 9;        // Pin del buzzer
const int PIN_LED = 13;          // LED indicador
const int PIN_BOTON_1 = 2;       // Botón para Jingle Bells
const int PIN_BOTON_2 = 3;       // Botón para Santa Claus
const int PIN_BOTON_3 = 4;       // Botón para We Wish You

// ==================== MELODÍA 1: JINGLE BELLS ====================
int melodia_jingle[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

// Duración de cada nota (4=negra, 8=corchea, 2=blanca, etc.)
int duracion_jingle[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

// ==================== MELODÍA 2: WE WISH YOU A MERRY CHRISTMAS ====================
int melodia_wish[] = {
  NOTE_B3, 
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};

int duracion_wish[] = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};

// ==================== MELODÍA 3: SANTA CLAUS IS COMING TO TOWN ====================
int melodia_santa[] = {
  NOTE_G4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_B3,
  NOTE_C4
};

int duracion_santa[] = {
  8,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 2,
  4, 4, 4, 4,
  4, 2, 4,
  1
};

// ==================== CONFIGURACIÓN INICIAL ====================
void setup() {
  // Configurar pines de salida
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  
  // Configurar pines de entrada (botones)
  pinMode(PIN_BOTON_1, INPUT);
  pinMode(PIN_BOTON_2, INPUT);
  pinMode(PIN_BOTON_3, INPUT);
  
  // Iniciar comunicación serial (opcional, para debugging)
  Serial.begin(9600);
  Serial.println("Sistema de melodias navidenas iniciado");
  Serial.println("Boton 1: Jingle Bells");
  Serial.println("Boton 2: Santa Claus");
  Serial.println("Boton 3: We Wish You");
}

// ==================== BUCLE PRINCIPAL ====================
void loop() {
  // Leer el estado de cada botón
  if (digitalRead(PIN_BOTON_1) == HIGH) {
    reproducirMelodia(1);
  } 
  else if (digitalRead(PIN_BOTON_2) == HIGH) {
    reproducirMelodia(2);
  } 
  else if (digitalRead(PIN_BOTON_3) == HIGH) {
    reproducirMelodia(3);
  }
}

// ==================== FUNCIÓN PARA REPRODUCIR MELODÍAS ====================
/*
  Reproduce una de las tres melodías disponibles
  Parámetro: numeroCancion (1=Jingle Bells, 2=Santa Claus, 3=We Wish You)
*/
void reproducirMelodia(int numeroCancion) {
  int* melodia;              // Puntero a la melodía
  int* duraciones;           // Puntero a las duraciones
  int numNotas;              // Cantidad de notas
  int velocidadBase;         // Velocidad base de reproducción
  
  // Seleccionar la melodía según el botón presionado
  switch(numeroCancion) {
    case 1:
      Serial.println("Reproduciendo: Jingle Bells");
      melodia = melodia_jingle;
      duraciones = duracion_jingle;
      numNotas = sizeof(melodia_jingle) / sizeof(int);
      velocidadBase = 1000;
      break;
      
    case 2:
      Serial.println("Reproduciendo: Santa Claus is Coming to Town");
      melodia = melodia_santa;
      duraciones = duracion_santa;
      numNotas = sizeof(melodia_santa) / sizeof(int);
      velocidadBase = 900;
      break;
      
    case 3:
      Serial.println("Reproduciendo: We Wish You a Merry Christmas");
      melodia = melodia_wish;
      duraciones = duracion_wish;
      numNotas = sizeof(melodia_wish) / sizeof(int);
      velocidadBase = 1000;
      break;
      
    default:
      return; // Si el número no es válido, salir
  }
  
  // Reproducir cada nota de la melodía
  for (int i = 0; i < numNotas; i++) {
    // Calcular duración de la nota
    // Ejemplo: negra (4) = 1000/4 = 250ms
    int duracionNota = velocidadBase / duraciones[i];
    
    // Reproducir el tono
    reproducirTono(PIN_BUZZER, melodia[i], duracionNota);
    
    // Pausa entre notas (30% más que la duración)
    int pausa = duracionNota * 1.30;
    delay(pausa);
    
    // Silencio entre notas
    noTone(PIN_BUZZER);
  }
  
  Serial.println("Melodia finalizada\n");
}

// ==================== FUNCIÓN PARA GENERAR TONOS ====================
/*
  Genera un tono en el buzzer usando oscilación manual
  
  Parámetros:
  - pin: Pin donde está conectado el buzzer
  - frecuencia: Frecuencia del tono en Hz
  - duracion: Duración del tono en milisegundos
  
  Nota: Esta función genera el tono manualmente alternando HIGH/LOW
  para mayor control. También se puede usar la función tone() de Arduino.
*/
void reproducirTono(int pin, long frecuencia, long duracion) {
  // Encender LED indicador
  digitalWrite(PIN_LED, HIGH);
  
  // Calcular el tiempo entre transiciones HIGH-LOW
  // Un ciclo completo necesita dos transiciones
  long delayValue = 1000000 / frecuencia / 2;
  
  // Calcular cuántos ciclos necesitamos para la duración deseada
  long numCiclos = frecuencia * duracion / 1000;
  
  // Generar la onda cuadrada
  for (long i = 0; i < numCiclos; i++) {
    digitalWrite(pin, HIGH);          // Subir voltaje
    delayMicroseconds(delayValue);    // Esperar
    digitalWrite(pin, LOW);           // Bajar voltaje
    delayMicroseconds(delayValue);    // Esperar
  }
  
  // Apagar LED indicador
  digitalWrite(PIN_LED, LOW);
}