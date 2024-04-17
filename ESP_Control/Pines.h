//Led Interrupciones
  #define LED_BUILTIN 2

//Sensor Lidar
  #define RX_LidarSensor 23
  #define TX_LidarSensor 19
  SoftwareSerial mySerial_LidarSensor(RX_LidarSensor, TX_LidarSensor); // Crea una instancia de SoftwareSerial

//UART0 - Serial
  #define RX0 3
  #define TX0 1

//UART2 - Serial2
  #define RX2 16
  #define TX2 17

//I2C - Wire - mini pantalla OLED
  #define SCL 22
  #define SCA 21

//Servoomotor Volante
  #define pinServoVolante 5
  Servo ServoVolante;

//Puente H - L298N 
  #define ENA 14
  #define IN1 27
  #define IN2 26




