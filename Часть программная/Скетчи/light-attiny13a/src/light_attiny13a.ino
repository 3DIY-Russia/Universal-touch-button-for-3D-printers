#define BLUE 2
#define WHITE 1   
#define LED_O 4
#define LED_R 3
#define SENS 0

#define W_ON digitalWrite(WHITE, LOW);
#define W_OFF digitalWrite(WHITE, HIGH);
#define B_ON digitalWrite(BLUE, LOW);
#define B_OFF digitalWrite(BLUE, HIGH);
#define LED_ON digitalWrite(LED_O, HIGH);
#define LED_OFF digitalWrite(LED_O, LOW);
#define LED_ON_R digitalWrite(LED_R, HIGH);
#define LED_OFF_R digitalWrite(LED_R, LOW);
#define L_ON LED_ON; LED_OFF_R;
#define L_OFF LED_OFF; LED_ON_R;

byte count = 0;
byte mod = 0; 

void setup() {
  pinMode(SENS, INPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(WHITE, OUTPUT);
  pinMode(LED_O, OUTPUT);
  pinMode(LED_R, OUTPUT);
  L_OFF;
  if (digitalRead(SENS)) { 
    while (1) {
      B_ON
      delay(100);
      B_OFF
      delay(100);
    }
  }
  for (byte i = 0; i < 5; i++) { 
    W_ON
    B_OFF
    delay(200);
    W_OFF
    B_OFF
    delay(200);
  }
  l_norm();
}

void loop() {
  if (digitalRead(SENS)) count++;
  if (!digitalRead(SENS)) {
    count = 0;
  }
  if (count > 2) inv(); 
  delay(50);
}


void inv() {
  mod = !mod;
  l_norm();
  while (digitalRead(SENS)); 
  count = 0;
  delay(100);
}

void l_norm() {
  if (!mod) { 
    W_ON
    B_OFF
    L_OFF
  } else {
    W_OFF
    B_ON
    L_ON
  }
}
