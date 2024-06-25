#include <WiFi.h>
#include <ESP32Servo.h>

Servo myservo;  // creamos un objeto servo para controlar un servo
// Se pueden crear doce objetos servo en la mayoría de las placas.

// GPIO al que está conectado el servo
static const int servoPin = 13;

// Reemplazamos con nuestras credenciales de red
const char* ssid     = "PLANTA_CERO";
const char* password = "Polodigital20";

// Establezca el número de puerto del servidor web en 80
WiFiServer server(80);

// Variable para almacenar la solicitud HTTP
String header;

// Decodificar el valor HTTP GET
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;

// Tiempo actual
unsigned long currentTime = millis();
// Momento anterior
unsigned long previousTime = 0; 
// Definir el tiempo de espera en milisegundos (ejemplo: 2000 ms = 2 s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  myservo.attach(servoPin);  // adjunta el servo en el servoPin al objeto servo

  // Conéctese a la red Wi-Fi con SSID y contraseña
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Imprima la dirección IP local e inicie el servidor web
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Escucha a los clientes entrantes

  if (client) {                             // Si un nuevo cliente se conecta,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // imprimir un mensaje en el puerto serie
    String currentLine = "";                // crear una cadena para contener los datos entrantes del cliente
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // Bucle mientras el cliente está conectado
      currentTime = millis();
      if (client.available()) {             // Si hay bytes para leer del cliente,
        char c = client.read();             // leer un byte, entonces
        Serial.write(c);                    // imprimirlo en el monitor serial
        header += c;
        if (c == '\n') {                    // si el byte es un carácter de nueva línea
          // Si la línea actual está en blanco, tienes dos caracteres de nueva línea seguidos.
          // ese es el final de la solicitud HTTP del cliente, así que envíe una respuesta:
          if (currentLine.length() == 0) {
            // Los encabezados HTTP siempre comienzan con un código de respuesta (por ejemplo, HTTP/1.1 200 OK)
            // y un tipo de contenido para que el cliente sepa lo que viene, luego una línea en blanco:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Mostrar la página web HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS para diseñar los botones de encendido/apagado 
            // Siéntete libre de cambiar los atributos de color de fondo y tamaño de fuente para adaptarlos a sus preferencias.
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println(".slider { width: 300px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
                     
            // Página web
            client.println("</head><body><h1>ESP32 with Servo</h1>");
            client.println("<p>Position: <span id=\"servoPos\"></span></p>");          
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\""+valueString+"\"/>");
            
            client.println("<script>var slider = document.getElementById(\"servoSlider\");");
            client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
            client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");
           
            client.println("</body></html>");     
            
            //GET /?value=180& HTTP/1.1
            if(header.indexOf("GET /?value=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);
              
              //Rotamos el servo
              myservo.write(valueString.toInt());
              Serial.println(valueString); 
            }         
            // La respuesta HTTP termina con otra línea en blanco
            client.println();
            // Salir del ciclo while
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // si tienes algo más que un carácter de retorno de carro,
          currentLine += c;      // agrégalo al final de la línea actual
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}