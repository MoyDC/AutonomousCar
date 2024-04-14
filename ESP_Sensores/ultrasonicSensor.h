//Class for ultrasonic sensors
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
};//End class UltrasonicSensor