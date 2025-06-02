
# Actividad 2: Sistemas de control y actuación en función del clima

## 📌 Objetivo

Desarrollar una aplicación de medición, control, actuación y presentación del clima utilizando instrumentación programable. Esta práctica integra sensores, actuadores y una interfaz HMI local para mantener el sistema cercano a los valores deseados, basándose en lo aprendido en la Actividad 1.

## 🧪 Descripción de los desarollos

### 1: Aplicación de servomotor

- Se conecta un **servomotor** directamente al pin digital **D9** del Arduino.
- El servomotor tiene tres cables:
  - Marrón: conectado a **GND** (tierra).
  - Rojo: conectado a **5V** (alimentación).
  - Naranja: conectado a **D9** (señal PWM).
- Se utiliza un **potenciómetro** para controlar el ángulo del servo:
  - Un extremo conectado a **GND**.
  - El otro extremo a **5V**.
  - El pin central (wiper) conectado a la entrada analógica **A0**.
- El servo se mueve según se modifique el potenciómetro.
- Se emplea la biblioteca `Servo.h` para facilitar el control del servomotor.
- La alimentación del protoboard se realiza desde los pines **5V** y **GND** del Arduino.

### 2: Aplicación de control de 8 leds con 74HC595 

- Se utiliza el chip **74HC595** para controlar el encendido de **8 LEDs** mediante solo **3 pines digitales** del Arduino, optimizando el uso de pines.
- El chip actúa como un **registro de desplazamiento serie-paralelo**, permitiendo enviar datos en serie y controlar múltiples salidas en paralelo.
- Los LEDs están conectados en paralelo sobre la protoboard, cada uno con su **resistencia limitadora**.
- Se incluyen **LEDs de diferentes colores** (verde, rojo, amarillo, azul) para representar distintos niveles de iluminación.
- Un **sensor de luz (LDR)** detecta la cantidad de luz ambiental.
- A menor iluminación detectada, mayor cantidad de LEDs encendidos, simulando un sistema de iluminación automática.
- Se incluye un **botón pulsador** que puede utilizarse para activar o desactivar el sistema manualmente o cambiar entre modos de operación.
- Las conexiones se realizan entre los pines digitales del Arduino (2 al 13) y los pines del 74HC595, además de la alimentación (5V y GND) a la protoboard.

### 3: Aplicación de la medición con LDR para el control de iluminación con un led mediante una salida PWM 

- Se mide la luz ambiental mediante un **sensor LDR** conectado al pin **A0** del Arduino.
- Un **LED rojo** está conectado al pin **D13**, y su brillo se ajusta en función de la luz detectada.
- Se utiliza un **potenciómetro** para calibrar o ajustar el umbral de sensibilidad del sistema.
- El sistema invierte la escala de lectura: **a menor luz detectada, mayor brillo del LED**.
- El LED se controla mediante una señal **PWM** (modulación por ancho de pulso), lo que permite variar su intensidad de forma analógica.
- Las conexiones se realizan de la siguiente manera:
  - LDR y potenciómetro conectados a **A0**.
  - LED conectado a **D13** con resistencia limitadora.
  - Alimentación de 5V y GND desde el Arduino a la protoboard.
- Se ha añadido un servomotor que modifica el ángulo en función de la luminancia ambiental, como una placa solar móvil.

### 4: Control de 5 leds según el valor de un LSR

- Se implementa un sistema de iluminación progresiva que responde a los niveles de oscuridad del entorno.
- Se utilizan **cinco LEDs** conectados en paralelo, cada uno con su **resistencia limitadora**, distribuidos en la protoboard.
- Los LEDs se encienden de forma secuencial a medida que disminuye la luz ambiental, simulando un sistema de iluminación gradual.
- Se incluye un **botón pulsador** que puede utilizarse para activar o desactivar el sistema o cambiar entre modos de operación.
- El sistema puede incluir un **motor paso a paso** como actuador adicional, aunque su función específica no está detallada en esta etapa.
- Las conexiones se realizan entre los pines digitales del Arduino y los LEDs, el botón y el motor, además de la alimentación desde los pines **5V** y **GND**.
- Se utiliza un **LDR** (sensor de luz) y un **potenciómetro** para ajustar el umbral de sensibilidad a la luz.
- El código está diseñado para adaptarse automáticamente a diferentes condiciones de iluminación sin necesidad de modificarlo manualmente.

### 5: Sistema de control de temperatura, humedad y luz con LED y servomotor

- Se utiliza un sensor DHT22 para medir temperatura y humedad y un sensor LDR para medir la luz ambiental. 
- Un LED se enciende o apaga dependiendo de la cantidad de luz detectada: 
	-Si hay poca luz, el LED se enciende. 
	-Si hay mucha luz, el LED se apaga. 
- Un servomotor ajusta su ángulo en función de la temperatura: 
	-A mayor temperatura, mayor será el ángulo del servo, simulando, por ejemplo, una ventana automática que se abre más cuanto más calor hace. 
	-A menos de 23 ºC la ventana se cierra, servo a 0º, entre 23 y 27 ºC la ventana se queda a mitad, servo a 90º y a mas de 27º la venta se abre, servo a 180ºC
- La humedad se puede visualizar en el monitor serial para seguimiento ambiental. 
- Se conecta el DHT22 al pin digital D2, el LDR al pin A0, el LED al pin D13, y el servomotor al pin D9. 
- La lógica permite una integración básica de clima en aplicaciones como invernaderos automatizados o sistemas de ventilación inteligente.

## 🛠️ Componentes Utilizados

- Arduino UNO
- Servomotor
- Potenciómetro
- Sensor LDR
- LEDs
- Registro de desplazamiento 74HC595
- Resistencias (10kΩ, 1KΩ, 220Ω)
- Potenciómetro de 10KΩ

## 🖥️ Plataforma de Simulación

Este proyecto se ha desarrollado y probado en [Wokwi](https://wokwi.com/), una plataforma de simulación online para proyectos con Arduino.


## Links

- 1: https://wokwi.com/projects/432546479173943297

- 2: https://wokwi.com/projects/432569130732354561

- 3: https://wokwi.com/projects/432569183912989697

- 4: https://wokwi.com/projects/432569157736335361

- 5: https://wokwi.com/projects/432578269007972353
