uint32_t getTime(){
  if(UDP.parsePacket() ==0){
    return 0;
  }
  UDP.read(NTPBuffer,NTP_PACKET_SIZE);
  uint32_t NTPTime = (NTPBuffer[40]<<24) | (NTPBuffer[41]<<16) | (NTPBuffer[42]<<8) | NTPBuffer[43];
  const uint32_t seventyYears = 2208988800UL;
  uint32_t UNIXTime = NTPTime - seventyYears;
  return UNIXTime;
}

void sendNTPpacket(IPAddress& address){
  memset(NTPBuffer,0,NTP_PACKET_SIZE);
  NTPBuffer[0] = 0b11100011;
  UDP.beginPacket(address,123);
  UDP.write(NTPBuffer,NTP_PACKET_SIZE);
  UDP.endPacket();
}

inline int getSeconds(uint32_t UNIXTime){
  return UNIXTime % 60;
}

inline int getMinutes(uint32_t UNIXTime){
  return UNIXTime / 60 % 60;
}

inline int getHours(uint32_t UNIXTime){
  return UNIXTime / 3600 % 24;
}
