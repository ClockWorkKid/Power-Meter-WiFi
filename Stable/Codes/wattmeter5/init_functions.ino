void startWiFi() { // Try to connect to some given access points. Then wait for a connection
  wifiMulti.addAP("MahathirSayeed", "e569874123");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("Tahmid", "ahnafia9999");
  wifiMulti.addAP("Sayeed","987456321");
//  wifiMulti.addAP("EEE DE LAB", "F27D4812EA");
//  wifiMulti.addAP("EEE New CKT Lab", "F27D4812EA");
//  wifiMulti.addAP("EEE Office", "F27D4812EA");
//  wifiMulti.addAP("EEE Room1102", "F27D4812EA");
//  wifiMulti.addAP("EEE Room632", "F27D4812EA");
//  wifiMulti.addAP("EEE-dsp", "F27D4812EA");
//  wifiMulti.addAP("EEE-Huawei Lab", "F27D4812EA");
//  wifiMulti.addAP("EEE-RNsim", "F27D4812EA");
//  wifiMulti.addAP("EEE-Telecom", "F27D4812EA");
//  wifiMulti.addAP("F-library", "F27D4812EA");
  
  Serial.println("Connecting");
  while (wifiMulti.run() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
    delay(100);
    Serial.print('.');
  }
  Serial.println("\r\n");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());             // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.print(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer
  Serial.println("\r\n");

  
}

void startOTA() { // Start the OTA service
  ArduinoOTA.setHostname(OTAName);
  ArduinoOTA.setPassword(OTAPassword);

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\r\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA ready\r\n");
}
