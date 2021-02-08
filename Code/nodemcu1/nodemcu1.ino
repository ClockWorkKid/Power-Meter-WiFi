#include <ESP8266WiFi.h> // Include WiFi library

const char* ssid      = "MahathirSayeed";
const char* password  = "e569874123";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.begin(ssid,password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED ){
    delay(1000);
    Serial.println(++i); Serial.print(' ');
  }
  
  Serial.println();
  Serial.print("Connected!");
  Serial.print("IP Address: \t");
  Serial.println(WiFi.localIP());

}

void loop() {
  
}
