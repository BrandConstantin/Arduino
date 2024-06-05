#define PIN_LED    2

#define PIN_BUTTON 13

// La función de configuración se ejecuta una vez cuando presiona restablecer o enciende la placa.

void setup() {

  // Inicializamos el pin digital PIN_LED como salida.

  pinMode(PIN_LED, OUTPUT);

  pinMode(PIN_BUTTON, INPUT);

}



// la función de bucle se ejecuta una y otra vez para siempre

void loop() {

  if (digitalRead(PIN_BUTTON) == LOW) {

    digitalWrite(PIN_LED,HIGH);

  }else{

    digitalWrite(PIN_LED,LOW);

  }

}