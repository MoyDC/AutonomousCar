//Class for ultrasonic sensors
class UltrasonicSensor {
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
};//End class UltrasonicSensor