//ESP para realizar el control
#include <TFMPlus.h>  // Include TFMini Plus Library v1.5.0
TFMPlus tfmP;         // Create a TFMini Plus object
#include <SoftwareSerial.h> 
#include <Wire.h>              // libreria para bus I2C
#include <Adafruit_GFX.h>      // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>  // libreria para controlador SSD1306

//Inputs

//OutPuts
#define LED_BUILTIN 2
#define RX_LidarSensor 23
#define TX_LidarSensor 19

//Variables 
#define NUM_ELEMENTOS 5
String datos[NUM_ELEMENTOS];  //Array para los datos
int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip

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
// Función para convertir una cadena serializada en un array de strings
void recibirDatosUART2(String datosSerializados, String datos[]) {
  // Extraemos los elementos de la cadena serializada y los almacenamos en el array
  int i = 0;
  char* ptr = strtok((char*)datosSerializados.c_str(), ",");
  while (ptr != NULL && i < NUM_ELEMENTOS) {
    datos[i++] = String(ptr);
    ptr = strtok(NULL, ",");
  }
}//End void recibirDatosUART2(String datosSerializados, String datos[])
//--------------------------------------------------------------------------------
// Crea una instancia de SoftwareSerial
SoftwareSerial mySerial_LidarSensor(RX_LidarSensor, TX_LidarSensor);
//Funcion para iniciar el sensor lidar
void initSensorLidar(void) {
  Serial.printf("\r\nTFMPlus Library Example\r\n");  // say 'hello'

  delay(20);               // Give port time to initalize
  tfmP.begin( &mySerial_LidarSensor);   // Initialize device library object and...
  // pass device serial port to the object.

  // Send some example commands to the TFMini-Plus
  // - - Perform a system reset - - - - - - - - - - -
  Serial.printf( "Soft reset: \n");
  if( tfmP.sendCommand( SOFT_RESET, 0))
  {
    Serial.printf( "passed.\r\n");
  }
  else tfmP.printReply();
  
  delay(500);  // added to allow the System Rest enough time to complete

  // - - Display the firmware version - - - - - - - - -
  Serial.printf( "Firmware version: ");
  if( tfmP.sendCommand( GET_FIRMWARE_VERSION, 0))
  {
    Serial.printf( "%1u.", tfmP.version[ 0]); // print three single numbers
    Serial.printf( "%1u.", tfmP.version[ 1]); // each separated by a dot
    Serial.printf( "%1u\r\n", tfmP.version[ 2]);
  }
  else tfmP.printReply();
  // - - Set the data frame-rate to 20Hz - - - - - - - -
  Serial.printf( "Data-Frame rate: ");
  if( tfmP.sendCommand( SET_FRAME_RATE, FRAME_20))
  {
    Serial.printf( "%2uHz.\r\n", FRAME_20);
  }
  else tfmP.printReply();
}//End initSensorLidar(void)
//--------------------------------------------------------------------------------
#define ANCHO 128  // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64    // reemplaza ocurrencia de ALTO por 64
#define OLED_RESET 4

// necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto

void DatosEquipo(void) {
  oled.clearDisplay();                  // limpia pantalla
  oled.setTextColor(WHITE);             // establece color al unico disponible (pantalla monocromo)
  oled.setTextSize(1);                  // establece tamano de texto en 1
  oled.setCursor(0, 0);                 // ubica cursor en origen de coordenadas 0,0
  oled.print("    IMTC - Equipo 4   ");  // escribe texto
  oled.setCursor(0, 10);
  oled.print("---------------------");
  oled.setCursor(0, 20);
  oled.print("      Distancias     ");
  oled.setCursor(0, 30);
  oled.print("Lidar:"+ String(tfDist)+" - S1:" + datos[0]);
  oled.setCursor(0, 40);
  oled.print("S2:" + datos[1] + " - S3:" + datos[2]);
  oled.setCursor(0, 50);
  oled.print("S4:" + datos[3] + " - S5:" + datos[4]);
  oled.display();  // muestra en pantalla todo lo establecido anteriormente
}  //Fin DatosEquipo(void)
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  initTimer0();
  Serial2.begin(9600);
  delay(20);

  Wire.begin(); // inicializa bus I2C
  Serial.println("OLED Init");
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // inicializa pantalla con direccion 0x3C
  DatosEquipo();

  Serial.println("LIDAR Init");
  mySerial_LidarSensor.begin(115200); // Inicializa el puerto UART
  initSensorLidar();
  
}
void loop()
{
  //Leer datos del sensor lidar
  tfmP.getData(tfDist, tfFlux, tfTemp);

  // Leer la cadena serializada
  String datosSerializados = Serial2.readStringUntil('\n');
  //Obtener los datos
  recibirDatosUART2(datosSerializados, datos);

  // Imprimir los datos
  Serial.println("Lidar: " + String(tfDist) + "cm, " + "UltraS1: " + datos[0] + "cm, " + "UltraS2: " + datos[1] + "cm, " + "UltraS3: " + datos[2] + "cm, " + "UltraS4: " + datos[3] + "cm, " + "UltraS5: " + datos[4] + "cm");

  DatosEquipo();
  // Esperar un momento
  delay(100);

  //dsvdsvsvsds
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
