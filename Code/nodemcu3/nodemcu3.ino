#include <ESP8266WiFi.h> // Include WiFi library


const char *ssid = "My_WiFi"; const char *password = "1475963";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid,password);
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

}

void loop() {
  
}
