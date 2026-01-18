//Juego de memorizar el patron

// ============================================
// DEFINICIONES DE NOTAS MUSICALES
// Frecuencias en Hz para cada nota musical
// ============================================
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

// ============================================
// CONSTANTES DE SELECCIÓN DE BOTONES/LEDs
// Se utilizan operaciones de bits para manejar múltiples LEDs simultáneamente
// ============================================
#define CHOICE_OFF      0 // Apagar todos los LEDs
#define CHOICE_NONE     0 // Ningún botón presionado
#define CHOICE_RED      (1 << 0) // Bit 0: Botón/LED rojo
#define CHOICE_GREEN    (1 << 1) // Bit 1: Botón/LED verde
#define CHOICE_BLUE     (1 << 2) // Bit 2: Botón/LED azul
#define CHOICE_YELLOW   (1 << 3) // Bit 3: Botón/LED amarillo

// ============================================
// PINES DE LOS LEDs
// ============================================
#define LED_RED     10
#define LED_GREEN   3
#define LED_BLUE    13
#define LED_YELLOW  5

// ============================================
// PINES DE LOS BOTONES
// ============================================
#define BUTTON_RED    9
#define BUTTON_GREEN  2
#define BUTTON_BLUE   12
#define BUTTON_YELLOW 6

// ============================================
// PINES DEL BUZZER (ZUMBADOR)
// Se utilizan dos pines para generar un sonido más potente
// ============================================
#define BUZZER1  0
#define BUZZER2  1

// ============================================
// PARÁMETROS DE CONFIGURACIÓN DEL JUEGO
// ============================================
#define ROUNDS_TO_WIN      13   // Número de rondas para ganar (13 es desafiante pero alcanzable)
#define ENTRY_TIME_LIMIT   3000 // Tiempo máximo de espera por entrada del usuario (en milisegundos)

// ============================================
// MODOS DE JUEGO DISPONIBLES
// ============================================
#define MODE_MEMORY  0 // Modo memoria: memoriza y repite la secuencia
#define MODE_BATTLE  1 // Modo batalla: dos jugadores compitiendo
#define MODE_BEEGEES 2 // Easter egg: reproduce música disco

// ============================================
// VARIABLES GLOBALES DEL ESTADO DEL JUEGO
// ============================================
byte gameMode = MODE_MEMORY;  // Modo de juego actual (por defecto: memoria)
byte gameBoard[32];           // Array que almacena la secuencia de botones a memorizar
byte gameRound = 0;           // Contador de rondas completadas exitosamente

void setup()
{
  // ============================================
  // CONFIGURACIÓN INICIAL DEL HARDWARE
  // ============================================
  
  // Configurar botones como entradas con resistencias pull-up internas
  // Esto significa que los botones leen HIGH cuando no están presionados
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);

  // Configurar LEDs como salidas
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  // Configurar pines del buzzer como salidas
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);

  // ============================================
  // DETECCIÓN DEL MODO DE JUEGO AL INICIO
  // ============================================
  
  gameMode = MODE_MEMORY; // Establecer modo memoria por defecto

  // Si el botón amarillo (inferior derecho) está presionado al encender,
  // activar el Easter egg de música disco
  if (checkButton() == CHOICE_YELLOW) play_beegees();

  // Si el botón verde (superior derecho) está presionado al encender,
  // activar el modo batalla para dos jugadores
  if (checkButton() == CHOICE_GREEN)
  {
    gameMode = MODE_BATTLE; // Cambiar a modo batalla

    // Indicación visual: encender LED verde
    setLEDs(CHOICE_GREEN);
    toner(CHOICE_GREEN, 150);

    // Encender los otros tres LEDs hasta que se suelte el botón
    setLEDs(CHOICE_RED | CHOICE_BLUE | CHOICE_YELLOW);

    // Esperar a que el usuario suelte el botón
    while(checkButton() != CHOICE_NONE) ;
    
    // El modo batalla se ejecutará en el loop principal
  }

  // Reproducir melodía de bienvenida al completar la configuración
  play_winner();
}

void loop()
{
  // ============================================
  // BUCLE PRINCIPAL DEL JUEGO
  // ============================================
  
  // Mostrar modo de atracción: luces parpadeantes esperando entrada del usuario
  attractMode();

  // Señal de inicio del juego: destello de todos los LEDs
  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW);
  delay(1000);
  setLEDs(CHOICE_OFF);
  delay(250);

  // Ejecutar el modo de juego correspondiente
  if (gameMode == MODE_MEMORY)
  {
    // Jugar modo memoria y procesar el resultado
    if (play_memory() == true) 
      play_winner(); // Victoria: reproducir sonido de ganador
    else 
      play_loser(); // Derrota: reproducir sonido de perdedor
  }

  if (gameMode == MODE_BATTLE)
  {
    // Jugar modo batalla hasta que alguien pierda
    play_battle();
    
    // El jugador perdió, reproducir sonido de derrota
    play_loser();
  }
}

// ============================================
// FUNCIONES RELACIONADAS CON LA LÓGICA DEL JUEGO
// ============================================

/**
 * Juega el modo memoria estándar (tipo Simon Dice)
 * Retorna: true si el jugador gana, false si pierde
 */
boolean play_memory(void)
{
  // Inicializar generador de números aleatorios con tiempo transcurrido
  randomSeed(millis());

  gameRound = 0; // Reiniciar el contador de rondas

  // Continuar hasta alcanzar el número de rondas necesarias para ganar
  while (gameRound < ROUNDS_TO_WIN) 
  {
    // Agregar un nuevo botón aleatorio a la secuencia
    add_to_moves();

    // Reproducir toda la secuencia actual para que el jugador la memorice
    playMoves();

    // El jugador debe repetir toda la secuencia correctamente
    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
    {
      // Esperar a que el jugador presione un botón
      byte choice = wait_for_button();

      // Si se agotó el tiempo de espera, el jugador pierde
      if (choice == 0) return false;

      // Si el botón presionado no coincide con la secuencia, el jugador pierde
      if (choice != gameBoard[currentMove]) return false;
    }

    // El jugador completó la ronda correctamente, esperar antes de la siguiente
    delay(1000);
  }

  // El jugador completó todas las rondas exitosamente
  return true;
}

/**
 * Juega el modo batalla para dos jugadores
 * Un jugador presiona un botón y pasa el dispositivo al otro
 * El segundo jugador repite la secuencia y agrega uno más
 * Retorna cuando alguien comete un error
 */
boolean play_battle(void)
{
  gameRound = 0; // Reiniciar el juego desde el principio

  while (1) // Bucle infinito hasta que alguien pierda
  {
    // Esperar a que el usuario ingrese el siguiente movimiento
    byte newButton = wait_for_button();
    
    // Agregar este nuevo botón al array de la secuencia
    gameBoard[gameRound++] = newButton;

    // El otro jugador debe repetir toda la secuencia
    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
    {
      byte choice = wait_for_button();

      // Si se agotó el tiempo, el jugador actual pierde
      if (choice == 0) return false;

      // Si la elección es incorrecta, el jugador pierde
      if (choice != gameBoard[currentMove]) return false;
    }

    // Dar 100ms extra para que el jugador pase el dispositivo al otro
    delay(100);
  }

  return true; // Esta línea nunca debería ejecutarse
}

/**
 * Reproduce la secuencia actual de movimientos
 * Enciende los LEDs y toca los tonos correspondientes
 */
void playMoves(void)
{
  for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++) 
  {
    // Reproducir el tono y encender el LED del botón actual
    toner(gameBoard[currentMove], 150);

    // Pausa entre botones (reducir este valor aumenta la dificultad)
    // 150ms funciona bien, 75ms es muy rápido
    delay(150);
  }
}

/**
 * Agrega un nuevo botón aleatorio a la secuencia del juego
 * Utiliza el temporizador como fuente de aleatoriedad
 */
void add_to_moves(void)
{
  // Generar número aleatorio entre 0 y 3 (4 opciones)
  byte newButton = random(0, 4);

  // Convertir el número (0-3) a la constante CHOICE correspondiente
  if(newButton == 0) newButton = CHOICE_RED;
  else if(newButton == 1) newButton = CHOICE_GREEN;
  else if(newButton == 2) newButton = CHOICE_BLUE;
  else if(newButton == 3) newButton = CHOICE_YELLOW;

  // Agregar el nuevo botón al array y avanzar el contador de rondas
  gameBoard[gameRound++] = newButton;
}

// ============================================
// FUNCIONES DE CONTROL DEL HARDWARE
// ============================================

/**
 * Enciende uno o más LEDs según el parámetro recibido
 * Parámetro leds: byte compuesto de CHOICE_RED, CHOICE_YELLOW, etc.
 * Se pueden combinar múltiples LEDs usando el operador OR (|)
 */
void setLEDs(byte leds)
{
  // Encender o apagar LED rojo según el bit correspondiente
  if ((leds & CHOICE_RED) != 0)
    digitalWrite(LED_RED, HIGH);
  else
    digitalWrite(LED_RED, LOW);

  // Encender o apagar LED verde según el bit correspondiente
  if ((leds & CHOICE_GREEN) != 0)
    digitalWrite(LED_GREEN, HIGH);
  else
    digitalWrite(LED_GREEN, LOW);

  // Encender o apagar LED azul según el bit correspondiente
  if ((leds & CHOICE_BLUE) != 0)
    digitalWrite(LED_BLUE, HIGH);
  else
    digitalWrite(LED_BLUE, LOW);

  // Encender o apagar LED amarillo según el bit correspondiente
  if ((leds & CHOICE_YELLOW) != 0)
    digitalWrite(LED_YELLOW, HIGH);
  else
    digitalWrite(LED_YELLOW, LOW);
}

/**
 * Espera a que el usuario presione un botón
 * Retorna: el color del botón presionado o 0 si se agotó el tiempo
 */
byte wait_for_button(void)
{
  // Guardar el tiempo de inicio para controlar el timeout
  long startTime = millis();

  // Continuar esperando hasta que se agote el tiempo límite
  while ( (millis() - startTime) < ENTRY_TIME_LIMIT)
  {
    byte button = checkButton();

    // Si se detectó un botón presionado
    if (button != CHOICE_NONE)
    { 
      // Reproducir el tono correspondiente al botón presionado
      toner(button, 150);

      // Esperar a que el usuario suelte el botón (evita lecturas múltiples)
      while(checkButton() != CHOICE_NONE) ;

      // Pequeña pausa para eliminar rebotes y toques dobles accidentales
      delay(10);

      return button;
    }
  }

  // Si llegamos aquí, se agotó el tiempo sin que se presionara ningún botón
  return CHOICE_NONE;
}

/**
 * Verifica qué botón está siendo presionado actualmente
 * Retorna: un bit en la posición correspondiente a CHOICE_RED, CHOICE_GREEN, etc.
 *          o CHOICE_NONE si ningún botón está presionado
 */
byte checkButton(void)
{
  // Los botones tienen pull-up, por lo que leen 0 cuando están presionados
  if (digitalRead(BUTTON_RED) == 0) return(CHOICE_RED); 
  else if (digitalRead(BUTTON_GREEN) == 0) return(CHOICE_GREEN); 
  else if (digitalRead(BUTTON_BLUE) == 0) return(CHOICE_BLUE); 
  else if (digitalRead(BUTTON_YELLOW) == 0) return(CHOICE_YELLOW);

  return(CHOICE_NONE); // Ningún botón está presionado
}

/**
 * Enciende un LED y reproduce el tono correspondiente
 * Frecuencias asignadas:
 * - Rojo (superior izquierdo):    440Hz - periodo 2.272ms
 * - Verde (superior derecho):     880Hz - periodo 1.136ms
 * - Azul (inferior izquierdo):    587.33Hz - periodo 1.702ms
 * - Amarillo (inferior derecho):  784Hz - periodo 1.276ms
 */
void toner(byte which, int buzz_length_ms)
{
  // Encender el LED correspondiente
  setLEDs(which);

  // Reproducir el sonido asociado con el LED seleccionado
  switch(which) 
  {
  case CHOICE_RED:
    buzz_sound(buzz_length_ms, 1136); 
    break;
  case CHOICE_GREEN:
    buzz_sound(buzz_length_ms, 568); 
    break;
  case CHOICE_BLUE:
    buzz_sound(buzz_length_ms, 851); 
    break;
  case CHOICE_YELLOW:
    buzz_sound(buzz_length_ms, 638); 
    break;
  }

  // Apagar todos los LEDs después de reproducir el sonido
  setLEDs(CHOICE_OFF);
}

/**
 * Alterna el estado del buzzer para generar un tono
 * Parámetro buzz_length_ms: duración total del sonido en milisegundos
 * Parámetro buzz_delay_us: microsegundos entre alternancias (determina la frecuencia)
 */
void buzz_sound(int buzz_length_ms, int buzz_delay_us)
{
  // Convertir la duración total de milisegundos a microsegundos
  long buzz_length_us = buzz_length_ms * (long)1000;

  // Continuar alternando hasta que el tiempo restante sea menor que un ciclo completo
  while (buzz_length_us > (buzz_delay_us * 2))
  {
    // Restar el tiempo de un ciclo completo (dos alternancias)
    buzz_length_us -= buzz_delay_us * 2;

    // Primera mitad del ciclo: BUZZER1 LOW, BUZZER2 HIGH
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(buzz_delay_us);

    // Segunda mitad del ciclo: BUZZER1 HIGH, BUZZER2 LOW
    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(buzz_delay_us);
  }
}

/**
 * Reproduce la animación y sonido de victoria
 * Alterna entre pares de LEDs con efectos de sonido
 */
void play_winner(void)
{
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winner_sound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winner_sound();
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winner_sound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winner_sound();
}

/**
 * Genera el sonido característico de victoria
 * Crea un efecto de barrido de frecuencia descendente con repeticiones
 */
void winner_sound(void)
{
  // Barrido de frecuencia: de 250 microsegundos a 70 microsegundos
  for (byte x = 250 ; x > 70 ; x--)
  {
    // Repetir cada frecuencia 3 veces para efecto de pulsación
    for (byte y = 0 ; y < 3 ; y++)
    {
      digitalWrite(BUZZER2, HIGH);
      digitalWrite(BUZZER1, LOW);
      delayMicroseconds(x);

      digitalWrite(BUZZER2, LOW);
      digitalWrite(BUZZER1, HIGH);
      delayMicroseconds(x);
    }
  }
}

/**
 * Reproduce la animación y sonido de derrota
 * Alterna entre pares de LEDs con tonos graves
 */
void play_loser(void)
{
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);

  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);

  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);

  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);
}

/**
 * Muestra el modo de atracción mientras espera que el usuario inicie el juego
 * Los LEDs parpadean en secuencia circular para atraer la atención
 */
void attractMode(void)
{
  while(1) 
  {
    // Secuencia de LEDs: Rojo -> Azul -> Verde -> Amarillo
    setLEDs(CHOICE_RED);
    delay(100);
    if (checkButton() != CHOICE_NONE) return; // Salir si se presiona cualquier botón

    setLEDs(CHOICE_BLUE);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;

    setLEDs(CHOICE_GREEN);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;

    setLEDs(CHOICE_YELLOW);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;
  }
}

// ============================================
// FUNCIONES DEL EASTER EGG (BEE GEES)
// ============================================

// Melodía principal: cada nota dura aproximadamente 1/8 de tiempo
// Los ceros (0) representan silencios/pausas musicales
int melody[] = {
  NOTE_G4, NOTE_A4, 0, NOTE_C5, 0, 0, NOTE_G4, 0, 0, 0,
  NOTE_E4, 0, NOTE_D4, NOTE_E4, NOTE_G4, 0,
  NOTE_D4, NOTE_E4, 0, NOTE_G4, 0, 0,
  NOTE_D4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_A4, 0, NOTE_C5, 0};

int noteDuration = 115; // Duración de cada nota (establece el tempo disco)
int LEDnumber = 0;      // Índice del LED actual durante la reproducción

/**
 * Easter egg: reproduce música disco estilo Bee Gees en bucle
 * Se activa manteniendo presionado el botón amarillo durante el encendido
 */
void play_beegees()
{
  // Indicar que se activó el modo Bee Gees con el LED amarillo
  setLEDs(CHOICE_YELLOW);
  toner(CHOICE_YELLOW, 150);

  // Encender los otros tres LEDs hasta que se suelte el botón
  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE);

  // Esperar a que el usuario suelte el botón
  while(checkButton() != CHOICE_NONE) ;

  // Apagar todos los LEDs
  setLEDs(CHOICE_NONE);

  // Pausa dramática antes de iniciar la música
  delay(1000);

  // Configurar BUZZER1 en bajo para que BUZZER2 genere el tono
  digitalWrite(BUZZER1, LOW);

  // Reproducir la canción en bucle hasta que se presione un botón
  while(checkButton() == CHOICE_NONE)
  {
    // Iterar sobre cada nota de la melodía (32 notas en total)
    for (int thisNote = 0; thisNote < 32; thisNote++) {
      // Cambiar al siguiente LED en cada nota
      changeLED();
      
      // Reproducir la nota actual con la duración especificada
      tone(BUZZER2, melody[thisNote], noteDuration);
      
      // Pausa entre notas para distinguirlas mejor
      // La duración de la nota + 30% crea un buen efecto de separación
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      
      // Detener el tono actual
      noTone(BUZZER2);
    }
  }
}

/**
 * Avanza al siguiente LED en secuencia circular
 * Crea un efecto visual de rotación durante la reproducción musical
 */
void changeLED(void)
{
  // Activar el LED actual usando desplazamiento de bits
  setLEDs(1 << LEDnumber);

  // Avanzar al siguiente LED
  LEDnumber++;
  
  // Si se supera el último LED (3), volver al primero (0)
  if(LEDnumber > 3) LEDnumber = 0;
}