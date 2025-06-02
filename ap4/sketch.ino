int valorLDR = 0;
byte i;

const int botonPin = 6;   // Pin donde está el botón
bool modoInvertido = false;  // Estado del modo (normal/invertido)

void setup() {
  // Configuramos los pines 8 a 12 como salida para los LEDs
  for(i = 8; i <= 12; i++) {
    pinMode(i, OUTPUT);
  }
  
  // Configuramos el pin del botón como entrada con pullup interno
  pinMode(botonPin, INPUT_PULLUP);

  analogReference(EXTERNAL);
}

void loop() {
  // Leer el botón (activa LOW cuando se presiona)
  if (digitalRead(botonPin) == LOW) {
    // Cambiar modo (cambiar estado de modoInvertido)
    modoInvertido = !modoInvertido;
    delay(300); // Anti-rebote y evitar múltiples cambios rápidos
  }

  valorLDR = analogRead(0);

  if (!modoInvertido) {
    // Modo NORMAL: más LEDs a medida que oscurece (valorLDR bajo)
    if(valorLDR >=1023) {
      for(i=8;i<=12;i++) {
        digitalWrite(i, LOW);
      }
    }
    else if(valorLDR >=823) {
      digitalWrite(8, HIGH);
      for(i=9;i<=12;i++) {
        digitalWrite(i, LOW);
      }
    }
    else if(valorLDR >=623) {
      for(i=8;i<=9;i++) {
        digitalWrite(i, HIGH);
      }
      for(i=10;i<=12;i++) {
        digitalWrite(i, LOW);
      }
    }
    else if(valorLDR >=423) {
      for(i=8;i<=10;i++) {
        digitalWrite(i, HIGH);
      }
      for(i=11;i<=12;i++) {
        digitalWrite(i, LOW);
      }
    }
    else if(valorLDR >=223) {
      for(i=8;i<=11;i++) {
        digitalWrite(i, HIGH);
      }
      digitalWrite(12, LOW);
    }
    else {
      for(i=8;i<=12;i++) {
        digitalWrite(i, HIGH);
      }
    }
  } else {
    // Modo INVERTIDO: más LEDs a medida que hay más luz (valorLDR alto)
    if(valorLDR >=1023) {
      for(i=8;i<=12;i++) {
        digitalWrite(i, HIGH);
      }
    }
    else if(valorLDR >=823) {
      digitalWrite(8, LOW);
      for(i=9;i<=12;i++) {
        digitalWrite(i, HIGH);
      }
    }
    else if(valorLDR >=623) {
      for(i=8;i<=9;i++) {
        digitalWrite(i, LOW);
      }
      for(i=10;i<=12;i++) {
        digitalWrite(i, HIGH);
      }
    }
    else if(valorLDR >=423) {
      for(i=8;i<=10;i++) {
        digitalWrite(i, LOW);
      }
      for(i=11;i<=12;i++) {
        digitalWrite(i, HIGH);
      }
    }
    else if(valorLDR >=223) {
      for(i=8;i<=11;i++) {
        digitalWrite(i, LOW);
      }
      digitalWrite(12, HIGH);
    }
    else {
      for(i=8;i<=12;i++) {
        digitalWrite(i, LOW);
      }
    }
  }
}
