//-----------------------------------------------------------------------------
//Class to read ultrasonic sensors using external interrupts
class UltrasonicSensor {
  private:
    int triggerPin;
    int echoPin;
    volatile unsigned long startCounting;
    volatile unsigned long stopCounting;
    volatile unsigned long duration;
    volatile float distance;
    volatile bool continuar;
    volatile bool InterrupcionEstado;

  public:
    // Constructor sin parámetros
    UltrasonicSensor() : triggerPin(-1), echoPin(-1) {
      continuar = true;
      InterrupcionEstado = false;
    }

    void SetPines(int trigger, int echo, void (*nameFuntion)(), int modeEchoPin = INPUT){
      triggerPin = trigger;
      echoPin = echo;
      pinMode(triggerPin, OUTPUT);
      pinMode(echoPin, modeEchoPin);
      attachInterrupt(digitalPinToInterrupt(echoPin), nameFuntion, CHANGE);
      continuar = true;
      InterrupcionEstado = false;
    }
    void SetStartCounting(volatile unsigned long _StartCounting_) { startCounting = _StartCounting_; }
    void SetStopCounting(volatile unsigned long _StopCounting_) { stopCounting = _StopCounting_; }
    void SetInterruption(volatile bool _InterrupcionEstado_) { InterrupcionEstado = _InterrupcionEstado_; }
    void SetContinuar(volatile bool _continuar_) { continuar = _continuar_; }
    volatile bool GetInterrupcionEstado() const { return InterrupcionEstado; }
    volatile bool GetContinuar() const { return continuar; }
    volatile float GetDuration() const { return duration; }
    volatile float GetDistance() const { return distance; }

    void Activar_Sensor(int _delaylectura_ = 5, unsigned long timeout = 1000000UL){
      //Recomendable usar esta funcion al inicio del loop principal
      if((micros() - startCounting) >= timeout){
        InterrupcionEstado = false;
        continuar = true;
      }
      if(InterrupcionEstado == false && continuar == true){
        continuar = false;
        delay(_delaylectura_); //5 valor ideal
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);
      }
    }

    void CalculateDuration(){
      duration = stopCounting - startCounting;
    }

    void CalculateDistance(){
      distance = (stopCounting - startCounting) / 58.2;
    }
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Class for ultrasonic sensors
/*class UltrasonicSensor {
  private:
    int triggerPin;
    int echoPin;
    unsigned long distanceParametro;
    unsigned long tiempoAuxParametro;

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
    // Método para establecer los pines del sensor
    void setParametros(int distance = 1000, int tiempoAux = 1000000) {
      distanceParametro = distance;
      tiempoAuxParametro = tiempoAux;
    }

    //Metodo para obtener distanceParametro
    int get_distanceParametro(){
      return distanceParametro;
    }

    //Metodo para obtener tiempoAuxParametro
    int get_tiempoAuxParametro(){
      return tiempoAuxParametro;
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
      float duration = pulseIn(echoPin, HIGH, tiempoAuxParametro); //tiempoAux por si quieres cambiar este parametro
      //Serial.println(duration);
      // Calcula la distancia en función de la duración del eco
      float distance = duration / 58.2; // Dividido por 2 porque el sonido viaja de ida y vuelta
      //Serial.println(distance);
      if(duration == 0){
        return distance = distanceParametro;
      }
      return distance;
    }
};//End class UltrasonicSensor*/
//-----------------------------------------------------------------------------