#include <SoftwareSerial.h>

SoftwareSerial mySerial(softSerialRX, softSerialTX); // RX, TX

void init_comm() {
  mySerial.begin(9600);
  pinMode(comm_trig,INPUT);
}

void send_data() { 
  mySerial.print(V);
  mySerial.print(',');
  mySerial.print(I);
  mySerial.print(',');
  mySerial.println(theta);
}
