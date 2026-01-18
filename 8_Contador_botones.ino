const int a = 2, b = 3, c = 4, d = 5, e = 6, f = 7, g = 8; // Pines correspondiente a los segmentos de la pantalla
const int upPin = 0;   // Sumar un numero
const int downPin = 1; // Restar un numero
int x = 0;   
int k = 0;

int upx = 0, upy = 0;
int downx = 0, downy = 0;

void setup() {
  pinMode(a, OUTPUT);  
  pinMode(b, OUTPUT);  
  pinMode(c, OUTPUT);  
  pinMode(d, OUTPUT);  
  pinMode(e, OUTPUT);  
  pinMode(f, OUTPUT);  
  pinMode(g, OUTPUT);  
  
  // Usar INPUT_PULLUP para no necesitar resistencias externas
  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  
  segmentdigit(x);  
}

void loop() {  
  // Leemos los pines 1 y 0
  upx = digitalRead(upPin);
  downx = digitalRead(downPin);

  checkupxButtonPress();
  checkdownxButtonPress();  

  if(k){
    k = 0;
    turnOff();
    segmentdigit(x);
  }
}

// Para sumar un numero
void checkupxButtonPress() {
  if (upx != upy) {
    if (upx == LOW) { 
      k = 1;
      x++;
      if(x > 9) x = 0;
    }
    delay(50); //retardo
  }
  upy = upx;
}

// Para restar un numero
void checkdownxButtonPress() {
  if (downx != downy) {
    if (downx == LOW) {
      k = 1;
      x--;
      if(x < 0) x = 9;
    }
    delay(50);//retardo
  }
  downy = downx;
}

void segmentdigit(int digit) {
  // Logica de segmentos de la pantalla
  if(digit!=1 && digit != 4) digitalWrite(a, HIGH);
  if(digit != 5 && digit != 6) digitalWrite(b, HIGH);
  if(digit != 2) digitalWrite(c, HIGH);
  if(digit != 1 && digit != 4 && digit != 7) digitalWrite(d, HIGH);
  if(digit == 2 || digit == 6 || digit == 8 || digit == 0) digitalWrite(e, HIGH);
  if(digit != 1 && digit != 2 && digit != 3 && digit != 7) digitalWrite(f, HIGH);
  if(digit != 0 && digit != 1 && digit != 7) digitalWrite(g, HIGH);
}

void turnOff() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}