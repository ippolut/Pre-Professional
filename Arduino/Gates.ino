#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <NewPing.h>
#define PIN_TRIG 49
#define PIN_ECHO 51
#define MAX_DISTANCE 200 // Константа для определения максимального расстояния, которое мы будем считать корректным.
NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCE);
const int solenoidPin = 48;
const int buzzerPin = 13;
#define NUM_KEYS 5 // количество знаков в коде  
long duration;
int distance=9;

// Настройка сервопривода
Servo servo;
const int servoPin = 4;
// Определяем правильный пин-код
char key;
char myarraw[NUM_KEYS] = { '6', '6', '6', '6', '6'};
char button_pressed[NUM_KEYS]; //массив для хранения нажатых кнопок
int k=0; // счетчик нажатий
int s=0; // счетчик совпадений нажатых кнопок с верными
String inputPin = "";

// Настройка матричной клавиатуры
const byte rows = 4; // Количество строк
const byte cols = 4; // Количество колонок
char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[rows] = {12, 11,9, 8}; 
byte colPins[cols] = {8, 7, 6, 5};      

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup() {
  pinMode(solenoidPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  servo.attach(11);
  digitalWrite(solenoidPin, LOW); // Соленоид закрыт
  Serial.begin(9600);
  servo.write(0);
}
void unlockGate() {
  int duration = 5;
  // Разблокировка калитки
  servo.write(90); // ставим угол поворота под 0
  digitalWrite(solenoidPin, HIGH); // Включаем соленоид
  duration = pulseIn(PIN_ECHO, HIGH); // включаем прием сигнала
  digitalWrite(buzzerPin, HIGH); // Издаём звуковой сигнал
  delay(1000);
  digitalWrite(buzzerPin,LOW);
  // Время ожидания для прохождения объекта
  while (sonar.ping_cm()<25) {
    delay(500);
  // Получаем значение от датчика расстояния и сохраняем его в переменную
    unsigned int distance = sonar.ping_cm();
  // Печатаем расстояние в мониторе порта
    Serial.print(distance);
    Serial.println("см");
    delay(50);
    // Ждем, пока не получим сигнал о прохождении
  }
}

void closeGate() {
  // Закрытие калитки
  servo.write(0); // ставим угол поворота под 90
  digitalWrite(solenoidPin, LOW); // Закрываем соленоид
}

void indicateError() {
  digitalWrite(buzzerPin, HIGH); // Издаём звуковой сигнал
  delay(1000);
  digitalWrite(buzzerPin,LOW);
}
void loop ()
  { key = keypad.getKey(); 
  if ( key != NO_KEY ) 
  {
    Serial.println(key);
    button_pressed [k] = key; 
    k = k + 1; 
    delay(100);
    if(k == NUM_KEYS) 
      {for ( uint8_t i = 0; i < NUM_KEYS; i++) 
      {
      if (button_pressed[i] == myarraw[i]) 
        {s = s + 1; 
 
 
}
 
}
 
    if(s == NUM_KEYS)
    {
      unlockGate();
      digitalWrite(PIN_TRIG, LOW);
      delay(4000);
      closeGate();
      k=0; 
      s=0;
    } else { 
    indicateError();
    k=0; 
    s=0; 
    }
  }
}
}