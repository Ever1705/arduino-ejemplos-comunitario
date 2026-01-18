// Definición de los pines del 1 al 7
const int pines[] = {2, 3, 4, 5, 6, 7, 8};

// Matriz de números (0-9)
// Cada fila representa un número, cada columna los segmentos a-g
byte numeros[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 0, 0, 1, 1}  // 9
};

void setup() {
  // Configurar pines 1 al 7 como salida
  for (int i = 0; i < 7; i++) {
    pinMode(pines[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 10; i++) {
    mostrarNumero(i);
    delay(1000); // Espera 1 segundo entre números
  }
}

void mostrarNumero(int n) {
  for (int s = 0; s < 7; s++) {
    digitalWrite(pines[s], numeros[n][s]);
  }
}