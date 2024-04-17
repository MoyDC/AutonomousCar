// Función para convertir una cadena serializada en un array de strings
void recibirDatosUART2(String datosSerializados, String datos[], int NUM_ELEMENTOS) {
  // Extraemos los elementos de la cadena serializada y los almacenamos en el array
  int i = 0;
  char* ptr = strtok((char*)datosSerializados.c_str(), ",");
  while (ptr != NULL && i < NUM_ELEMENTOS) {
    datos[i++] = String(ptr);
    ptr = strtok(NULL, ",");
  }
}//End void recibirDatosUART2(String datosSerializados, String datos[])