void implement_switch_setup() {
  pinMode(NOTIFICATION_PIN, OUTPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  delay(100);
  
  #if NOTIFICATION_PIN_OFF_DEFAULT
    switchOff(NOTIFICATION_PIN);
  #else
    switchOff(NOTIFICATION_PIN);
  #endif

  #if ! IMPLEMENT_ROLLERSHUTER && ! IMPLEMENT_DOOROPENER
    switchOn(RELAY1);
    switchOn(RELAY2);
  #else
    switchOff(RELAY1);
    switchOff(RELAY2);
    notification(3,"Please write logic for roller shutter in implement_switch.h");
  #endif
};

void implement_switch_loop() {

};
