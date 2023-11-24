#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  
const int potPin = 35;
const int greenLedPin = 13;
const int redLedPin = 12;
const int buzzerPin = 32;

const int limiteInferior = 60;
const int limiteSuperior = 100;

void setup() {
  Wire.begin(21, 22);  
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Batimentos:");

  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);
  tone(buzzerPin, 1000);  
  delay(1000);  
  noTone(buzzerPin);  
}

void loop() {
  lcd.clear();

  int potValue = analogRead(potPin);

  int batimentosCardiacos = map(potValue, 0, 4095, 40, 160);

  lcd.setCursor(0, 1);
  lcd.print(batimentosCardiacos);
  lcd.print(" BPM     ");

  if (batimentosCardiacos < limiteInferior || batimentosCardiacos > limiteSuperior) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    tone(buzzerPin, 1000); 

    if (batimentosCardiacos < limiteInferior) {
      lcd.setCursor(0, 0);
      lcd.print("BPM BAIXO");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("BPM ALTO");
    }
  } else {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    noTone(buzzerPin);

    lcd.setCursor(0, 0);
    lcd.print("BPM SAUDAVEL");
  }

  delay(1000);
}
