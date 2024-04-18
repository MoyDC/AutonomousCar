//Interrupcion Timer0

//Variables
int LedToggleTimer0;
hw_timer_t *Timer0_Cfg = NULL;
#define INTERVALO_LED 250
volatile int ContEstadoLed = 0;


//Funciones
void IRAM_ATTR Timer0_ISR(){ 
  if(ContEstadoLed >= INTERVALO_LED){
    digitalWrite(LedToggleTimer0, !digitalRead(LedToggleTimer0));
    ContEstadoLed = 0;
  }
  else{
    ContEstadoLed++;
  }  
}//End void IRAM_ATTR Timer0_ISR()
void initTimer0(int PinLed){
  LedToggleTimer0 = PinLed;
  pinMode(LedToggleTimer0, OUTPUT);
  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 1000, true);
  timerAlarmEnable(Timer0_Cfg);
}//End void initTimer0(void)