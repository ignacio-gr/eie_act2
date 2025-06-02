// Autor: Noelia de la Plaza Lafuente
// Máster en Ingeniería de Telecomunicaciones – UNIR
// Asignatura: Equipos e Instrumentación Electrónica

//DEFINICIÓN DE PINES 
// Pines de control para el registro de desplazamiento 74HC595
const int latchPin = 11;   // ST_CP - Latch: activa la salida
const int clockPin = 9;    // SH_CP - Reloj: desplaza los bits internamente
const int dataPin  = 12;   // DS - Datos en serie a enviar

// Pin digital para el botón de cambio de modo
const int botonPin = 7;

//VARIABLES GLOBALES

bool estadoBotonAnterior = HIGH;  // Guarda el estado anterior del botón (pull-up = HIGH)
byte leds = 0;                    // Byte que representa el patrón de encendido de LEDs (Q0-Q7)
int modo = 0;                     // Variable de estado: 0 = secuencial, 1 = modo navidad

// CONFIGURACIÓN INICIAL 

void setup() {
  // Configurar los pines del 74HC595 como salidas digitales
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  // Configurar el pin del botón con resistencia pull-up interna
  pinMode(botonPin, INPUT_PULLUP);

  // Inicializar el estado del registro apagando todos los LEDs
  updateShiftRegister();
}

//  BUCLE PRINCIPAL

void loop() {
  // Lectura actual del estado del botón (LOW = pulsado)
  bool estadoBoton = digitalRead(botonPin);

  // Detectar flanco de bajada: cambio de HIGH a LOW
  if (estadoBoton == LOW && estadoBotonAnterior == HIGH) {
    modo = !modo;  // Cambia entre modo 0 y modo 1 (conmuta)
    delay(200);    // Debounce simple para evitar múltiples cambios por rebote
  }

  // Actualizar el estado anterior del botón para la próxima lectura
  estadoBotonAnterior = estadoBoton;

  // MODO 0: Secuencial izquierda a derecha
  if (modo == 0) {
    for (int i = 0; i < 8; i++) {
      leds = 0;              // Apagar todos los LEDs
      bitSet(leds, i);       // Encender solo el LED en posición i (Q0 a Q7)
      updateShiftRegister(); // Actualizar las salidas del 74HC595
      delay(300);            // Espera para visualización
    }
  }

  // MODO 1: "Navidad" – Encendido en pares alternos 
  else {
    for (int i = 0; i < 4; i++) {
      leds = 0;                        // Apagar todos
      bitSet(leds, i * 2);             // Encender LED par (Q0, Q2, Q4, Q6)
      bitSet(leds, (i * 2) + 1);       // Encender siguiente (Q1, Q3, Q5, Q7)
      updateShiftRegister();          // Reflejar patrón en los LEDs
      delay(300);
    }
  }
}

// FUNCIÓN PARA ACTUALIZAR LOS LEDs 

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);                        // Desactiva latch para cargar datos
  shiftOut(dataPin, clockPin, LSBFIRST, leds);        // Envía el byte por desplazamiento
  digitalWrite(latchPin, HIGH);                       // Activa latch para mostrar el patrón
}
