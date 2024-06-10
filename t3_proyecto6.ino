const byte ledPins[] = {15, 2, 4}; //definir pines LED rojos, verdes y azules
//const byte chns[] = {0, 1, 2}; //definir los canales pwm
int red, green, blue;
void setup() {
for (int i = 0; i < 3; i++) { //configurar los canales pwm, 1KHz, 8bit
//ledcSetup(chns[i], 1000, 8);
ledcAttach(ledPins[i], 1000, 8);
}
}

void loop() {
red = random(0, 256);
green = random(0, 256);
blue = random(0, 256);
setColor(red, green, blue);
delay(1000);
}

void setColor(byte r, byte g, byte b) {
ledcWrite(ledPins[0], 255 - r); //LED de ánodo común, nivel bajo para encender el led.
ledcWrite(ledPins[1], 255 - g);
ledcWrite(ledPins[2], 255 - b);
}