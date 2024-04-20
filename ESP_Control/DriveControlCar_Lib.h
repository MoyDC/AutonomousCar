//Class for the Control Car
class DriveControlCar {
  private:
    int tfDist, dato0, dato1, dato2, dato3, dato4;
    int limiteMinError = 5; //Liminte minimo error
    int limiteForwardActual;
    float factorTurnRight;
    float factorTurnLeft;
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

    //Metodo para obtener los datos
    void ReadData(int tf_Dist, String datos[]){
      tfDist = tf_Dist;
      dato0 = datos[0].toInt();
      dato1 = datos[1].toInt();
      dato2 = datos[2].toInt();
      dato3 = datos[3].toInt();
      dato4 = datos[4].toInt();
    }
    int Get_Data0(void){
      return dato0;
    }
    int Get_Data1(void){
      return dato1;
    }
    int Get_Data2(void){
      return dato2;
    }
    int Get_Data3(void){
      return dato3;
    }
    int Get_Data4(void){
      return dato4;
    }

    // Método para saber si hay error
    bool error() {
      if(tfDist<=limiteMinError and dato0<=limiteMinError and dato1<=limiteMinError and dato2<=limiteMinError and dato3<=limiteMinError and dato4<=limiteMinError){
        return true;
      }
      else{
        return false;
      }
    }

    //Metodo para avanzar hacia adelante
    bool Forward(){
      int limiteForward1 = 50;
      int limiteForward2 = 35;
      int limiteForward3 = 20;
      if(tfDist>=limiteForward1){
        limiteForwardActual = limiteForward1;
        return true;
      }
      else if(tfDist>=limiteForward2){
        limiteForwardActual = limiteForward2;
        return true;
      }
      else if(tfDist>=limiteForward3){
        limiteForwardActual = limiteForward3;
        return true;
      }
      else{
        return false;
      }
    }

    //Metodo para obtener limiteForward
    int get_limiteForwardActual(){
      return limiteForwardActual;
    }

    void Backward(){
      
    }

    //Metodo para girar hacia la derecha
    bool TurnRight(void){
      int dato;
      int limiteForward1 = 45;
      int limiteForward2 = 35;
      int limiteForward3 = 25;

      if(dato1 <= dato3){
        dato = dato1;
      }
      else{
        dato = dato3;
      }
      /*else if(dato3 <= limiteForward2){
        dato = dato3;
      }*/

      if(dato >= limiteForward1){// || dato3 >= limiteForward1){
        factorTurnRight = 1; // + Aux_TurnRight();
        return false;
      }
      else if(dato >= limiteForward2){// || dato3 >= limiteForward2){
        factorTurnRight = 1.3; // + Aux_TurnRight();
        return true;
      }
      else if(dato >= limiteForward3){// || dato3 >= limiteForward3){
        factorTurnRight = 1.6; // + Aux_TurnRight();
        return true;
      }
      else if(dato >= limiteMinError){// || dato3 >= limiteMinError){
        factorTurnRight = 2; // + Aux_TurnRight();
        return true;
      }
      else{
        factorTurnRight = 2;
        return true;
      }
    }//End bool TurnRight(void)

    //Metodo para obtener factorTurnRight
    float get_factorTurnRight(void){
      /*if(factorTurnRight >= 2){
        factorTurnRight = 2;
        return factorTurnRight;
      }
      else{
        return factorTurnRight;
      }*/
      return factorTurnRight;
    }//End float get_factorTurnRight(void)

    //Metodo para girar hacia la izquierda
    bool TurnLeft(void){
      int dato;
      int limiteForward1 = 45;
      int limiteForward2 = 35;
      int limiteForward3 = 25;

      if(dato0 <= dato2){
        dato = dato0;
      }
      else{
        dato = dato2;
      }
      
      /*if(dato0 <= limiteForward2){
        dato = dato0;
      }
      else if(dato2 <= limiteForward2){
        dato = dato2;
      }*/

      if(dato >= limiteForward1){// || dato2 >= limiteForward1){
        factorTurnLeft = 1; // - Aux_TurnLeft();
        return false;
      }
      else if(dato >= limiteForward2){// || dato2 >= limiteForward2){
        factorTurnLeft = 0.7; //  - Aux_TurnLeft();
        return true;
      }
      else if(dato >= limiteForward3){// || dato2 >= limiteForward3){
        factorTurnLeft = 0.4; //  - Aux_TurnLeft();
        return true;
      }
      else if(dato >= limiteMinError){// || dato2 >= limiteMinError){
        factorTurnLeft = 0; //  - Aux_TurnLeft();
        return true;
      }
      else{
        factorTurnLeft = 0;
        return true;
      }
    }//End bool TurnLeft(void)

    //Metodo para girar hacia la derecha con ayuda de otro dato/sensor
    float Aux_TurnLeft(void){
      int limiteForward1 = 40;
      int limiteForward2 = 25;
      int limiteForward3 = 15;

      if(dato2>=limiteForward1){
        return 0;
      }
      else if(dato2>=limiteForward2){
        return 0.2;
      }
      else if(dato2>=limiteForward3){
        return 0.3;
      }
      else if(dato2>=limiteMinError){
        return 0.4;
      }
      else{
        return 0.4;
      }
    }//End int Aux_TurnLeft(void)

    //Metodo para obtener factorTurnLeft
    float get_factorTurnLeft(){
      /*if(factorTurnLeft <= 0){
        factorTurnLeft = 0;
        return factorTurnLeft;
      }
      else{
        return factorTurnLeft;
      }*/
      return factorTurnLeft;
    }

    void Stop(){
      
    }
};//End class DriveControlCar