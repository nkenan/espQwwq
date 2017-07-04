#if IMPLEMENT_DOOROPENER
  int doorOpenerDelay = 3000;
#endif

#if IMPLEMENT_ROLLERSHUTTER
  int rollerShutterDelay = 20000;
#endif



bool espInformation() {
  Serial.begin(115200);
  Serial.print("ESP.getChipId(): ");
  Serial.println(ESP.getChipId());
  Serial.print("ESP.getResetReason(): ");
  Serial.println(ESP.getResetReason());
  Serial.print("ESP.getFreeHeap(): ");
  Serial.println(ESP.getFreeHeap());
  Serial.print("ESP.getCoreVersion(): ");
  Serial.println(ESP.getCoreVersion());
  Serial.print("ESP.getSdkVersion(): ");
  Serial.println(ESP.getSdkVersion());
  Serial.print("ESP.getCpuFreqMHz(): ");
  Serial.println(ESP.getCpuFreqMHz());
  Serial.print("ESP.getSketchSize(): ");
  Serial.println(ESP.getSketchSize());
  Serial.print("ESP.getFreeSketchSpace(): ");
  Serial.println(ESP.getFreeSketchSpace());
  Serial.print("ESP.getSketchMD5(): ");
  Serial.println(ESP.getSketchMD5());
  Serial.print("ESP.getFlashChipId(): ");
  Serial.println(ESP.getFlashChipId());
  Serial.print("ESP.getFlashChipSize(): ");
  Serial.println(ESP.getFlashChipSize());
  Serial.print("ESP.getFlashChipRealSize(): ");
  Serial.println(ESP.getFlashChipRealSize());
  Serial.print("ESP.getFlashChipSpeed(): ");
  Serial.println(ESP.getFlashChipSpeed());
  Serial.print("ESP.getCycleCount(): ");
  Serial.println(ESP.getCycleCount());
  Serial.print("ESP.getVcc(): ");
  Serial.println(ESP.getVcc());
};
bool toggle(int pin, int count, int delayMilliSeconds) {
  if (!pin) pin = RELAY1;
  if (!count) count = 1;
  if (!delayMilliSeconds) delayMilliSeconds = 30;
  for (int i=0; i<count; i++) {
      bool tmp = digitalRead(pin) ? 0 : 1;
      digitalWrite(pin, tmp);
      delay(delayMilliSeconds);
  }
  return true;
};

bool switchOn(int pin) {
  if (!pin) return false;

  if (pin == NOTIFICATION_PIN && NOTIFICATION_PIN_INVERTED || pin == RELAY1 && RELAY1_INVERTED || pin == RELAY2 && RELAY2_INVERTED) {
    digitalWrite(pin,LOW);
    #if IMPLEMENT_DOOROPENER
      delay(doorOpenerDelay);
      digitalWrite(pin,HIGH);
    #endif
    #if IMPLEMENT_ROLLERSHUTER
      delay(rollerShutterDelay);
      digitalWrite(pin,HIGH);
    #endif
    
  } else {
    digitalWrite(pin,HIGH);
    #if IMPLEMENT_DOOROPENER
      delay(doorOpenerDelay);
      digitalWrite(pin,LOW);
    #endif
    #if IMPLEMENT_ROLLERSHUTER
      delay(rollerShutterDelay);
      digitalWrite(pin,LOW);
    #endif
  };
  return true;
};

bool switchOff(int pin) {
  if (!pin) return false;

  if (pin == NOTIFICATION_PIN && NOTIFICATION_PIN_INVERTED || pin == RELAY1 && RELAY1_INVERTED || pin == RELAY2 && RELAY2_INVERTED) {
    digitalWrite(pin,HIGH);
  } else {
    digitalWrite(pin,LOW);
  };
  return true;
};

bool notification(int level, String notificationMessage) {
  if (level == 0) { //success messages
    toggle(NOTIFICATION_PIN, 16, 100);
    if (debug) Serial.println(notificationMessage);
    return true;
  } else if (level == 1) { //error messages
    //
    toggle(NOTIFICATION_PIN, 4, 400);
    if (debug) Serial.println(notificationMessage);
    return true;
  } else {
    if (debug) Serial.println(notificationMessage);
    return false;
  };
};
