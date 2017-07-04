ADC_MODE(ADC_VCC); // for ESP.getVcc();

bool debug = true;

#define WEMOSD1MINI false// WEMOSD1MINI, NODEMCU or SONOFF
#define NODEMCU true// WEMOSD1MINI, NODEMCU or SONOFF
#define SONOFF false// WEMOSD1MINI, NODEMCU or SONOFF
// ###################################################################
// ###################################################################
#if WEMOSD1MINI
#define NOTIFICATION_PIN 2
#define NOTIFICATION_PIN_INVERTED true
#define NOTIFICATION_PIN_OFF_DEFAULT true

#define RELAY1 12
#define RELAY1_INVERTED true

#define RELAY2 14 // ??
#define RELAY2_INVERTED true

#define BUTTON1 0
#define BUTTON1_INVERTED true

#define BUTTON2 0
#define BUTTON2_INVERTED true

#define EXTRA_PIN 14
#define IR_DETECTOR 5
#endif

#if NODEMCU
#define NOTIFICATION_PIN 2
#define NOTIFICATION_PIN_INVERTED true
#define NOTIFICATION_PIN_OFF_DEFAULT true

#define RELAY1 12
#define RELAY1_INVERTED true

#define RELAY2 14 // ??
#define RELAY2_INVERTED true

#define BUTTON1 0
#define BUTTON1_INVERTED true

#define BUTTON2 0
#define BUTTON2_INVERTED true

#define EXTRA_PIN 14
#define IR_DETECTOR 5
#endif

#if SONOFF
#define NOTIFICATION_PIN 13
#define NOTIFICATION_PIN_INVERTED true
#define NOTIFICATION_PIN_OFF_DEFAULT true

#define RELAY1 12
#define RELAY1_INVERTED true

#define RELAY2 4 // ??
#define RELAY2_INVERTED true

#define BUTTON1 0
#define BUTTON1_INVERTED true

#define BUTTON2 0
#define BUTTON2_INVERTED true

#define EXTRA_PIN 14
#define IR_DETECTOR 5
#endif
// ###################################################################
// ###################################################################
#define IMPLEMENT_WIFI true
#define IMPLEMENT_SWITCH true
#define IMPLEMENT_BUTTON true
#define IMPLEMENT_OTA true
#define IMPLEMENT_DHT false

#define IMPLEMENT_WIFIBUTTON false
#define IMPLEMENT_ROLLERSHUTTER false
#define IMPLEMENT_DOOROPENER true
// ###################################################################
// ###################################################################
#include "secret.h" //debug
#include "implement_tools.h"
// ###################################################################
// ###################################################################
#if IMPLEMENT_DHT
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 4
#define DHTTYPE DHT22 // DHT 22 (AM2302) DHT 21 (AM2301) DHT 11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
String temperature, humidity;
#include "implement_dht.h"
#endif
// ###################################################################
#if IMPLEMENT_WIFI
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
ESP8266WebServer server(80);
String json;
#include "implement_wifi.h"
#endif

// ###################################################################
#if IMPLEMENT_SWITCH
#include "implement_switch.h"
#endif

// ###################################################################
#if IMPLEMENT_BUTTON
#include "implement_button.h"
#endif

// ###################################################################
#if IMPLEMENT_OTA
#include <ArduinoOTA.h>
#include "implement_ota.h"
#endif

// ###################################################################
// ###################################################################
void setup() {
  espInformation();

  #if IMPLEMENT_SWITCH
  implement_switch_setup();
  #endif

  #if IMPLEMENT_BUTTON
  implement_button_setup();
  #endif

  #if IMPLEMENT_DHT
  implement_dht_setup();
  #endif

  #if IMPLEMENT_WIFI
  implement_wifi_setup();
  #endif

  #if IMPLEMENT_OTA
  implement_ota_setup();
  #endif
};

// ###################################################################
// ###################################################################
void loop() {
  #if IMPLEMENT_WIFI
  implement_wifi_loop();
  #endif

  #if IMPLEMENT_SWITCH
  implement_switch_loop();
  #endif

  #if IMPLEMENT_BUTTON
  implement_button_loop();
  #endif

  #if IMPLEMENT_DHT
  implement_dht_loop();
  #endif

  #if IMPLEMENT_OTA
  implement_ota_loop();
  #endif

  delay(10);
}
