void calculate_time()
{
    unsigned long currentMillis = millis();

  if(currentMillis - prevNTP > intervalNTP){
    prevNTP = currentMillis;
    Serial.println("\r\nSending NTP request ...");
    sendNTPpacket(timeServerIP);
  }

  uint32_t time = getTime();
  if(time){
    timeUNIX = time;
    Serial.print("NTP response:\t");
    Serial.println(timeUNIX);
    lastNTPResponse = currentMillis;
  } else if ((currentMillis - lastNTPResponse)> 3600000){
    Serial.println("More than 1 hour since last NTP");
    Serial.flush();
    ESP.reset();
  }

  uint32_t actualTime = timeUNIX + (currentMillis - lastNTPResponse)/1000;
  if(actualTime != prevActualTime && timeUNIX !=0){
    prevActualTime = actualTime;
    Serial.printf("\rUTC time:\t%d:%d:%d \n", getHours(actualTime), getMinutes(actualTime), getSeconds(actualTime));
  }
}
