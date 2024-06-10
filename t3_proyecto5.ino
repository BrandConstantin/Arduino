#define PIN_LED 2 //definimos el led pin

#define CHN 0 //define el canal

#define FRQ 1000 //define la frecuencia

#define PWM_BIT 8 //define la precisión

void setup() {

ledcAttach(PIN_LED, FRQ, PWM_BIT); //establecemos el canal

//ledcAttachPin(PIN_LED, CHN); //conectamos el pin led al canal

}


void loop() {

for (int i = 0; i < 255; i++) { //hace que la luz se desvanezca

ledcWrite(PIN_LED, i);

delay(10);

}

for (int i = 255; i > -1; i--) { //hace que la luz se apague

ledcWrite(PIN_LED, i);

delay(10);

}

}