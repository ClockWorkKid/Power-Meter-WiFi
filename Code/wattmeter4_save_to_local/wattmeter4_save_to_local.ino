//code is for nodemcu board
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>

/*_________________________Voltmeter Parameters_____________________________*/

#define limit 400 // number of samples per one loop of code
float voltages[limit]; // voltage array
float currents[limit]; // current array
long int t0, t1; // time stamp
int mavgParam = 3; // number of running average terms
float expo = 0.8;
int sample_per_period = 100; // samples per a period of 20ms for 50Hz AC
int sampling_period; //in microseconds

float R1 = 100.600;  //kohm
float R2 = 4.590;    //kohm
float RI = 220.0;    //ohm
float Vp = 220.0;    //volt
float Vs = 9.2;      //volt
float Ip = 5000.0;   //mA
float Is = 5.0;      //mA
float Vref = 2.96;    //volt

float freq, V, I;

#define inPin A0
#define ctrl1 16
#define ctrl2 5
#define ctrl3 4

void takeReading();
void zeroOffset();
void showVals();
void init_Meter();
  

/*__________________________________WiFi Parameters_____________________________*/

ESP8266WiFiMulti wifiMulti;

const char* ssid1 = "MahathirSayeed";
const char* password1 = "e569874123";

void init_WiFi();

void setup() {
  Serial.begin(115200);
  init_Meter();
  init_WiFi();
  delay(100);

}

void loop() {
  ArduinoOTA.handle();
  takeReading();
  zeroOffset();
  showVals();
}
