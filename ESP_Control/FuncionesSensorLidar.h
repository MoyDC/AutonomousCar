//Funcion para iniciar el sensor lidar
TFMPlus tfmP;  // Create a TFMini Plus object
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