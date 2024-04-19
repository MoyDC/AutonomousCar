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
TaskHandle_t taskCore0; //Core 0 - Nucleo 0
#define NUM_ELEMENTOS 5
String datos[NUM_ELEMENTOS];  //Array para los datos
DriveControlCar Car;
int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
int contError = 0;
int ValMedioServo = 50;


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void setup(){
  Serial.begin(115200);
  initTimer0(LED_BUILTIN);
  Serial2.begin(9600);
  delay(20);

  //Core 0 - Nucleo 0
  xTaskCreatePinnedToCore(
    Loop2,   //Nombre del loop creado
    "Loop2",     //Nombre
    10000,        //Tama;o de la pila
    NULL,         //Parametro casi siempre Nulo
    1,            //Prioridad de la tarea
    &taskCore0,   //Nombre de la tarea
    0             //Nucleo donde se ejecutara
  );

  ServoVolante.attach(pinServoVolante);
  ServoVolante.write(ValMedioServo);

  Wire.begin(); // inicializa bus I2C
  Serial.println("OLED Init");
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // inicializa pantalla con direccion 0x3C
  DatosEquipo(tfDist, datos);

  Serial.println("LIDAR Init");
  mySerial_LidarSensor.begin(115200); // Inicializa el puerto UART
  initSensorLidar();
  
  initTimer1(LED1_FD, LED2_FI, LED3_AD, LED4_AI);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(ENA, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);


}
void loop(){
  //Reseteo de variables
  tfDist = 0;

  //Se leen los datos del sensor Lidar
  tfDist = FiltroDatosSensorLidar();

  // Imprimir los datos
  Serial.println("Lidar: " + String(tfDist) + "cm, " + "UltraS1: " + datos[0] + "cm, " + "UltraS2: " + datos[1] + "cm, " + "UltraS3: " + datos[2] + "cm, " + "UltraS4: " + datos[3] + "cm, " + "UltraS5: " + datos[4] + "cm");
  
  //Mostrar informacion en el OLED
  DatosEquipo(tfDist, datos);
  
  
  if(Car.error(tfDist, datos)){
    Serial.println("Los sensores marcan valores menores al rango minimo");

    //Se detiene los motores

    //Se detiene el servomotor
    ServoVolante.write(ValMedioServo);

    //Apagar y prender los leds
    toggleTimer1(true, true, true, true, true);
  }
  else{
    toggleTimer1(false);
  }
  //delay(5); //delay de lectura
  // Esperar un momento
  //delay(100);
  /*Serial.println("Servo 25");
  ServoVolante.write(25);    // Mover el servo a 0 grados
  delay(1000);         // Esperar 1 segundo
  Serial.println("Servo 50");
  ServoVolante.write(ValMedioServo);   // Mover el servo a 90 grados
  delay(1000);         // Esperar 1 segundo
  Serial.println("Servo 75");
  ServoVolante.write(75);  // Mover el servo a 180 grados
  delay(1000);
  Serial.println("Servo 50");
  ServoVolante.write(ValMedioServo);   // Mover el servo a 90 grados
  delay(1000);         // Esperar 1 segundo
  //dsvdsvsvsds


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
}//End loop
void Loop2(void *parameter){//Core 0 - Nucleo 0
  while(true){
    //Serial.println(" ");
    if(Serial2.available()){
      // Leer la cadena serializada
      String datosSerializados = Serial2.readStringUntil('\n');
      //Obtener los datos
      recibirDatosUART2(datosSerializados, datos, NUM_ELEMENTOS);
    }
    delay(20);
  }//End while(true)
  vTaskDelay(10); //Eviar advertencia de watchdog
}//Fin Loop2(void *parameter)

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
int FiltroDatosSensorLidar(void){
  int datos[5];
  for(int i=0; i<5; i++){
    //Leer datos del sensor lidar
    tfmP.getData(tfDist, tfFlux, tfTemp);
    datos[i] = tfDist;
    delay(10);
  }
  return calcularMediana(datos, 5);
}//End int FiltroDatosSensorLidar(void)

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
}//End int calcularMediana(int datos[], int longitud)
