//Class for the Control Car
class DriveControlCar {
  private:
    //int triggerPin;
    //int echoPin;

  public:
    // Constructor
    DriveControlCar() {}

    // Método para establecer los pines
    /*void setPins(int TrigPin, int EchPin) {
      triggerPin = TrigPin;
      echoPin = EchPin;
      pinMode(triggerPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }*/

    // Método para saber si hay error
    bool error(int tfDist, String datos[]) {
      int dato0, dato1, dato2, dato3, dato4, limite;
      limite = 10;
      dato0 = datos[0].toInt();
      dato1 = datos[1].toInt();
      dato2 = datos[2].toInt();
      dato3 = datos[3].toInt();
      dato4 = datos[3].toInt();
      if(tfDist<=limite and dato0<=limite and dato1<=limite and dato2<=limite and dato3<=limite and dato4<=limite){
        return true;
      }
      else{
        return false;
      }
    }
};//End class DriveControlCar