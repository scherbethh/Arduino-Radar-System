#include <Servo.h> 

const int trigPin = 13;
const int echoPin = 12;
const int Red = 2;
const int Green = 3; 
const int Buzzer = 4; // Buzzer pini

long duration;
int distance;
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Red, OUTPUT); // Kırmızı LED pinini çıkış olarak ayarlayın
  pinMode(Green, OUTPUT); // Yeşil LED pinini çıkış olarak ayarlayın
  pinMode(Buzzer, OUTPUT); // Buzzer pinini çıkış olarak ayarlayın
  Serial.begin(9600);
  myServo.attach(9);
}

void loop() {
  for (int i = 15; i <= 165; i++) {
    myServo.write(i); // Servo motoru hareket ettirme 
    delay(30);
    distance = calculateDistance();

   /* Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");*/

    if (distance <=10 ) { // Eğer mesafe 5 cm veya daha az ise
      redLed(); // LED durumunu ayarla

       Serial.print("UYARI,");
      Serial.print("Mesafe: ");
      Serial.print(distance);
      Serial.println(" cm");
      

      buzzerAlarm();  // Buzzer'ı sesi çıkar
    } else {
      // LED durumunu ayarla
      greenLed();
    }
  }

  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    
   /* Serial.print(i); // Servo açısı
    Serial.print(","); // diğer veri için belirteç
    Serial.print(distance); // Uzaklık verisi
    Serial.print("."); // verinin sonu belirteç*/

    if (distance <= 10) { // Eğer mesafe 5 cm veya daha az ise
      redLed();  // LED durumunu ayarla
      Serial.print("UYARI,");
      Serial.print("Mesafe: ");
      Serial.print(distance);
      Serial.println(" cm");
      buzzerAlarm(); // Buzzer'ı sesi çıkar
    } else {
      // LED durumunu ayarla
      greenLed();
    }
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void buzzerAlarm() {
  for (int j = 0; j < 3; j++) {
    digitalWrite(Buzzer, HIGH);
    delay(200); // Buzzer'ı 200 ms süreyle aktif et
    digitalWrite(Buzzer, LOW);
    delay(200); // 200 ms süreyle bekle
  }
}

void greenLed() {
  digitalWrite(Red, HIGH); 
  digitalWrite(Green, LOW); 
}

void redLed() {

  digitalWrite(Red, LOW); 
  digitalWrite(Green, HIGH);
   
}

/* ..



















































*/
