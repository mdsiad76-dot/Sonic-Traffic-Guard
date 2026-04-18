#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int redLed = 13;
const int yellowLed = 12;
const int greenLed = 11;
const int soundPin = A0;

int threshold = 600;      
int redTime = 15;         
int yellowTime = 3;       
int greenTime = 15;       
int penaltyTime = 5;      

// LCD আপডেট করার ফাংশন 
void updateLCD(String status, int time) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Status: ");
  lcd.print(status);
  lcd.setCursor(0, 1);
  lcd.print("Time Left: ");
  lcd.print(time);
  lcd.print("s");
}

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(soundPin, INPUT);

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(2, 0);
  lcd.print("Sonic TRAFFIC");
  lcd.setCursor(4, 1);
  lcd.print("SYSTEM by Siad PGC");
  delay(2000);
}

void loop() {
  // green light 
  digitalWrite(greenLed, HIGH);
  for (int i = greenTime; i > 0; i--) {
    updateLCD("GO (Green)", i);
    delay(1000);
  }
  digitalWrite(greenLed, LOW);

  // yellow light 
  digitalWrite(yellowLed, HIGH);
  for (int i = yellowTime; i > 0; i--) {
    updateLCD("WAIT (Yellow)", i);
    delay(1000);
  }
  digitalWrite(yellowLed, LOW);

  // red light 
  digitalWrite(redLed, HIGH);
  int timeLeft = redTime;
  
  while (timeLeft > 0) {
    updateLCD("STOP (Red)", timeLeft);
    
    for (int ms = 0; ms < 10; ms++) {
      int noise = analogRead(soundPin);
      if (noise > threshold) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("NOISY! PENALTY");
        timeLeft += penaltyTime; 
        delay(1000); 
        break; 
      }
      delay(100); 
    }
    timeLeft--;
  }
  digitalWrite(redLed, LOW);
}