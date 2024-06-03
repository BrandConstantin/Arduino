void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT); // ESTABLECEMOS EL LED 2 COMO SALIDA
}

void loop() {
  // EL MODELO DE PLACA DEL FABRICANTE TIENE EL LED 2 INVERTIDO

  int primerEncendidoCorto = 3, encendidoLargo = 3;

  // 3 ENCENDIDOS CORTOS
  while(primerEncendidoCorto > 0){
    digitalWrite(2, LOW);
    delay(1000);
    digitalWrite(2, HIGH);
    delay(500);
    primerEncendidoCorto -= 1;
  }

  // 3 ENCENDIDOS LARGOS
  while(encendidoLargo > 0){
    digitalWrite(2, LOW);
    delay(3000);
    digitalWrite(2, HIGH);
    delay(500);
    encendidoLargo -= 1;
  }

  // 3 ENCENDISOS CORTOS
  primerEncendidoCorto = 3;
  while(primerEncendidoCorto > 0){
    digitalWrite(2, LOW);
    delay(1000);
    digitalWrite(2, HIGH);
    delay(3000);
    primerEncendidoCorto -= 1;
  }

}
