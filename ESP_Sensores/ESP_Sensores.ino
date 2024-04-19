//ESP para leer los sensores
#include "ultrasonicSensor.h" //Libreria para los sensores ultrasonicos
#include "Pines.h"
#include "InterrupcionTimer0.h"
#include "DatosUart2.h"

//Variables 
const int numSensors = 5; // Define la cantidad de sensores que deseas crear
//String datos[numSensors]; //Array de los datos de los sensores
UltrasonicSensor sensors[numSensors]; // Declara un array de objetos UltrasonicSensor
const int MasDatos = 1; //agregar mas datos al momento de enviar por uart

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  initTimer0(LED_BUILTIN);
  Serial2.begin(9600);

  Serial.println("Init...");
  Serial.println("Init...");
  Serial.println("Init...");
  delay(1000);
  
  // Inicializa cada objeto UltrasonicSensor con los pines correspondientes
  sensors[0].setPins(TRIG1, ECHO1);
  sensors[1].setPins(TRIG2, ECHO2);
  sensors[2].setPins(TRIG3, ECHO3);
  sensors[3].setPins(TRIG4, ECHO4);
  sensors[4].setPins(TRIG5, ECHO5);

  sensors[0].setParametros(50, 5000);
  sensors[1].setParametros(50, 5000);
  sensors[2].setParametros(50, 5000);
  sensors[3].setParametros(50, 5000);
  sensors[4].setParametros(50, 5000);
  
}//End setup
void loop()
{
  // Array de enteros
  int* datos = leerDatos(5);; //Array de los datos de los sensores
  // Convertir los datos a strings
  String datosString[numSensors + MasDatos];
  for (int i = 0; i < numSensors; i++) {
    datosString[i] = String(datos[i]);
  }
  //Se agrega el dato de distancia dada por el usuario
  datosString[numSensors] = String(sensors[0].get_distanceParametro()); //deberia ser asi numSensors + MasDatos, pero
                                                                        //eso daria 6, y se ocupa la posicion 5 no 6
  //Se envian los datos
  enviarDatosUART2(datosString, numSensors + MasDatos);
}//End loop
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

int* leerDatos(int NumDatos){
  static int DatoFiltrado[numSensors];
  int Sensor1[NumDatos];
  int Sensor2[NumDatos];
  int Sensor3[NumDatos];
  int Sensor4[NumDatos];
  int Sensor5[NumDatos];

  for(int i=0; i<NumDatos; i++){
    Sensor1[i] = sensors[0].readDistance();
    Sensor2[i] = sensors[1].readDistance();
    Sensor3[i] = sensors[2].readDistance();
    Sensor4[i] = sensors[3].readDistance();
    Sensor5[i] = sensors[4].readDistance();
    delay(10);
  }

  DatoFiltrado[0] = calcularMediana(Sensor1, NumDatos);
  DatoFiltrado[1] = calcularMediana(Sensor2, NumDatos);
  DatoFiltrado[2] = calcularMediana(Sensor3, NumDatos);
  DatoFiltrado[3] = calcularMediana(Sensor4, NumDatos);
  DatoFiltrado[4] = calcularMediana(Sensor5, NumDatos);

  return DatoFiltrado;
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


int filtrarDatos(UltrasonicSensor dato){
  int datoFiltrado = 0;

  //Serial.println(" ");
  for(int i=0; i<5; i++){
    int distancia = dato.readDistance();
    datoFiltrado += distancia;
    //Serial.println(String(i) + " - " + String(datoFiltrado) + " - " + String(distancia));
    delay(5);
  }
  datoFiltrado /= 5;
  //Serial.println(datoFiltrado);
  return datoFiltrado;
}