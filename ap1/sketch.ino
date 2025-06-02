#include <Servo.h>
Servo myservo;

int potPin = A0;  
int val = 0;      

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
}

void loop() {
  val = analogRead(potPin);              // Lee el valor del potenciómetro
  int angle = map(val, 0, 1023, 0, 180); // Conversión a ángulos
  myservo.write(angle);                  // Movimiento del servo
  Serial.print("Potenciómetro: ");
  Serial.print(val);
  Serial.print(" → Ángulo: ");
  Serial.println(angle);
  delay(15);
}

