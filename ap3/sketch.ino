#include <Servo.h>
// Autor: Noelia de la Plaza Lafuente
// Máster en Ingeniería de Telecomunicaciones – UNIR
// Asignatura: Equipos e Instrumentación Electrónica

//DEFINICIÓN DE VARIABLES 

int valorcds;
int brilloLED;
Servo miServo;

void setup() {
  Serial.begin(9600);
  miServo.attach(9);  // Conectar el servo al pin 9 (puedes cambiarlo si quieres)
  pinMode(5, OUTPUT);
}

void loop() {
  valorcds = analogRead(A0);
  Serial.println(valorcds);
  
  valorcds = 1023 - valorcds;  // Invertimos la lectura para que el valor sea mayor cuando hay menos luz
  brilloLED = map(valorcds, 0, 1023, 0, 255);
  
  analogWrite(5, brilloLED);  // Ajustamos brillo del LED en el pin 5
  
  // Mapear el valor del LDR para controlar el servo de 0 a 180 grados
  int anguloServo = map(valorcds, 0, 1023, 0, 180);
  miServo.write(anguloServo);  // Mover el servo al ángulo calculado

  delay(100);
}
