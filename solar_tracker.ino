#include <LiquidCrystal.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13                

OneWire oneWire(ONE_WIRE_BUS);        
DallasTemperature sensors(&oneWire);  

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

int ldr_up_pin = A2;
int ldr_right_pin = A0;
int ldr_down_pin = A3;
int ldr_left_pin = A1;

int sw1 = 2; // ÜST
int sw2 = A4; // ALT

int m1p1 = 9; // SAĞ
int m1p2 = 10; // SOL

int m2p1 = 11; // YUKARI
int m2p2 = 12;  // AŞAĞI

int ldr_up;
int ldr_right;
int ldr_down;
int ldr_left;

int current_sensor = A4;

void setup() {
  Serial.begin(9600);

  pinMode(A4, INPUT_PULLUP);
  pinMode(2, INPUT);
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  sensors.begin();
  pinMode(13, INPUT);

  lcd.begin(16, 2);
  lcd.noAutoscroll();

  ldr_up = analogRead(ldr_up_pin);
  ldr_right = analogRead(ldr_right_pin);
  ldr_down = analogRead(ldr_down_pin);
  ldr_left = analogRead(ldr_left_pin);
  
  /*
   lcd.setCursor(0,0); lcd.print("U:");
   lcd.setCursor(8,0); lcd.print("R:");  
   lcd.setCursor(0,1); lcd.print("D:");
   lcd.setCursor(8,1); lcd.print("L:");
  */ 
}

void loop() {
// LDR DEĞERLERİ
 ldr_up = analogRead(ldr_up_pin);
 ldr_right = analogRead(ldr_right_pin);
 ldr_down = analogRead(ldr_down_pin);
 ldr_left = analogRead(ldr_left_pin);
// SWITCH ON/OFF
 bool ustSwitch = digitalRead(sw1) == LOW;
 bool altSwitch = digitalRead(sw2) == LOW;

// MOTOR KONTROL
  if (ldr_left < ldr_right - 100) { 
    digitalWrite(m1p1, HIGH);
    digitalWrite(m1p2, LOW);
 
  } else if (ldr_right < ldr_left  - 100) {
    digitalWrite(m1p1, LOW);
    digitalWrite(m1p2, HIGH);
  } else {
    digitalWrite(m1p1, LOW);
    digitalWrite(m1p2, LOW);
  }
  if (ldr_up < ldr_down - 50 && altSwitch) {
    digitalWrite(m2p1, LOW);
    digitalWrite(m2p2, HIGH);
  }  else if (ldr_down < ldr_up - 50 && ustSwitch) {
    digitalWrite(m2p1, HIGH);
    digitalWrite(m2p2, LOW);
  }   
  else {
    digitalWrite(m2p1, LOW);
    digitalWrite(m2p2, LOW);
  }

delay(1000);

/* AKIM SENSÖRÜ 
int adc = analogRead(current_sensor);
float voltage = adc*5/1023.0;
float current = (voltage-2.5)/0.185;
Serial.print("adc:");
Serial.println(adc);
Serial.print("volt:");
Serial.println(voltage);
Serial.print("Current:");
Serial.println(current);
lcd.setCursor(0, 1);
lcd.print("V:");
lcd.print(voltage, 2); 
lcd.setCursor(8, 1);
lcd.print("I:");       
lcd.print(current, 2);
*/

/*
SICAKLIK ÖLÇÜMÜ
sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0); 

  Serial.print("Temperature (C): ");
  Serial.println(temperatureC);

  if (temperatureC == DEVICE_DISCONNECTED_C) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    Serial.println("Error: Sensor disconnected!");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatureC, 1); 
    lcd.print((char)223);       
    lcd.print("C");
  }

*/

/*
LCD İÇİN LDR DEĞERLERİ
  lcd.setCursor(2, 0); lcd.print("    ");
   lcd.setCursor(2, 0); lcd.print(ldr_up);
   lcd.setCursor(10, 0); lcd.print("    ");
   lcd.setCursor(10, 0); lcd.print(ldr_right);
   lcd.setCursor(2, 1); lcd.print("    ");
   lcd.setCursor(2, 1); lcd.print(ldr_down);
   lcd.setCursor(10, 1); lcd.print("    ");
   lcd.setCursor(10, 1); lcd.print(ldr_left);
*/  
}


