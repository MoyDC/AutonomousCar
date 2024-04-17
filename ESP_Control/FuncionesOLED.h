#define ANCHO 128  // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64    // reemplaza ocurrencia de ALTO por 64
#define OLED_RESET 4

// necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto

void DatosEquipo(int tfDist, String datos[]) {
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