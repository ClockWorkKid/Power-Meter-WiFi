#include <ESP8266WiFi.h> // Include WiFi library
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;

const char* ssid1  = "MahathirSayeed"; const char* password1  = "e569874123";
const char* ssid2  = "Sayeed";         const char* password2  = "987456321";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFiMulti.addAP(ssid1,password1);
  WiFiMulti.addAP(ssid2,password2);

  Serial.println("Connecting...");

  int i = 0;
  while (WiFiMulti.run() != WL_CONNECTED ){
    delay(1000);
    Serial.println(++i);
  }
  
  Serial.println();
  Serial.print("Connected to: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  
}
