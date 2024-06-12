/*-------Sensor de distancia ultrasónico-----*/
/*-- (usado para medir distancias entre objetos o superficies) --*/

int trigPin = 13;
int echoPin = 14;

//definir la velocidad del sonido en cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration; // Crea un valor de variable de tiempo
long duration_demo; // Simula el valor de la variable de tiempo anterior
float distanceCm; // Crea una variable de distancia
float distanceInch; // Crea un valor variable para convertir a pulgadas/pies



/*------------------- DHT 11 ---------------*/
#include <DHT.h>

#define DHTPIN 2 // Entrada conectada al cable SDA, posición D2.
#define DHTTYPE DHT11 // DHT11 (AM2302) tipo de sensor

float temperature_demo = 0; // Es una réplica de los datos anteriores
float humidity_demo = 0; // Es una réplica de los datos anteriores.

DHT dht(DHTPIN, DHTTYPE); // Establecer como función (Entrada, Tipo)


/*------------------- LCD 16x2 (I2C) ---------------*/
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);// LiquidCrystal_I2C lcd(addressid , colums ,rows)  
// (no estoy seguro) puedes verte obligado a utilizar SCL ext. 22 SDA ext. 21, de lo contrario no se encontrará el dispositivo. 0x27,16,2 es el valor predeterminado.


void setup() {

  Serial.begin(115200);

    /*-------Sensor de distancia ultrasónico-----*/
      pinMode(trigPin, OUTPUT); // Establece el trigPin como una salida
      pinMode(echoPin, INPUT); // Establece el echoPin como una entrada

      digitalWrite(trigPin, LOW); // Establecemos LOW por defecto
    /*---------------------------------------*/

    /*------------------- DHT 11 ---------------*/
      dht.begin();
    /*-------------------------------------------*/


}

void loop() {

  /*-------Sensor de distancia ultrasónico-----*/
    digitalWrite(trigPin, HIGH); // importante

    if(digitalRead(trigPin) == HIGH){
     
      digitalWrite(trigPin, LOW); // Cerrado para medir el tiempo de impacto
      //delayMicroseconds(2);

      duration = pulseIn(echoPin, HIGH); // Importante//Reflejo de la medición de la duración del sonido
      distanceCm = duration * SOUND_SPEED/2; // Calcular la distancia a la que se puede escuchar un sonido
      distanceInch = distanceCm * CM_TO_INCH; // Calcular pulgadas/pies

      /*Serial.print("Duración de tiempo (--): ");
      Serial.println(duración);
      Serial.print("Distancia (cm): ");
      Serial.println(distanciaCM);
      Serial.print("Distancia (inch): ");
      Serial.println(distanciaINCH);
      delayMicroseconds(10); // importante ----> delay 10 mseg*/

      /*------------------- DHT 11 ---------------*/

        float temperature = dht.readTemperature(); // Lee temperatura en el dispositivo
        float humidity = dht.readHumidity(); // Lee humedad en el dispositivo

        /*Serial.print("Temperatura: ");
        Serial.print(temperatura);
        Serial.print(" °C\t");
        Serial.print("Humedad: ");
        Serial.print(humedad);
        Serial.println(" %");*/
      /*-------------------------------------------*/


      /*-------------------------------- Función para comprobar que hay valores de movimiento para mostrar. ----------------------------------------*/

      /*---------------------------------- LCD 16x2 (I2C) --------------------------------*/
        lcd.init(); // Seleccione el valor desde el principio como funtion()
        lcd.backlight();// fondo brillante        
      /*------------------- LCD 16x2 (I2C) Mostramos sensor de distancia ultrasónico---------------*/
      if(duration != duration_demo){
        lcd.clear();
        lcd.setCursor(2,0); // Establecer carácter de posición en la pantalla LCD
        lcd.print("Distance (cm):");
        lcd.setCursor(5,1);   // Establecer carácter de posición en la pantalla LCD
        lcd.print(distanceCm);
        delay(2000);

        lcd.clear();
        lcd.setCursor(0,0);   // Establecer carácter de posición en la pantalla LCD
        lcd.print("Distance (inch):");
        lcd.setCursor(5,1);   // Establecer carácter de posición en la pantalla LCD
        lcd.print(distanceInch);
        delay(2000);
        duration_demo = duration;
      }
      /*--------------------------------------------------------------------------------*/
      if(temperature != temperature_demo){
      /*----------------------------- LCD 16x2 (I2C) Mostramos_DHT 11 -----------------------*/
        lcd.clear();
        lcd.setCursor(2,0);   // Establecer letras de posición en la pantalla LCD
        lcd.print("Temperature ");
        lcd.setCursor(3,1);   // Establecer letras de posición en la pantalla LCD
        lcd.print(temperature);
        lcd.setCursor(7,1);   // Establecer letras de posición en la pantalla LCD
        lcd.print(" °C\t");
        temperature_demo = temperature;
        delay(2000);
      }
      if(humidity != humidity_demo){
        lcd.clear();
        lcd.setCursor(4,0);   // Establecer letras de posición en la pantalla LCD
        lcd.print("Humidity: ");
        lcd.setCursor(5,1);   // Establecer letras de posición en la pantalla LCD
        lcd.print(humidity);
        lcd.setCursor(9,1);   // Establecer letras de posición en la pantalla LCD
        lcd.print(" %");
        humidity_demo = humidity;
        delay(2000);
      /*-------------------------------------------------------------------------------*/
      }
   
    }
   

  /*---------------------------------------*/


 
  delay(1000);
}