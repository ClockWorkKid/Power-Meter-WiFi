#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>

ESP8266WiFiMulti wifiMulti;

const byte led = 2;
unsigned long T0 = millis();
const unsigned long interval = 100;

const char* ssid = "MahathirSayeed";
const char* password = "e569874123";

void setup(){
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP(ssid,password);

  Serial.print("Connecting...");
  while(wifiMulti.run()!=WL_CONNECTED){
    delay(20);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address:\t");
  Serial.println(WiFi.localIP());

  ArduinoOTA.setHostname("ESP8266");
  ArduinoOTA.setPassword("987456321");

  ArduinoOTA.onStart([](){
    Serial.println("Start");
  });

  ArduinoOTA.onEnd([](){
    Serial.println("Start");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total){
    Serial.printf("Progress: %u%%\r",(progress/(total/100)));
  });
  ArduinoOTA.onError([](ota_error_t error){
    Serial.printf("Error[%u]: ",error);
    if (error == OTA_AUTH_ERROR) Serial.println("Authorization Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connection Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA ready");

  pinMode(led,OUTPUT);
  digitalWrite(led,1);
}

void loop(){
  ArduinoOTA.handle();

  unsigned long diff = millis() - T0;
  if(diff>interval){
    digitalWrite(led,!digitalRead(led));
    T0 += diff;
  }
}
