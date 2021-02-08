#include <ESP8266WiFi.h>
#define limit 400 // number of samples per one loop of code
float voltages[limit]; // voltage array
float currents[limit]; // current array
long int t0, t1; // time stamp
int sample_per_period = 100; // samples per a period of 20ms for 50Hz AC
int sampling_period; //in microseconds
float V = 0, I = 0, theta = 0, power = 0;     //Voltmeter final parameters

float R1 = 100.00;  //kohm
float R2 = 4.70;    //kohm
float RI = 220.0;    //ohm
float Vp = 220.0;    //volt
float Vs = 9.2;      //volt
float Ip = 5000.0;   //mA
float Is = 5.0;      //mA
float Vref = 3.30;    //volt

#define inPin A0
#define ctrl1 5

void startWattmeter(){
  pinMode(inPin, INPUT);
  pinMode(ctrl1, OUTPUT);
  digitalWrite(ctrl1, 0);
  sampling_period = 20 * 1000 / sample_per_period; // microseconds
}

void wattmeter(){
  takeReading();
  calculateVals();
}

void takeReading() {

  double Vsum = 0;
  double Isum = 0;
  
////////////////////// take analogRead values //////////////////////////////////
  
  t0 = micros();
  for (int i = 0; i < limit; i++) {
    digitalWrite(ctrl1, 0);
    voltages[i] = analogRead(inPin);
    digitalWrite(ctrl1, 1);
    currents[i] = analogRead(inPin);
    delayMicroseconds(sampling_period);
  }
  t1 = micros();

//////////////////////// Offset to zero ////////////////////////////////////////


  for (int i = 0; i < limit; i++) {
    Vsum = Vsum + voltages[i];
    Isum = Isum + currents[i];
  }

  Vsum /= limit;
  Isum /= limit;

  for (int i = 0; i < limit; i++) {
    voltages[i] -= Vsum;
    currents[i] -= Isum;
  }
}

void calculateVals() {
  int counter = 0, state1 = 0, state0 = 0, stamp[40] = {}, cycles = 0;
  long int duration = 0;
  float VsqrSum = 0, IsqrSum = 0;
  V = 0;
  I = 0;

  //identify zero crossings and measure frequency
  state0 = (voltages[0] > 0) ?  1 : -1 ;
  for (int i = 1; i < limit && counter < 40; i++) {
    state1 = (voltages[i] > 0) ? 1 : -1 ;
    if (state1 != state0)
    {
      stamp[counter] = i;//zero crossing indices
      counter++;
      state0 = state1;
    }
  }
  if (!(counter % 2)) counter-- ;

  //measure Vrms Irms
  for (int i = stamp[0]; i <= stamp[counter - 1] ; i++)
  {
    V = voltages[i] * (Vref / 1023.0); //transform to values at pin
    VsqrSum += V * V;
    I = currents[i] * (Vref / 1023.0);
    IsqrSum += I * I;
  }
  V = sqrt((VsqrSum) / ((float)(stamp[counter - 1] - stamp[0]))) * ((R1 + R2) / R2) * (Vp / Vs); //original values
  I = sqrt((IsqrSum) / ((float)(stamp[counter - 1] - stamp[0]))) / RI * (Ip / Is);
  power = V*I*cos(theta);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ssid = "MahathirSayeed";         // Enter the SSID of your WiFi Network. *****************
const char* password = "e569874123";    // Enter the Password of your WiFi Network. ******************
char server[] = "192.168.0.103";    // write SMTP server address ****************
int port = 11500;
//sudo chmod a+rw /dev/ttyUSB0
WiFiClient Client;              //define wifi client as client

////////////////////////////////////////////////////////////////////////////////////////////////////



  
void setup() {



  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.begin(115200);         // set baudrate as 9600 similar to Atmega16
  Serial.println("");
  Serial.print("Connecting To: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);     // connect to WIFI
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.flush();
  //////////////////////////////////////////////////////////////////////////////////////////////////
  startWattmeter();
}

void loop() {

//////////////////////////////////////////////////////////////////////
    Client.connect(server, port);
    Serial.println(0);
    while(Client.connected())
    {
      String a=""+String(V)+" "+String(I)+" "+String(power)+"\n";
      
    Serial.print(V);
    Serial.print(' ');
    Serial.print(I);
    Serial.print(' ');
    Serial.println(power);
    
    Client.println(a);
    ///////////////////////////////////////////////////////////////////////////

    wattmeter();
    delay(1000);
      
    }
  
}
