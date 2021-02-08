#include <ESP8266WiFi.h>
const char* ssid = "MahathirSayeed";         // Enter the SSID of your WiFi Network. *****************
const char* password = "e569874123";    // Enter the Password of your WiFi Network. ******************
char server[] = "192.168.0.106";    // write SMTP server address ****************
int port = 11500;

WiFiClient Client;              //define wifi client as client

#define limit 400 // number of samples per one loop of code
float voltages[limit]; // voltage array
float currents[limit]; // current array
long int t0, t1; // time stamp
int mavgParam = 3; // number of running average terms
float expo = 0.8;
int sample_per_period = 200; // samples per a period of 20ms for 50Hz AC
int sampling_period; //in microseconds

bool plot = 0;
bool calculate = 1;

float R1 = 100.600;  //kohm
float R2 = 4.590;    //kohm
float RI = 220.0;    //ohm
float Vp = 220.0;    //volt
float Vs = 9.2;      //volt
float Ip = 5000.0;   //mA
float Is = 5.0;      //mA
float Vref = 2.96;    //volt

float V = 0, I = 0, freq = 0;

#define inPin A0
#define ctrl1 16
#define ctrl2 5
#define ctrl3 4
#define LED 2

void takeReading();
void zeroOffset();
void plotData();
void showVals();
byte sendEmail();
byte emailResp();

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("");
  Serial.print("Connecting To: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);     // connect to WIFI

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.flush();

  
  pinMode(inPin, INPUT);
  pinMode(ctrl1, OUTPUT);
  pinMode(ctrl2, OUTPUT);
  pinMode(ctrl3, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(ctrl1, 0);
  digitalWrite(ctrl2, 0);
  digitalWrite(ctrl3, 0);
  digitalWrite(LED, LOW);
  sampling_period = 20 * 1000 / sample_per_period; // microseconds
}

void loop() {
  takeReading();
  zeroOffset();
  //if (plot)
    //plotData();
  //if (calculate)
  showVals();
  sendEmail();
}
