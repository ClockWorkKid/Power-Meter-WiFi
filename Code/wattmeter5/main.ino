const unsigned long intervalTime = 1000;   // Do a power measurement every second
unsigned long prevTime;

void data_logger() {

  unsigned long currentMillis = millis();
  
  if (currentMillis - prevTime > intervalTime) {  // Every minute, request the power
    Serial.println("Attempting to send data to server");
    send_to_server();
    
    wattmeter();
    Serial.println("Wattmeter reading taken");
    prevTime = currentMillis;
  }

}


//////////////////////////////////////////////////////////////////////////////////////////////////

void send_to_server() {

  if (!Client.connected())
  {
    digitalWrite(status_LED, LOW);
    Serial.println("Trying to connect to server");
    Client.connect(server, port);
    if (!Client.connected()) Serial.println("Connection Failed");
    else Serial.println("Connected to server!");
  }

  if (Client.connected()) {
    
    Serial.println("Sending data to server");
    stat != stat;
    digitalWrite(status_LED, stat);
    
    String a = String(V) + "," + String(I) + "," + String(power);
    
    Serial.println(a);
    Client.println(a);
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////
