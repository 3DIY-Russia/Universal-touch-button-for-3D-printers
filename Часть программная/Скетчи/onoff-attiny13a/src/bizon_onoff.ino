#define BLUE 2
#define WHITE 1    
#define RELAY_ON 4 
#define RELAY_OFF 3 
#define SENS 0

#define W_ON digitalWrite(WHITE, LOW);
#define W_OFF digitalWrite(WHITE, HIGH);
#define B_ON digitalWrite(BLUE, LOW);
#define B_OFF digitalWrite(BLUE, HIGH);
#define RON_ON digitalWrite(RELAY_ON, HIGH);
#define RON_OFF digitalWrite(RELAY_ON, LOW);
#define ROFF_ON digitalWrite(RELAY_OFF, HIGH);
#define ROFF_OFF digitalWrite(RELAY_OFF, LOW);
#define R_ON RON_ON; ROFF_OFF
#define R_OFF RON_OFF; ROFF_ON

byte count = 0;
byte mod = 0;  

void setup() {
  pinMode(SENS, INPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(WHITE, OUTPUT);
  pinMode(RELAY_ON, OUTPUT);
  pinMode(RELAY_OFF, OUTPUT);
  R_OFF;
  if (digitalRead(SENS)) { 
    while (1) {
      B_ON
      delay(250);
      B_OFF
      delay(250);
    }
  }
  for (byte i = 0; i < 5; i++) {
    W_OFF
    B_ON
    delay(200);
    W_ON
    B_OFF
    delay(200);
  }
  l_norm();
}

void loop() {
  if (digitalRead(SENS)) count++;
  if (!digitalRead(SENS)) {
    l_norm();
    count = 0;
  }
  if (count > 0) mig();
  if (count > 40) inv();
  delay(50);
}



void inv() {
  mod = !mod;
  l_norm();
  R_ON;
  while (digitalRead(SENS));
  //  if (mod) {
  delay(1000);
  count = 0;
  R_OFF;
  //  }
}

void l_norm() {
  if (!mod) {
    W_ON
    B_OFF
  } else {
    W_OFF
    B_ON
  }
}

void mig() {
  static byte fl = 0;
  static unsigned long timer = 0;
  if (timer + 100 > millis()) return;
  if (!fl) {
    W_ON
    B_OFF
  } else {
    W_OFF
    B_ON
  }
  fl = !fl;
  timer = millis();
}
