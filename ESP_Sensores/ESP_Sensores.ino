//ESP para leer los sensores


//Inputs

//OutPuts
#define LED_BUILTIN 2
#define ECHO1       32
#define TRIG1       33
#define ECHO2       25
#define TRIG2       26
#define ECHO3       23
#define TRIG3       22
#define ECHO4       27
#define TRIG4       14
#define ECHO5       12
#define TRIG5       13

//Variables 
const int numSensors = 5; // Define la cantidad de sensores que deseas crear

//--------------------------------------------------------------------------------
//Interrupcion Timer0
hw_timer_t *Timer0_Cfg = NULL;

#define INTERVALO_LED 250
volatile int ContEstadoLed = 0;

void IRAM_ATTR Timer0_ISR(){ 
  if(ContEstadoLed >= INTERVALO_LED){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    ContEstadoLed = 0;
  }
  else{
    ContEstadoLed++;
  }  
}//End void IRAM_ATTR Timer0_ISR()

void initTimer0(void){
  pinMode(LED_BUILTIN, OUTPUT);
  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 1000, true);
  timerAlarmEnable(Timer0_Cfg);
}//End void initTimer0(void)
//--------------------------------------------------------------------------------
// Función para serializar datos en un array de strings y enviarlos por Serial2
void enviarDatosUART2(String datos[]) {
  // Serializar los datos
  String datosSerializados;
  for (int i = 0; i < numSensors; i++) {
    datosSerializados += datos[i];
    datosSerializados += ","; 
  }
  // Enviar los datos serializados por Serial2
  Serial2.println(datosSerializados);
  Serial.println(datosSerializados);
}//End void enviarDatos(String datos[])
//--------------------------------------------------------------------------------
class UltrasonicSensor {
  private:
    int triggerPin;
    int echoPin;

  public:
    // Constructor
    UltrasonicSensor() {}

    // Método para establecer los pines del sensor
    void setPins(int TrigPin, int EchPin) {
      triggerPin = TrigPin;
      echoPin = EchPin;
      pinMode(triggerPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    // Método para leer la distancia
    float readDistance() {
      // Envía un pulso corto al pin de activación del sensor
      //digitalWrite(triggerPin, LOW);
      //delayMicroseconds(2);
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);
      //Serial.println(triggerPin);
      //Serial.println(echoPin);
      // Lee la duración del eco del pin de eco
      float duration = pulseIn(echoPin, HIGH);
      //Serial.println(duration);
      // Calcula la distancia en función de la duración del eco
      float distance = duration / 58.2; // Dividido por 2 porque el sonido viaja de ida y vuelta
      //Serial.println(distance);
      return distance;
    }
};
// Declara un array de objetos UltrasonicSensor
UltrasonicSensor sensors[numSensors];
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  initTimer0();
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

  enviarDatosUART2(datos);

  //delay(100);
}//End loop
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------