const unsigned long intervalNTP = ONE_HOUR; // Update the time every hour
unsigned long prevNTP = 0;
unsigned long lastNTPResponse = millis();

const unsigned long intervalTime = 60000;   // Do a power measurement every second
unsigned long prevTime;
bool valRequested = false;
const unsigned long DS_delay = 500;         // Reading the power can take up to 750ms

uint32_t timeUNIX = 0;                      // The most recent timestamp received from the time server


void data_logger(){
  unsigned long currentMillis = millis();

  if (currentMillis - prevNTP > intervalNTP) { // Request the time from the time server every hour
    prevNTP = currentMillis;
    sendNTPpacket(timeServerIP);
  }

  uint32_t time = getTime();                   // Check if the time server has responded, if so, get the UNIX time
  if (time) {
    timeUNIX = time;
    Serial.print("NTP response:\t");
    Serial.println(timeUNIX);
    lastNTPResponse = millis();
  } else if ((millis() - lastNTPResponse) > 24UL * ONE_HOUR) {
    Serial.println("More than 24 hours since last NTP response. Rebooting.");
    Serial.flush();
    ESP.reset();
  }

  if (timeUNIX != 0) {
    if (currentMillis - prevTime > intervalTime) {  // Every minute, request the power
      wattmeter();
      valRequested = true;
      prevTime = currentMillis;
      Serial.println("Values requested");
    }
    if (currentMillis - prevTime > DS_delay && valRequested) { // 500 ms after requesting the temperature
      uint32_t actualTime = timeUNIX + (currentMillis - lastNTPResponse) / 1000;
      // The actual time is the last NTP time plus the time that has elapsed since the last NTP response
      valRequested = false;

      File powerLog = SPIFFS.open("/power.csv", "a"); // Write the time and the temperature to the csv file
      powerLog.print(actualTime);
      powerLog.print(',');
//      powerLog.print(freq);
//      powerLog.print(',');
//      powerLog.print(V);
//      powerLog.print(',');
//      powerLog.print(I);
//      powerLog.print(',');
      powerLog.println(V*I);
      powerLog.close();
    }
  } else {                                    // If we didn't receive an NTP response yet, send another request
    sendNTPpacket(timeServerIP);
    delay(500);
  }

  server.handleClient();                      // run the server
  ArduinoOTA.handle();                        // listen for OTA events
}
