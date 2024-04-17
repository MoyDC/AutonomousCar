//ESP para leer los sensores
#include "ultrasonicSensor.h" //Libreria para los sensores ultrasonicos
#include "Pines.h"
#include "InterrupcionTimer0.h"
#include "DatosUart2.h"

//Variables 
const int numSensors = 5; // Define la cantidad de sensores que deseas crear
UltrasonicSensor sensors[numSensors]; // Declara un array de objetos UltrasonicSensor

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  initTimer0(LED_BUILTIN);
  Serial2.begin(9600);

  // Inicializa cada objeto UltrasonicSensor con los pines correspondientes
  sensors[0].setPins(TRIG1, ECHO1);
  sensors[1].setPins(TRIG2, ECHO2);
  sensors[2].setPins(TRIG3, ECHO3);
  sensors[3].setPins(TRIG4, ECHO4);
  sensors[4].setPins(TRIG5, ECHO5);
}//End setup
void loop()
{
  // Array de strings
  String datos[numSensors]; //Array de los datos de los sensores
  //sensors[0].readDistance();
  datos[0] = String(sensors[0].readDistance()); //cm
  datos[1] = String(sensors[1].readDistance()); //cm
  datos[2] = String(sensors[2].readDistance()); //cm
  datos[3] = String(sensors[3].readDistance()); //cm
  datos[4] = String(sensors[4].readDistance()); //cm

  //Se envian los datos por UART
  enviarDatosUART2(datos, numSensors);
}//End loop
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------