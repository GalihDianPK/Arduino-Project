int motorIN1 = 5;
int motorIN2 = 6;
int motorIN3 = 7;
int motorIN4 = 8;
int button = 11;
int infraRed = 2;
int infraRed2 = 3;

bool sistemAktif = false;

void setup() {
    Serial.begin(115200);
    pinMode(motorIN1, OUTPUT);
    pinMode(motorIN2, OUTPUT);
    pinMode(motorIN3, OUTPUT);
    pinMode(motorIN4, OUTPUT);
    pinMode(button, INPUT_PULLUP);
    pinMode(infraRed, INPUT);
    pinMode(infraRed2, INPUT);
}

void matikanSemua() {
    digitalWrite(motorIN1, LOW);
    digitalWrite(motorIN2, LOW);
    digitalWrite(motorIN3, LOW);
    digitalWrite(motorIN4, LOW);
}

void maju() {
    digitalWrite(motorIN1, HIGH);
    digitalWrite(motorIN2, LOW);
    digitalWrite(motorIN3, HIGH);
    digitalWrite(motorIN4, LOW);
}

void belokKanan () {
    digitalWrite(motorIN1, HIGH);
    digitalWrite(motorIN2, LOW);
    digitalWrite(motorIN3, LOW);
    digitalWrite(motorIN4, LOW);
}

void belokKiri() {
    digitalWrite(motorIN1, LOW);
    digitalWrite(motorIN2, LOW);
    digitalWrite(motorIN3, HIGH);
    digitalWrite(motorIN4, LOW);
}

void loop() {
    int sensorKiri = digitalRead(infraRed);
    int sensorKanan = digitalRead(infraRed2);

    if (digitalRead(button) == LOW) {
        sistemAktif = !sistemAktif;
        delay(300);

        if(!sistemAktif) {
            matikanSemua();
            Serial.println("mobil nonaktif");
        } else {
            Serial.println("mobil aktif");
        }

    }
    if (!sistemAktif){
        return;
    }

    if (sensorKiri == LOW && sensorKanan == LOW) {
            matikanSemua();
            Serial.println("mobil mati");
        } else if (sensorKiri == HIGH && sensorKanan == LOW) {
            belokKanan();
            Serial.println("mobil ke kanan");
        } else if (sensorKiri == LOW && sensorKanan == HIGH) {
            belokKiri();
            Serial.println("mobil ke kiri");
        } else {
            maju();
            Serial.println("mobil maju");
        }
}