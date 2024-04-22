//ESP para leer los sensores
#include "ultrasonicSensor.h" //Libreria para los sensores ultrasonicos
#include "Pines.h"
#include "InterrupcionTimer0.h"
#include "DatosUart2.h"
//-----------------------------------------------------------------------------
//Variables 
const int numSensors = 5; // Define la cantidad de sensores que deseas crear
//String datos[numSensors]; //Array de los datos de los sensores
UltrasonicSensor sensors[numSensors]; // Declara un array de objetos UltrasonicSensor
const int MasDatos = 1; //agregar mas datos al momento de enviar por uart
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Objetos de Clase UltrasonicSensor 
/*UltrasonicSensor Sensor1;
UltrasonicSensor Sensor2;
UltrasonicSensor Sensor3;
UltrasonicSensor Sensor4;
UltrasonicSensor Sensor5;*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Funciones interrupciones externas
void IRAM_ATTR interruptionSensor0(){
  //Serial.println("Entre a la interrupcion");
  if(sensors[0].GetInterrupcionEstado() == false){ //Primer cambio Low a High 
    sensors[0].SetStartCounting(micros());
    sensors[0].SetInterruption(true);
  }
  else{ //Segundo cambio High a Low
    sensors[0].SetStopCounting(micros());
    sensors[0].SetInterruption(false);
    sensors[0].SetContinuar(true);
    sensors[0].CalculateDistance();
  }
}//End void IRAM_ATTR interruptionSensor0()
void IRAM_ATTR interruptionSensor1(){
  //Serial.println("Entre a la interrupcion");
  if(sensors[1].GetInterrupcionEstado() == false){ //Primer cambio Low a High 
    sensors[1].SetStartCounting(micros());
    sensors[1].SetInterruption(true);
  }
  else{ //Segundo cambio High a Low
    sensors[1].SetStopCounting(micros());
    sensors[1].SetInterruption(false);
    sensors[1].SetContinuar(true);
    sensors[1].CalculateDistance();
  }
}//End void IRAM_ATTR interruptionSensor1()
void IRAM_ATTR interruptionSensor2(){
  //Serial.println("Entre a la interrupcion");
  if(sensors[2].GetInterrupcionEstado() == false){ //Primer cambio Low a High 
    sensors[2].SetStartCounting(micros());
    sensors[2].SetInterruption(true);
  }
  else{ //Segundo cambio High a Low
    sensors[2].SetStopCounting(micros());
    sensors[2].SetInterruption(false);
    sensors[2].SetContinuar(true);
    sensors[2].CalculateDistance();
  }
}//End void IRAM_ATTR interruptionSensor2()
void IRAM_ATTR interruptionSensor3(){
  //Serial.println("Entre a la interrupcion");
  if(sensors[3].GetInterrupcionEstado() == false){ //Primer cambio Low a High 
    sensors[3].SetStartCounting(micros());
    sensors[3].SetInterruption(true);
  }
  else{ //Segundo cambio High a Low
    sensors[3].SetStopCounting(micros());
    sensors[3].SetInterruption(false);
    sensors[3].SetContinuar(true);
    sensors[3].CalculateDistance();
  }
}//End void IRAM_ATTR interruptionSensor3()
void IRAM_ATTR interruptionSensor4(){
  //Serial.println("Entre a la interrupcion");
  if(sensors[4].GetInterrupcionEstado() == false){ //Primer cambio Low a High 
    //Serial.println("Interrupcion Cambio 1");
    sensors[4].SetStartCounting(micros()); //startCounting = ;
    sensors[4].SetInterruption(true); //InterrupcionEstado = true;
  }
  else{ //Segundo cambio High a Low
    //Serial.println("Interrupcion Cambio 2");
    sensors[4].SetStopCounting(micros()); // = micros();
    sensors[4].SetInterruption(false); //InterrupcionEstado = false;
    sensors[4].SetContinuar(true); // = true;
    //duration = stopCounting - startCounting;
    //Sensor5.GetDuration();
    sensors[4].CalculateDistance();// = duration / 58.2; // Dividido por 2 porque el sonido viaja de ida y vuelta
    //Serial.println(duration5);
  }
}//End void IRAM_ATTR interruptionSensor4()
//-----------------------------------------------------------------------------
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
  sensors[0].SetPines(TRIG1, ECHO1, interruptionSensor0);
  sensors[1].SetPines(TRIG2, ECHO2, interruptionSensor1);
  sensors[2].SetPines(TRIG3, ECHO3, interruptionSensor2);
  sensors[3].SetPines(TRIG4, ECHO4, interruptionSensor3);
  sensors[4].SetPines(TRIG5, ECHO5, interruptionSensor4);

  /*sensors[0].setParametros(50, 5000);
  sensors[1].setParametros(50, 5000);
  sensors[2].setParametros(50, 5000);
  sensors[3].setParametros(50, 5000);
  sensors[4].setParametros(50, 5000);*/
  
}//End setup
void loop()
{
  // Array de enteros
  int* datos = leerDatos(5);; //Array de los datos de los sensores
  // Convertir los datos a strings
  String datosString[numSensors]; //+ MasDatos
  for (int i = 0; i < numSensors; i++) {
    datosString[i] = String(datos[i]);
  }
  //Se agrega el dato de distancia dada por el usuario
  //datosString[numSensors] = String(sensors[0].get_distanceParametro()); //deberia ser asi numSensors + MasDatos, pero
                                                                        //eso daria 6, y se ocupa la posicion 5 no 6
  //Se envian los datos
  enviarDatosUART2(datosString, numSensors); //+ MasDatos
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
    sensors[0].Activar_Sensor(4);
    sensors[1].Activar_Sensor(4);
    sensors[2].Activar_Sensor(4);
    sensors[3].Activar_Sensor(4);
    sensors[4].Activar_Sensor(4);
    //delay(10);//Delay para poder obtener la señal 
    Sensor1[i] = sensors[0].GetDistance();
    Sensor2[i] = sensors[1].GetDistance();
    Sensor3[i] = sensors[2].GetDistance();
    Sensor4[i] = sensors[3].GetDistance();
    Sensor5[i] = sensors[4].GetDistance();
  }

  DatoFiltrado[0] = filtrarDato_Promedio(Sensor1, NumDatos);
  DatoFiltrado[1] = filtrarDato_Promedio(Sensor2, NumDatos);
  DatoFiltrado[2] = filtrarDato_Promedio(Sensor3, NumDatos);
  DatoFiltrado[3] = filtrarDato_Promedio(Sensor4, NumDatos);
  DatoFiltrado[4] = filtrarDato_Promedio(Sensor5, NumDatos);

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


int filtrarDato_Promedio(int datos[], int longitud){
  int datoFiltrado = 0;

  //Serial.println(" ");
  for(int i=0; i<longitud; i++){
    //int distancia = dato.readDistance();
    datoFiltrado += datos[i];
    //Serial.println(String(i) + " - " + String(datoFiltrado) + " - " + String(distancia));
    //delay(5);
  }
  datoFiltrado /= longitud;
  //Serial.println(datoFiltrado);
  return datoFiltrado;
}