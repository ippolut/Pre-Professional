#include <SPI.h>
#include <RFID.h>
#include <LiquidCrystal.h>
#include <AccelStepper.h>
#include <Stepper.h>
#include <NewPing.h>
#define MAX_DISTANCE 200 // Константа для определения максимального расстояния,

// Настройка пинов для RFID
#define SDA_DIO 9
#define RESET_DIO 13
#define PIN_TRIG 25
#define PIN_ECHO 23
RFID RC522(SDA_DIO, RESET_DIO); 
int i=40;

// Настройка пинов для LCD
LiquidCrystal lcd(8, 7, 6,5, 4, 3);

// Настройка пинов для шагового мотора
#define STEP_PIN 39
#define DIR_PIN 41
Stepper stepper(200, DIR_PIN, STEP_PIN);
AccelStepper mystepper(200, STEP_PIN, DIR_PIN);// Шаговый двигатель, управляемый платой                                                                                 
// ultrazvuk 
int distance =0 ;
int duration =0 ;
NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  RC522.init();
  lcd.begin(16, 2);
  stepper.setSpeed(1000); // Установка максимальной скорости
  mystepper.setAcceleration(100); // Настройка ускорения
  lcd.print("Поднесите карточку");
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(45, INPUT_PULLUP);
  pinMode(49, INPUT_PULLUP);

}
void openGates() {
  while (digitalRead(45) ==1){//пока кнопка2 не нажата
    stepper.step(-1400);
    lcd.print("working");
    lcd.clear();
    while (sonar.ping_cm()>i) {
      delay(50);
  // Получаем значение от датчика расстояния и сохраняем его в переменную
      unsigned int distance = sonar.ping_cm();
  // Печатаем расстояние в мониторе порта
      delay(500);
    }
    stepper.step(-1400);
    lcd.clear();
  }
}
void closeGates() {
  while (digitalRead(49) ==1){//пока кнопка2 не нажата
    stepper.step(1400);
    lcd.print("working");
    lcd.clear();
    while (sonar.ping_cm()>i) {
      delay(50);
  // Получаем значение от датчика расстояния и сохраняем его в переменную
      unsigned int distance = sonar.ping_cm();
  // Печатаем расстояние в мониторе порта
      delay(500);
    }
    stepper.step(1400);
    lcd.clear();
  }
}
void loop() {
  // Проверка наличия новой карточки
  if (RC522.isCard()){
    String uid = ""; // Хранение UID карточки
    RC522.readCardSerial();
    for(int i=0;i<5;i++){
      Serial.print(RC522.serNum[i],DEC);
    }
    Serial.println(uid); // Отправка UID по серийному порту

    // Ждем ответа по серийному порту
    while (!Serial.available());
    String receivedUid = Serial.readStringUntil('\n'); // Ожидание строки до символа переноса строки

    lcd.clear(); // Очистка дисплея

    // Проверка полученного UID
    if (receivedUid == uid) {
      lcd.clear();
      lcd.print("You Welcome");
      openGates();
      while (sonar.ping_cm()>i) {
        delay(50);
        unsigned int distance = sonar.ping_cm();
  // Печатаем расстояние в мониторе порта
        delay(500);
      }
      closeGates();
    }
    if (receivedUid == 1){ //  не найдено
      for (int i = 0; i < 5; i++) {
        lcd.print("working");
        delay(150);
        lcd.clear();
        delay(150);
      }
    }
    if (receivedUid == 2){ // время вышло
      for (int i = 0; i < 5; i++) {
        lcd.print("working");
        delay(450);
        lcd.clear();
        delay(450);
    }
    }
  }
}
}