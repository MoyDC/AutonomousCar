// Función para serializar datos en un array de strings y enviarlos por Serial2
void enviarDatosUART2(String datos[], int numSensors) {
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