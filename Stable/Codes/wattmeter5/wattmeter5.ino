#define pi 3.14159265
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>

ESP8266WiFiMulti wifiMulti;    // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

const char *OTAName = "Power Meter";         // A name and a password for the OTA service
const char *OTAPassword = "987456321";

char server[] = "192.168.0.103";    // write SMTP server address ****************
int port = 11500;
//sudo chmod a+rw /dev/ttyUSB0
WiFiClient Client;              //define wifi client as client


float V = 0, I = 0, theta = 0, power = 0;     //Voltmeter final parameters

/*__________________________________________________________SETUP__________________________________________________________*/

void setup() {
  Serial.begin(115200);        // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println("\r\n");


  startWiFi();                 // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
  startOTA();                  // Start the OTA service
  startWattmeter();            // Begin Wattmeter and set input output pinss
  Serial.flush();

  delay(500);
}

/*__________________________________________________________LOOP__________________________________________________________*/

void loop() {
  data_logger();
}
