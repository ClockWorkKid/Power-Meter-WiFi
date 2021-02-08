const unsigned long intervalTime = 1000;   // Do a power measurement every second
unsigned long prevTime;

void data_logger() {
  
  unsigned long currentMillis = millis();

  if (currentMillis - prevTime > intervalTime) {  // Every minute, request the power
    send_to_server();
    prevTime = currentMillis;
  }
  
  wattmeter();
  ArduinoOTA.handle();                        // listen for OTA events
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void send_to_server() {

  if (!Client.connected())
  {
    Serial.println("trying to connect");
    Client.connect(server, port);
    if (Client.connected()) Serial.println("connected");
  }

  if (Client.connected()){
  Serial.println("sending data");
  String a = "" + String(V) + " " + String(I) + " " + String(power) + "\n";
  //Serial.println(Client.connected());
  Serial.println(a);
  Client.println(a);
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////
