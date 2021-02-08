byte sendEmail()
{
  byte t;
  if (Client.connect(server, port) == 1)        // connect to smtp server with port address 2525
  {
    Serial.println(F("connected to server"));
    Client.println(F("This is is a test \n"));

    delay(500);
    while(!Client.available());
    while(Client.available()){
      t=Client.read();
      Serial.print((char)t);
      Serial.flush();
    }
  } 
  else 
  {
    Serial.println(F("connection failed"));
    return 0;
  }
  String data_to_b_sent = "Frequency";
  Client.println(F(data_to_b_sent.c_str()));
  //Client.printf("Frequency = %f Hz; Voltage = %f volts; Current = %f amps; Power = %f watts\n",freq,V,I,V*I);
}


byte emailResp()
{
  byte responseCode;
  byte readByte;
  int loopCount = 0;

  while (!Client.available()) 
  {
    delay(1);
    loopCount++;
    // Wait for 20 seconds and if nothing is received, stop.
    if (loopCount > 20000) 
    {
      Client.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }

  responseCode = Client.peek();
  while (Client.available())
  {
    readByte = Client.read();
    Serial.write(readByte);
  }

  if (responseCode >= '4')
  {
    //  efail();
    return 0;
  }
  return 1;
}
