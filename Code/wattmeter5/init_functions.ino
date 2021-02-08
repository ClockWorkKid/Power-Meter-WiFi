void startWiFi() {

  // Try to connect to some given access points. Then wait for a connection
  wifiMulti.addAP("MahathirSayeed", "e569874123");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("Tahmid", "ahnafia9999");
  wifiMulti.addAP("Sayeed", "987456321");

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

  Serial.println("Connecting to WiFi");
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

  // show status on led
  for(int i = 0; i < 20; i++) {
    digitalWrite(status_LED, HIGH);
    delay(100);
    digitalWrite(status_LED, LOW);
    delay(100);
  }

}

