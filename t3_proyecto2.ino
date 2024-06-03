void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT); // ESTABLECEMOS EL LED 13 COMO SALIDA
  pinMode(12, OUTPUT);
}

void loop() {
  // EL MODELO DE PLACA DEL FABRICANTE TIENE EL LED 2 INVERTIDO

  int primerEncendidoCorto = 3, encendidoLargo = 3;

  // 3 ENCENDIDOS CORTOS
  while(primerEncendidoCorto > 0){
    digitalWrite(13, LOW);
    delay(1000);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(12, LOW);
    delay(1000);
    digitalWrite(12, HIGH);
    delay(500);
    primerEncendidoCorto -= 1;
  }

  // 3 ENCENDIDOS LARGOS
  while(encendidoLargo > 0){
    digitalWrite(13, LOW);
    delay(3000);
    digitalWrite(13, HIGH);
    delay(500);
    encendidoLargo -= 1;
  }

  // 3 ENCENDISOS CORTOS
  primerEncendidoCorto = 3;
  while(primerEncendidoCorto > 0){
    digitalWrite(12, LOW);
    delay(1000);
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(1000);
    digitalWrite(13, HIGH);
    delay(3000);
    primerEncendidoCorto -= 1;
  }

}
