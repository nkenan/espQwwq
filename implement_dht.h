void implement_dht_setup() {
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  if (debug) {
    Serial.println("DHTxx Unified Sensor Example");
    Serial.println("------------------------------------");
    Serial.println("Temperature");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
    Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
    Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");
    Serial.println("------------------------------------");
  };
  dht.humidity().getSensor(&sensor);
  if (debug) {
    Serial.println("------------------------------------");
    Serial.println("Humidity");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
    Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
    Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");
    Serial.println("------------------------------------");
  };
  delayMS = sensor.min_delay / 1000;
};

void implement_dht_loop() {
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    if (debug) Serial.println("Error reading temperature!");
  }
  else {
    if (debug) Serial.print("Temperature: ");
    temperature = event.temperature;
    if (debug) Serial.print(temperature);
    if (debug) Serial.println(" *C");
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    if (debug) Serial.println("Error reading humidity!");
  }
  else {
    if (debug ){
      Serial.print("Humidity: ");
      humidity = event.relative_humidity;
      Serial.print(humidity);
      Serial.println("%");
    }
  };
};
