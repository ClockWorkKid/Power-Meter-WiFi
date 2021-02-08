void startWiFi(){
  wifiMulti.addAP("MahathirSayeed","e569874123");
  wifiMulti.addAP("Tahmid","ahnafia9999");

  Serial.println("Connecting");
  while(wifiMulti.run()!=WL_CONNECTED){
    delay(250);
    Serial.print('.');
  }
  Serial.println("\r\n");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address:\t");
  Serial.print(WiFi.localIP());
  Serial.println("\r\n");
}

void startUDP(){
  Serial.println("Starting UDP");
  UDP.begin(123);
  Serial.print("Local port:\t");
  Serial.println(UDP.localPort());
  Serial.println();
}
