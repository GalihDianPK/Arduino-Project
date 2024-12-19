#include <Servo.h>

Servo servoMotor;
int sensorHujan = A0;
int buttonPin = 4;
int stepperStepPin = 2;
int stepperDirPin = 3;
int led1 = 11;
int led2 = 12;
int led3 = 13;

int nilaiMinimalHujan = 500; 
bool sistemAktif = true;
unsigned long waktuSebelumnya = 0;
unsigned long waktuSetelahDikeluarkan = 0;
const unsigned long intervalPutar = 10000; 
const unsigned long delayAwalPutar = 5000; 

bool papanTerbuka = false; 
bool baruDikeluarkan = false; 

void setup() {
  pinMode(sensorHujan, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(stepperStepPin, OUTPUT);
  pinMode(stepperDirPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  servoMotor.attach(10);
  servoMotor.write(0); 

  Serial.begin(9600);
}

void loop() {
  int nilaiSensorHujan = analogRead(sensorHujan);
  bool tombolDitekan = digitalRead(buttonPin) == LOW;

  if (tombolDitekan) {
    sistemAktif = !sistemAktif;
    delay(300); 
    Serial.println(sistemAktif ? "Sistem diaktifkan." : "Sistem dinonaktifkan.");
  if (!sistemAktif && papanTerbuka) {
      Serial.println("Sistem dimatikan, menarik papan ke dalam...");
      digitalWrite(stepperDirPin, LOW); 
      gerakStepper(200);               
      papanTerbuka = false;            
    }
  }

  if (!sistemAktif) {
    digitalWrite(stepperStepPin, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    servoMotor.detach(); 
    return;
  } else {
    servoMotor.attach(10); 
  }

  if (nilaiSensorHujan > nilaiMinimalHujan) {
    if (papanTerbuka) {
      digitalWrite(stepperDirPin, LOW);
      gerakStepper(200);               
      papanTerbuka = false;            
      baruDikeluarkan = false;         
      Serial.println("Hujan terdeteksi, papan ditarik ke dalam.");
    }
    // Nyalakan LED saat hujan
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  } else {

    if (!papanTerbuka) {
      digitalWrite(stepperDirPin, HIGH); 
      gerakStepper(200);                
      papanTerbuka = true;              
      baruDikeluarkan = true;           
      waktuSetelahDikeluarkan = millis(); 
      Serial.println("Tidak hujan, papan didorong keluar.");
    }
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);

    unsigned long waktuSekarang = millis();
    if (papanTerbuka) {
      if (baruDikeluarkan && waktuSekarang - waktuSetelahDikeluarkan >= delayAwalPutar) {
        baruDikeluarkan = false; 
        waktuSebelumnya = waktuSekarang; 
        putarPapan();
      } else if (!baruDikeluarkan && waktuSekarang - waktuSebelumnya >= intervalPutar) {
        waktuSebelumnya = waktuSekarang;
        putarPapan();
      }
    }
  }

  delay(100);
}

void putarPapan() {
  Serial.println("Memutar papan untuk pengeringan merata.");
  servoMotor.write(180); 
  delay(2000);           
  servoMotor.write(0);   
  delay(2000);           
}

void gerakStepper(int langkah) {
  for (int i = 0; i < langkah; i++) {
    digitalWrite(stepperStepPin, HIGH);
    delayMicroseconds(1000); 
    digitalWrite(stepperStepPin, LOW);
    delayMicroseconds(1000);
  }
}
