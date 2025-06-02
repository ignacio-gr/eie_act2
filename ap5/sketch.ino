#include <DHT.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- CONFIGURACIÓN DE PINES ---
#define DHTPIN 2           // Pin de datos del DHT
#define DHTTYPE DHT22      
#define LDR_PIN A0         // Pin analógico para el LDR
#define NUM_LEDS 8
#define LED_START_PIN 3
#define SERVO_PIN 9

// --- OBJETOS DE LIBRERÍAS ---
DHT dht(DHTPIN, DHTTYPE);
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- VARIABLES DE CONTROL ---
float tempDeseada = 25.0;
int zonaMuerta = 2;
int umbralLuz = 600; 

void setup() {
  Serial.begin(9600);
  dht.begin();
  servo.attach(SERVO_PIN);
  
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_START_PIN + i, OUTPUT);
  }

  lcd.setCursor(0, 0);
  lcd.print("Iniciando sistema");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();  // °C por defecto
  float humedad = dht.readHumidity();
  int ldrValor = analogRead(LDR_PIN);

  // Validar datos
  if (isnan(temp) || isnan(humedad)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error sensor DHT");
    delay(2000);
    return;
  }

  // --- CONTROL DE TEMPERATURA ---
  float limiteMax = tempDeseada + zonaMuerta;
  float limiteMin = tempDeseada - zonaMuerta;
  String accionTemp = "Estable  ";

  if (temp < limiteMin) {
    servo.write(0); 
    accionTemp = "Calentando";
  } else if (temp > limiteMax) {
    servo.write(180); 
    accionTemp = "Enfriando ";
  } else {
    servo.write(90); 
  }

  // --- CONTROL DE ILUMINACIÓN ---
  // El LDR devuelve más voltaje a más luz 
  int porcentajeLuz = map(ldrValor, 0, 1023, 0, 100); // 0-100%
  porcentajeLuz = constrain(porcentajeLuz, 0, 100);

  int ledsEncendidos = map(porcentajeLuz, 0, 100, NUM_LEDS, 0);
  ledsEncendidos = constrain(ledsEncendidos, 0, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_START_PIN + i, (i < ledsEncendidos) ? HIGH : LOW);
  }

  // --- VISUALIZACIÓN EN LCD ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C ");
  lcd.print(accionTemp);

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humedad, 0);
  lcd.print("% L:");
  lcd.print(porcentajeLuz);
  lcd.print("%");

  // --- MONITOR SERIE PARA DEBUG ---
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C | Humedad: ");
  Serial.print(humedad);
  Serial.print(" % | Luz: ");
  Serial.print(porcentajeLuz);
  Serial.println(" %");

  delay(2500);
}

