// Variables para el Timer 0
int LedToggleTimer0;
hw_timer_t *Timer0_Cfg = NULL;
#define INTERVALO_LED 250
volatile int ContEstadoLed = 0;

// Variables para el Timer 1
int LedToggleTimer1_LED1;
int LedToggleTimer1_LED2;
int LedToggleTimer1_LED3;
int LedToggleTimer1_LED4;
hw_timer_t *Timer1_Cfg = NULL; // Agregamos el puntero para el Timer 1
#define INTERVALO_LED_1 100 // Definimos un nuevo intervalo para el Timer 1
volatile int ContEstadoLed1 = 0; // Contador para el Timer 1


// Funciones
void IRAM_ATTR Timer0_ISR() {
  if (ContEstadoLed >= INTERVALO_LED) {
    digitalWrite(LedToggleTimer0, !digitalRead(LedToggleTimer0));
    ContEstadoLed = 0;
  } else {
    ContEstadoLed++;
  }
}

void IRAM_ATTR Timer1_ISR() {
  if (ContEstadoLed1 >= INTERVALO_LED_1) {
    digitalWrite(LedToggleTimer1_LED1, !digitalRead(LedToggleTimer1_LED1));
    digitalWrite(LedToggleTimer1_LED2, !digitalRead(LedToggleTimer1_LED2));
    digitalWrite(LedToggleTimer1_LED3, !digitalRead(LedToggleTimer1_LED3));
    digitalWrite(LedToggleTimer1_LED4, !digitalRead(LedToggleTimer1_LED4));
    ContEstadoLed1 = 0;
  } else {
    ContEstadoLed1++;
  }
}

// Inicialización del Timer 0
void initTimer0(int PinLed) {
  LedToggleTimer0 = PinLed;
  pinMode(LedToggleTimer0, OUTPUT);
  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 1000, true);
  timerAlarmEnable(Timer0_Cfg);
}

// Inicialización del Timer 1
void initTimer1(int PinLed1, int PinLed2, int PinLed3, int PinLed4) {
  LedToggleTimer1_LED1 = PinLed1;
  LedToggleTimer1_LED2 = PinLed2;
  LedToggleTimer1_LED3 = PinLed3;
  LedToggleTimer1_LED4 = PinLed4;
  pinMode(LedToggleTimer1_LED1, OUTPUT);
  pinMode(LedToggleTimer1_LED2, OUTPUT);
  pinMode(LedToggleTimer1_LED3, OUTPUT);
  pinMode(LedToggleTimer1_LED4, OUTPUT);
  Timer1_Cfg = timerBegin(1, 80, true); // Inicializamos el Timer 1 con ID 1
  timerAttachInterrupt(Timer1_Cfg, &Timer1_ISR, true);
  timerAlarmWrite(Timer1_Cfg, 1000, true);
  timerAlarmDisable(Timer1_Cfg);
}

// Función para activar o desactivar el Timer 1
void toggleTimer1(bool activate) {
  if (activate) {
    // Activar el Timer 1
    timerAlarmEnable(Timer1_Cfg);
  } else {
    // Desactivar el Timer 1
    timerAlarmDisable(Timer1_Cfg);
    digitalWrite(LedToggleTimer1_LED1, LOW);
    digitalWrite(LedToggleTimer1_LED2, LOW);
    digitalWrite(LedToggleTimer1_LED3, LOW);
    digitalWrite(LedToggleTimer1_LED4, LOW);
  }
}
