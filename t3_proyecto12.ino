#include #include // Usamos la placa ESP32
//#include // Descomentamos esta línea en caso de usar la esp8266 y comentamos la línea de arriba
#include #include // Instalamos DHT library by adafruit


#define DHT_SENSOR_PIN 4
#define DHT_SENSOR_TYPE DHT11

//Proporciona la conexión y el tipo de sensor
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

//Proporciona la información del proceso de generación del token
#include "addons/TokenHelper.h"
//Proporciona información de impresión de carga útil RTDB
//y otras funciones auxiliares
#include "addons/RTDBHelper.h"

// Insertamos nuestras credenciales de acceso
#define WIFI_SSID "PLANTA_CERO"
#define WIFI_PASSWORD "Polodigital20"

// Insertamos Firebase project API Key
#define API_KEY "AIzaSyDMcuxo76wxoV_QtrhhcrLDZyQdV07XxLI"

// Insertamos la URL de nuestra base de datos
#define DATABASE_URL "https://est-meteo-1-default-rtdb.firebaseio.com"

#define PIN_LED 2
//Definimos el objeto de la Data para Firebase
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
//ya que estamos haciendo un inicio de sesión anónimo

void setup(){

dht_sensor.begin();
Serial.begin(115200);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("Connecting to Wi-Fi");
while (WiFi.status() != WL_CONNECTED){
Serial.print(".");
delay(300);
}
Serial.println();
Serial.print("Connected with IP: ");
Serial.println(WiFi.localIP());
Serial.println();

/* Asignamos la API_KEY (requerida) */
config.api_key = API_KEY;

/* Asignamos la RTDB URL (requerida) */
config.database_url = DATABASE_URL;

/* Nos logamos */
if (Firebase.signUp(&config, &auth, "", "")){
Serial.println("ok");
signupOK = true;
}
else{
Serial.printf("%s\n", config.signer.signupError.message.c_str());
}

/* Asignamos la función de devolución de llamada
para la tarea de generación de tokens de larga duración */
config.token_status_callback = tokenStatusCallback; //ver addons/TokenHelper.h

Firebase.begin(&config, &auth);
Firebase.reconnectWiFi(true);

// Config LED
pinMode(PIN_LED, OUTPUT);

}

void loop(){

/* La temperatura y la humedad medidas deben almacenarse en variables
para que el usuario pueda usarlo más tarde en la base de datos */

float temperature = dht_sensor.readTemperature();
float humidity = dht_sensor.readHumidity();

if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
// Para actualizar la data cada segundo
sendDataPrevMillis = millis();
// Ingresamos la temperatura en la tabla DHT_11
if (Firebase.RTDB.setInt(&fbdo, "DHT_11/Temperatura", temperature)){
/*Este comando se ejecutará incluso si no realiza una
impresión en serie, pero nos aseguraremos de que funcione */
Serial.print("Temperatura : ");
Serial.println(temperature);
}
else {
Serial.println("No se pudo leer del sensor");
Serial.println("MOTIVO: " + fbdo.errorReason());
}


// Ingresamos la humedad en la tabla DHT_11
if (Firebase.RTDB.setFloat(&fbdo, "DHT_11/Humedad", humidity)){
Serial.print("Humedad : ");
Serial.print(humidity);
Serial.print(" ");
}
else {
Serial.println("No se pudo leer del sensor");
Serial.println("MOTIVO: " + fbdo.errorReason());
}

// Indica que la Temp > 28 grados
if (temperature>28){
digitalWrite(PIN_LED,HIGH);
}else{
digitalWrite(PIN_LED,LOW);
}

}
}