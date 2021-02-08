#include <ESP8266WiFi.h> // Include WiFi library
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h> // Include Webserver library

ESP8266WiFiMulti WiFiMulti;
ESP8266WebServer server(80);

void handleRoot();
void handleNotFound();
void handleLED();

const int led = 2;

const char* ssid1  = "MahathirSayeed"; const char* password1  = "e569874123";
const char* ssid2  = "Sayeed";         const char* password2  = "987456321";

void setup(void) {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  pinMode(led,OUTPUT);

  WiFiMulti.addAP(ssid1,password1);
  WiFiMulti.addAP(ssid2,password2);

  Serial.print("Connecting...");

  while (WiFiMulti.run() != WL_CONNECTED ){
    delay(100);
    Serial.print('.');
  }
  
  Serial.println();
  Serial.print("Connected to: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if(!MDNS.begin("nodemcu"))
    Serial.println("Error in setting up mDNS responder");
  else
    Serial.println("mDNS responder started.");  

   server.on("/",HTTP_GET,handleRoot);
   server.on("/LED",HTTP_POST,handleLED);
   server.onNotFound(handleNotFound);
   server.begin();
   Serial.println("HTTP server started");

}

void loop() {
  server.handleClient();
}

void handleRoot(){
  server.send(200,"text/html","<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form");
}

void handleNotFound(){
  server.send(404,"text/plain","404: Not found :p");
}

void handleLED(){
  digitalWrite(led,!digitalRead(led));
  server.sendHeader("Location","/");
  server.send(303);
}
