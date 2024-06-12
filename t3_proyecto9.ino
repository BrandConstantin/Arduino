#include <LiquidCrystal.h>      //Incluir la librería para la pantalla LCD.
//Configuración Pantalla LCD 16X2
LiquidCrystal screen (23,22,5,18,19,21);      //Screen: Nombre de nuestra pantalla.
byte pacman [ ] {      //Bytes para construir nuestro gráfico (PACMAN).
  B01110,      //Byte cuerpo Pacman.
  B11101,      //Byte cuerpo Pacman.    
  B11111,      //Byte cuerpo Pacman.
  B11110,      //Byte cuerpo Pacman.
  B11100,      //Byte cuerpo Pacman.
  B01110,      //Byte cuerpo Pacman.
  B11111,      //Byte cuerpo Pacman.
  B01110       //Byte cuerpo Pacman.
};      //Cierre de la estructura byte.

//Configuración Joystick
int x = 35;      //Posición en la tarjeta ESP32 del joystick en el eje "x".
int lectura_x = 0;      //La lectura se iguala a "0" puesto que en algun momento esta varía.
int y = 34;      //Posición en la tarjeta ESP32 del joystick en el eje "y".
int lectura_y = 0;      //La lectura se iguala a "0" puesto que en algun momento esta varía.

int posicion_x = 0;      //Posición en el eje "x" inicial del Pacman.
int posicion_y = 0;      //Posición en el eje "y" inicial del Pacman.

void setup() {      //Configuración de la tarjeta ESP32
  Serial.begin(115200);      //Velocidad viaje de datos (115200).
  screen.begin (16,2);      //Inicio de nuestra pantalla de tamaño 16x2.
  screen.createChar (0,pacman);      //Crear espacio de Pacman.
  screen.print ("Welcome to the Pac-Man Game");
  screen.clear ();      //Utilizamos este comando para limpiar nuestra pantalla.

  pinMode (x,INPUT);      //Configuración del joystick en "x" como entrada.
  pinMode (y,INPUT);      //Configuración del joystick en "y" como entrada.
  Serial.println ("Posición X ............ Posición Y");      //Resultados del joystick.
}      //Cierre void setup.

void loop() {      //Ejecución de las tareas
  Serial.print (lectura_x);      //Imprimir la lectura del joystick en el eje "x".
  Serial.print ("            ,         ");      //Visualización en forma de tabla.
  Serial.print (lectura_y);      //Imprimir la lectura del joystick en el eje "y".
  Serial.println ("       ");      //Forma y orden a la visualización de nuestra tabla.
  delay (1000);      //Tiempo designado para mostrar los nuevos resultados.

  //Configuración Pacman movimiento en el eje "x"
  lectura_x = analogRead (x);      //Valor joystick en el eje "x" en el pin "35" de la ESP32.
   if (lectura_x < 1000) {      //Condicional para posición en dicho eje.
        for (int i = 0; i < 15; i++) {      //Si cumple con la condición realizar dicho movimiento.
            if (posicion_x < 15 ) {      //Condicional para posición en dicho eje.
                posicion_x++; // Mover a la derecha
            }       //Cierre se la condición.
            screen.clear();      //Utilizamos este comando para limpiar nuestra pantalla.
            screen.setCursor(posicion_x, posicion_y);      //Indicamos la posición inicial de la pantalla.
            screen.write((byte)0);      //Llamamos a nuestra variable byte en lugar 0.
            delay(100);      //Tiempo para aparecer nuestro pacman.
        }      //Cierre del ciclo for.
    } else if (lectura_x > 1000) {      //Condicional para posición en dicho eje.
        for (int i = 0; i < 15; i++) {      //Si cumple con la condición realizar dicho movimiento.
            if (posicion_x > 0) {      //Condicional para posición en dicho eje.
                posicion_x--; // Mover a la izquierda
            }      //Cierre de la condición.
            screen.clear();      //Utilizamos este comando para limpiar nuestra pantalla.
            screen.setCursor(posicion_x, posicion_y);      //Indicamos la posición inicial de la pantalla.
            screen.write((byte)0);      //Llamamos a nuestra variable byte en lugar 0.
            delay(100);      //Tiempo para aparecer nuestro pacman.
        }      //Cierre del ciclo for.
    }      //Cierre de la condicional para posición en eje "x".

  //Configuración Pacman movimiento en el eje "y"
  lectura_y = analogRead(y);      //Valor del joystick en el eje "y" en el pin "34" de la ESP32.
    if (lectura_y < 700) {      //Condicional para posición en dicho eje.
        for (int i = 0; i < 1; i++) {      //Si cumple con la condición realizar dicho movimiento.
            if (posicion_y < 1) {      //Condicional para posición en dicho eje.
                posicion_y++; // Mover hacia abajo
            }      //Cierre de la condición.
            screen.clear();      //Utilizamos este comando para limpiar nuestra pantalla.
            screen.setCursor(posicion_x, posicion_y);      //Indicamos la posición inicial de la pantalla.
            screen.write((byte)0);      //Llamamos a nuestra variable byte en lugar 0.
            delay(100);      //Tiempo para aparecer nuestro pacman.
        }      //Cierre del ciclo for.
    } else if (lectura_y > 700) {      //Condicional para posición en dicho eje.
        for (int i = 0; i < 1; i++) {      //Si cumple con la condición realizar dicho movimiento.
            if (posicion_y > 0) {      //Condicional para posición en dicho eje.
                posicion_y--; // Mover hacia arriba
            }      //Ciere de la condición.
            screen.clear();      //Utilizamos este comando para limpiar nuestra pantalla.
            screen.setCursor(posicion_x, posicion_y);      //Indicamos la posición inicial de la pantalla.
            screen.write((byte)0);      //Llamamos a nuestra variable byte en lugar 0.
            delay(100);      //Tiempo para aparecer nuestro pacman.
            }      //Cierrre del ciclo for.
          }      //Ciere de la condición para el eje "y".
}      //Cierre del void loop.