String wifiMode = "apSta"; // client, ap, apSta

int secondsToWaitForAp = 15;
    
int retryClientConnectCount = 0;
int retryClientConnectCountMaximum = 30000;

int retryClientConnectCycleCount = 1;
int retryClientConnectCycleCountMaximum = 3;

bool retryClientConnectStop = false;

void refreshApi() {
  //"espQwwq": true, "switch": "true", "dht": "true", "pir": "false", "irremote": "false", "ledstrip": "false", "update": "false"
  //timestamp("on");
  json = "{\n";
  json += "\"espQwwq\" : \"true\", \n";
  json += "\"rssi\" : \"" + String(WiFi.RSSI()) + "\",\n";
  json += "\"chipId\" : \"" + String(ESP.getChipId()) + "\",\n";
  #if IMPLEMENT_SWITCH
  json += "\"switch\" : \"true\", \n";
  #else
  json += "\"switch\" : \"false\", \n";
  #endif
  #if IMPLEMENT_DHT
  json += "\"dht\" : \"true\", \n";
  #else
  json += "\"dht\" : \"false\", \n";
  #endif
  #if IMPLEMENT_PIR
  json += "\"pir\" : \"true\", \n";
  #else
  json += "\"pir\" : \"false\", \n";
  #endif
  #if IMPLEMENT_IR_REMOTE
  json += "\"irremote\" : \"true\", \n";
  #else
  json += "\"irremote\" : \"false\", \n";
  #endif
  #if IMPLEMENT_OTA
  json += "\"otaUpdate\" : \"true\", \n";
  #else
  json += "\"otaUpdate\" : \"false\", \n";
  #endif
  json += "}";
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

bool wifiHandle(String newWifiMode) {
  
  if (newWifiMode == "off") {
    WiFi.mode(WIFI_OFF);
    notification(3,"[WIFI] Off");
    return true;    
  };
  
  if ( wifiMode != newWifiMode ) {
    retryClientConnectCount = 0;
  };
  
  if( retryClientConnectCount != 0 && (retryClientConnectCount % retryClientConnectCountMaximum)) {
    if (retryClientConnectCycleCount > retryClientConnectCycleCountMaximum) {
      retryClientConnectStop = true;
    };
    if (retryClientConnectCount >= retryClientConnectCountMaximum) {
      retryClientConnectCycleCount += 1;
      retryClientConnectCount = 0;
    };
    retryClientConnectCount += 1;
    return false;
  };
  
  notification(3,"[WIFI] Setting up wifi");
 
  if ( wifiMode != newWifiMode ) {
    notification(3,"[WIFI] Changing wifi mode from " + wifiMode + " to " + newWifiMode);
  };
  
  wifiMode = newWifiMode;
  
  notification(3,"[WIFI] Wifi mode: " + wifiMode);  
  
  if (retryClientConnectCount == 0) {      
    if (wifiMode == "client") WiFi.mode(WIFI_STA);
    if (wifiMode == "ap") WiFi.mode(WIFI_AP);
    if (wifiMode == "apSta") WiFi.mode(WIFI_AP_STA);    
    if (wifiMode == "ap" || "apSta" ) {
      WiFi.hostname(mySsid);
      WiFi.softAP(mySsid, myPassword);
      server.begin(); notification(3, "[WIFI] Webserver started.");
      };

    if (MDNS.begin(mySsid)) {
      if (debug) {
        Serial.print("[WIFI] MDNS responder started: ");
        Serial.print(String(mySsid));
        Serial.println(".local");
      };
    };
  };

  if (wifiMode == "client" || "apSta") {
    WiFi.begin(apSsid,apPassword);
    int i=0;
    while (WiFi.status() != WL_CONNECTED) {
      if (debug) {
        Serial.print(".");
        if (i > secondsToWaitForAp ) {
          Serial.println("");
          break;
        };
      };      
      i++;
      delay(1000);
    };
  
    if(WiFi.status() != WL_CONNECTED) {
      notification(1, "[WIFI] Could not connect to " + String(apSsid));
      retryClientConnectCount += 1;
      return false;
    } else {
      retryClientConnectCount = 0;
      notification(0, "[WIFI] Client connected to " + String(apSsid));
      notification(3, "[WIFI] RSSI (dBm): " + String(WiFi.RSSI()));
      IPAddress ipAddress = WiFi.localIP();
      Serial.print("[WIFI] IP address: ");
      Serial.println(ipAddress);
    };
  };
  return true;
};

void implement_wifi_setup() {
  //if (!wifiHandle("client")) wifiHandle("ap");
  wifiHandle(wifiMode);
  #include "implement_routes.h"
};

void implement_wifi_loop() {
  if ( retryClientConnectCount != 0 && ! retryClientConnectStop ) {
    wifiHandle(wifiMode);
  };
  server.handleClient();
};
