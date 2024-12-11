#include <LiquidCrystal_I2C.h> // led display
const int col = 16;
const int row = 2;
LiquidCrystal_I2C lcd(0x27, col, row);

int sensorPin = A0;
int buzzer = 7;
int ledGreen = 8;
int ledRed = 9;

int button = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(sensorPin, INPUT);
  lcd.init();
  lcd.backlight();
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(button);
  int nilaiSensor = analogRead(sensorPin);
  Serial.println(nilaiSensor);
  delay(1000);

  if (nilaiSensor <= 800){
    for (int i = 0; i < 3; i++) {
      tone(buzzer, 1000);
      digitalWrite(ledRed, HIGH);
      delay(500); 
      noTone(buzzer);
      digitalWrite(ledRed, LOW);
      delay(500); 
      digitalWrite(ledGreen, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Kondisi Cuaca: ");
      lcd.setCursor(0, 1);
      lcd.print("Hujan");
    }
  }
  else{
    noTone(buzzer);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Kondisi Cuaca: ");
    lcd.setCursor(0, 1);
    lcd.print("Tidak Hujan");
  }
}
