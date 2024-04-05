// Кнопка сенсорная универсальная
//
// Назначение: управление питанием принтера с помощью MKS PWC
//
// Версия кода (прошивки): 1.1.0
// Версия предыдущего кода (прошивки): 1.0.0
// Обновления:
// - в функции inv() изменено время задержки после включения реле (R_ON). Было: 1000 мс, стало: 500 мс.
// - в функции inv() перемещена строка count = 0; после выключения реле (R_OFF).
// - в цикле loop() перемещена проверка count > 40 перед вызовом функции inv().
// Ожидания на следующие версии:
// - выпиливание delay, замена его на millis

#define BLUE 2      // синий светодиод
#define WHITE 1     // белый светодиод
#define RELAY_ON 4  // порт NO на MKS PWC
#define RELAY_OFF 3 // порт NC на MKS PWC
#define SENS 0      // чтение значений с TTP223

#define W_ON digitalWrite(WHITE, LOW);
#define W_OFF digitalWrite(WHITE, HIGH);
#define B_ON digitalWrite(BLUE, LOW);
#define B_OFF digitalWrite(BLUE, HIGH);
#define RON_ON digitalWrite(RELAY_ON, HIGH);
#define RON_OFF digitalWrite(RELAY_ON, LOW);
#define ROFF_ON digitalWrite(RELAY_OFF, HIGH);
#define ROFF_OFF digitalWrite(RELAY_OFF, LOW);
#define R_ON \
  RON_ON;    \
  ROFF_OFF
#define R_OFF \
  RON_OFF;    \
  ROFF_ON

byte count = 0;
byte mod = 0;

void setup()
{
  pinMode(SENS, INPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(WHITE, OUTPUT);
  pinMode(RELAY_ON, OUTPUT);
  pinMode(RELAY_OFF, OUTPUT);
  R_OFF;
  if (digitalRead(SENS))
  {
    while (1)
    {
      B_ON
          delay(250);
      B_OFF
      delay(250);
    }
  }
  for (byte i = 0; i < 5; i++)
  {
    W_OFF
    B_ON
        delay(200);
    W_ON
        B_OFF
            delay(200);
  }
  l_norm();
}

void loop()
{
  if (digitalRead(SENS))
    count++;
  if (!digitalRead(SENS))
  {
    l_norm();
    count = 0;
  }
  if (count > 0)
    mig();
  if (count > 40)
    inv();
  delay(50);
}

void inv()
{
  mod = !mod;
  l_norm();
  R_ON;
  delay(500); // время синала на MKS PWC о нажатии (500 мс = 0.5 сек)
  count = 0;
  R_OFF;
  while (digitalRead(SENS))
    ;
}

void l_norm()
{
  if (!mod)
  {
    W_ON
        B_OFF
  }
  else
  {
    W_OFF
    B_ON
  }
}

void mig()
{
  static byte fl = 0;
  static unsigned long timer = 0;
  if (timer + 100 > millis())
    return;
  if (!fl)
  {
    W_ON
        B_OFF
  }
  else
  {
    W_OFF
    B_ON
  }
  fl = !fl;
  timer = millis();
}
