//ESP para realizar el control
#include <TFMPlus.h>  // Include TFMini Plus Library v1.5.0
#include <SoftwareSerial.h> 
#include <Wire.h>              // libreria para bus I2C
#include <Adafruit_GFX.h>      // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>  // libreria para controlador SSD1306
#include <ESP32Servo.h>
#include "InterrupcionTimer.h"
#include "Pines.h"
#include "DatosUart2.h"
#include "FuncionesOLED.h"
#include "FuncionesSensorLidar.h"
#include "DriveControlCar_Lib.h"

//Variables 
#define NUM_ELEMENTOS 5
String datos[NUM_ELEMENTOS];  //Array para los datos
DriveControlCar Car;
int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
int contError = 0;


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  initTimer0(LED_BUILTIN);
  Serial2.begin(9600);
  delay(20);



  ServoVolante.attach(pinServoVolante);
  ServoVolante.write(50);

  Wire.begin(); // inicializa bus I2C
  Serial.println("OLED Init");
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // inicializa pantalla con direccion 0x3C
  DatosEquipo(tfDist, datos);

  Serial.println("LIDAR Init");
  mySerial_LidarSensor.begin(115200); // Inicializa el puerto UART
  initSensorLidar();
  
  initTimer1(LED1_FD, LED2_FI, LED3_AD, LED4_AI);
  //initLEDs();

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(ENA, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);


}
void loop()
{
  //Reseteo de variables
  tfDist = 0;
  datos[0] = "0";
  datos[1] = "0";
  datos[2] = "0";
  datos[3] = "0";
  datos[4] = "0";

  //Leer dato sensor lidar
  tfDist = FiltroDatosSensorLidar();
  //delay(5); //delay de lectura

  // Leer la cadena serializada
  String datosSerializados = Serial2.readStringUntil('\n');
  //Obtener los datos
  recibirDatosUART2(datosSerializados, datos, NUM_ELEMENTOS);

  // Imprimir los datos
  Serial.println("Lidar: " + String(tfDist) + "cm, " + "UltraS1: " + datos[0] + "cm, " + "UltraS2: " + datos[1] + "cm, " + "UltraS3: " + datos[2] + "cm, " + "UltraS4: " + datos[3] + "cm, " + "UltraS5: " + datos[4] + "cm");

  DatosEquipo(tfDist, datos);

  if(Car.error(tfDist, datos)){
    Serial.println("Los sensores marcan valores menores al rango minimo");
    //contError = LEDsError(100, contError);
    toggleTimer1(true);
  }
  else{
    toggleTimer1(false);
  }
  // Esperar un momento
  //delay(100);
  Serial.println("Servo 25");
  ServoVolante.write(25);    // Mover el servo a 0 grados
  delay(1000);         // Esperar 1 segundo
  Serial.println("Servo 50");
  ServoVolante.write(50);   // Mover el servo a 90 grados
  delay(1000);         // Esperar 1 segundo
  Serial.println("Servo 75");
  ServoVolante.write(75);  // Mover el servo a 180 grados
  delay(1000);
  Serial.println("Servo 50");
  ServoVolante.write(50);   // Mover el servo a 90 grados
  delay(1000);         // Esperar 1 segundo
  //dsvdsvsvsds

/*
  // Gira hacia adelante durante 2 segundos
  Serial.println("Girando hacia adelante");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(ENA, HIGH);
  delay(5000);

  // Gira hacia atrás durante 2 segundos
  Serial.println("Girando hacia atrás");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(ENA, HIGH);
  delay(5000);

  // Se detiene durante 2 segundos
  Serial.println("Deteniendo motor");
  digitalWrite(ENA, LOW);
  delay(1000);*/
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
int FiltroDatosSensorLidar(void){
  int datos[5];
  for(int i=0; i<5; i++){
    //Leer datos del sensor lidar
    tfmP.getData(tfDist, tfFlux, tfTemp);
    datos[i] = tfDist;
    delay(5);
  }
  return calcularMediana(datos, 5);
}
// Función para calcular la mediana de un conjunto de datos enteros
int calcularMediana(int datos[], int longitud) {
  // Primero, ordenamos el conjunto de datos
  for (int i = 0; i < longitud - 1; i++) {
    for (int j = i + 1; j < longitud; j++) {
      if (datos[i] > datos[j]) {
        // Intercambiamos los valores si el elemento actual es mayor que el siguiente
        int temp = datos[i];
        datos[i] = datos[j];
        datos[j] = temp;
      }
    }
  }

  // Calculamos la mediana
  if (longitud % 2 == 0) {
    // Si hay un número par de elementos, la mediana es el promedio de los dos valores centrales
    return (datos[longitud / 2 - 1] + datos[longitud / 2]) / 2;
  } else {
    // Si hay un número impar de elementos, la mediana es el valor central
    return datos[longitud / 2];
  }
}
