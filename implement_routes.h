server.onNotFound(handleNotFound);

// ###### MAIN
server.on("/", [](){
  delay(200);
  server.send(200, "text/plain", "Hier steht nichts.");
});

server.on("/restart", [](){
  delay(200);
  server.send(200, "text/plain", "");
  delay(200);
  ESP.restart();
});

// ###### API
server.on("/api", [](){
  refreshApi();
  delay(200);
  server.send(200, "application/json", json);
});

// ###### WIFI
server.on("/wifi/ap", [](){
  server.send(200, "text/plain", "[WIFI] Setting AP mode");
  wifiHandle("ap");
});

server.on("/wifi/apSta", [](){
  server.send(200, "text/plain", "[WIFI] Setting AP_STA mode");
  wifiHandle("apSta");
});

server.on("/wifi/client", [](){
  server.send(200, "text/plain", "[WIFI] Setting client mode");
  wifiHandle("client");
});

server.on("/wifi/off", [](){
  server.send(200, "text/plain", "[WIFI] Switching of wifi");
  wifiHandle("off");
});

server.on("/wifi/rssiNotification", [](){
  server.send(200, "text/plain", String(WiFi.RSSI()));
  double rssi;
  int delayTime;
  for (int i = 0; i < 31; i++) { // even numer for switching properly led.
    rssi = WiFi.RSSI();
    delayTime = 5000 / (int(rssi)+100);
    toggle(NOTIFICATION_PIN,1,delayTime);
  };
});

// ###### NOTIFICATIONS
server.on("/notification/on", [](){
  switchOff(NOTIFICATION_PIN);
  delay(200);
  server.send(200, "text/plain", "");
});

server.on("/notification/off", [](){
  switchOn(NOTIFICATION_PIN);
  delay(200);
  server.send(200, "text/plain", "");
});

server.on("/notification/toggle", [](){
  toggle(NOTIFICATION_PIN, 1, 0);
  delay(200);
  server.send(200, "text/plain", "");
});

server.on("/notification/pattern/0", [](){
  notification(0, "[NOTIFICATION] Pattern 0");
  delay(200);
  server.send(200, "text/plain", "[NOTIFICATION] Pattern 0");
});

server.on("/notification/pattern/1", [](){
  notification(1, "[NOTIFICATION] Pattern 1");
  delay(200);
  server.send(200, "text/plain", "[NOTIFICATION] Pattern 1");
});

server.on("/notification/pattern/2", [](){
  notification(2, "[NOTIFICATION] Pattern 2");
  delay(200);
  server.send(200, "text/plain", "[NOTIFICATION] Pattern 2");
});

// ###### TEMPERATURE AND HUMIDITY
#if IMPLEMENT_DHT
server.on("/temperature", [](){
  delay(200);
  server.send(200, "text/plain", temperature);
});

server.on("/humidity", [](){
  delay(200);
  server.send(200, "text/plain", humidity);
});
#endif

// ###### SWITCHING RELAYS
#if IMPLEMENT_SWITCH
server.on("/relay/1/on", [](){
  server.send(200, "text/plain", "Relay 1: ON");
  delay(200);
  switchOn(RELAY1);
  
});

server.on("/relay/1/off", [](){
  server.send(200, "text/plain", "Relay 1: OFF");
  delay(200);
  switchOff(RELAY1);
});

server.on("/relay/2/on", [](){
  server.send(200, "text/plain", "Relay 2: ON");
  delay(200);
  switchOn(RELAY2);
});

server.on("/relay/2/off", [](){
  server.send(200, "text/plain", "Relay 2: OFF");
  delay(200);
  switchOff(RELAY2);
});
#endif

// ###### ROLLER SHUTTER
#if IMPLEMENT_ROLLERSHUTTER
server.on("/rollershutter/close", [](){
  switchOn(RELAY2); //ANDEREN SCHALTER AUSSCHALTEN
  server.send(200, "text/plain", "Rolladen fährt herunter.");
  delay(200);
  switchOff(RELAY1);
  delay(20000);
  switchOn(RELAY1);
});

server.on("/rollershutter/open", [](){
  switchOn(RELAY1); //ANDEREN SCHALTER AUSSCHALTEN
  server.send(200, "text/plain", "Rolladen fährt hoch.");
  delay(200);
  switchOff(RELAY2);
  delay(20000);
  switchOn(RELAY2);
});
#endif

// ###### DOOR OPENER
#if IMPLEMENT_DOOROPENER
server.on("/door/1/open", [](){
  server.send(200, "text/plain", "Opening door #1 for three seconds.");
  delay(200);
  switchOn(RELAY1);  
});

server.on("/door/2/open", [](){
  server.send(200, "text/plain", "Opening door #2 for three seconds.");
  delay(200);
  switchOn(RELAY2);  
});
server.on("/door/1/open/delay", [](){
  server.send(200, "text/plain", "Opening door #1 for three seconds after a short delay.");
  delay(5000);
  switchOn(RELAY1);  
});

server.on("/door/2/open/delay", [](){
  server.send(200, "text/plain", "Opening door #2 for three seconds after a short delay.");
  delay(5000);
  switchOn(RELAY2);  
});
#endif

// ###### ROUTES 
#if IMPLEMENT_WIFI
server.on("/button1", [](){
  server.send(200, "text/plain", "test");
});
#endif
