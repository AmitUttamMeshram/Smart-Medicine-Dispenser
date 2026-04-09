#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include "HX711.h"
#include <ESP32Servo.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RTC
RTC_DS3231 rtc;

// HX711
HX711 scale;
#define DT 32
#define SCK 33

// Servos
Servo s1, s2, s3;

// Pins
#define IR_PIN 14
#define BUZZER 13

// Medicine time (example)
int medHour = 9;
int medMinute = 32;

void setup() {
  Serial.begin(115200);

  // LCD
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  // RTC
  rtc.begin();

  // HX711
  scale.begin(DT, SCK);
  scale.set_scale();
  scale.tare();

  // Servos
  s1.attach(25);
  s2.attach(26);
  s3.attach(27);

  // IR + buzzer
  pinMode(IR_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());

  // Check medicine time
  if (now.hour() == medHour && now.minute() == medMinute) {
    dispenseMedicine();
    delay(60000); // avoid repeat
  }

  delay(1000);
}

void dispenseMedicine() {
  lcd.clear();
  lcd.print("Take Medicine!");

  // Buzzer alert
  for (int i = 0; i < 5; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(300);
    digitalWrite(BUZZER, LOW);
    delay(300);
  }

  // Rotate servos
  s1.write(90); delay(1000); s1.write(0);
  s2.write(90); delay(1000); s2.write(0);
  s3.write(90); delay(1000); s3.write(0);

  lcd.clear();
  lcd.print("Dispensed");

  // Check weight
  float weight = scale.get_units(5);
  Serial.println(weight);

  // Wait for hand detection
  lcd.setCursor(0,1);
  lcd.print("Waiting pickup");

  while (digitalRead(IR_PIN) == HIGH) {
    delay(100);
  }

  lcd.clear();
  lcd.print("Taken!");
  delay(2000);
}