#include <ESP8266WiFi.h>
#define pi  3.1415926535
#define c_len 10
#define limit 450 // number of samples per one loop of code

float V_corr = 222.0/258.0;
float I_corr = 1;
float voltages[limit]; // voltage array
float currents[limit]; // current array
long int t0, t1; // time stamp
float V = 0, I = 0, theta = 0, power = 0;     //Voltmeter final parameters

float R1 = 100.00;  //kohm
float R2 = 4.70;    //kohm
float RI = 220.0;    //ohm
float Vp = 220.0;    //volt
float Vs = 9.2;      //volt
float Ip = 5000.0;   //mA
float Is = 5.0;      //mA
float Vref = 3.30;    //volt

unsigned long int temp = 0;

#define inPin A0
#define ctrl1 5
#define ctrl2 16

void startWattmeter() {
  pinMode(inPin, INPUT);
  pinMode(ctrl1, OUTPUT);
  pinMode(ctrl2, OUTPUT);
  digitalWrite(ctrl1, 0);
  digitalWrite(ctrl2,0);
}

void wattmeter() {
  takeReading();
  calculateVals();
}

void takeReading() {

  double offset = 0;

  // Read offset voltage
  digitalWrite(ctrl1,0);
  digitalWrite(ctrl2,1);
  offset = analogRead(inPin);
  digitalWrite(ctrl2,0);
  
  ////////////////////// take analogRead values //////////////////////////////////

  t0 = micros();
  for (int i = 0; i < limit; i++) {
    digitalWrite(ctrl1, 0);
    voltages[i] = analogRead(inPin);
    digitalWrite(ctrl1, 1);
    currents[i] = analogRead(inPin);
  }
  t1 = micros();

   /////////////////zero offset////////////////////
  for (int i = 0; i < limit; i++) {
      voltages[i] -= offset;
      currents[i] -= offset;
  }

}

void calculateVals() {
  int counterVpos = 0, counterIpos = 0, state1 = 0, state0 = 0;
  int stampVpos[c_len] = {},stampIpos[c_len] = {}, cycles = 0;
  long int duration = 0;
  float VsqrSum = 0, IsqrSum = 0;
  V = 0;
  I = 0;

  //identify zero crossings and measure frequency
  
    for (int i = 1; i < limit ; i++) {
    if ( voltages[i - 1] < 0 && voltages[i] >= 0 && counterVpos < c_len) {
      stampVpos[counterVpos] = i;// voltage positive zero crossing index
      counterVpos++;
    }
    
    if ( currents[i - 1] < 0 && currents[i] >= 0  && counterIpos < c_len ) {
      stampIpos[counterIpos] = i;// current positive zero crossing index
      counterIpos++;
    }
  }
  

  //measure Vrms Irms
  
    if (abs(counterVpos - counterIpos) <= 2 ) {
    // for when there is a valid current waveshape
    for (int i = stampVpos[0]; i < stampVpos[counterVpos - 1] ; i++) {
      V = voltages[i] * (Vref / 1023.0); //transform to values at pin
      VsqrSum += V * V;
      I = currents[i] * (Vref / 1023.0);
      IsqrSum += I * I;
    }
    
    V = sqrt((VsqrSum) / ((float)(stampVpos[counterVpos - 1] - stampVpos[0]))) * ((R1 + R2) / R2) * (Vp / Vs); //original values
    V = V*V_corr;
    I = sqrt((IsqrSum) / ((float)(stampVpos[counterVpos - 1] - stampVpos[0]))) / RI * (Ip / Is);
    if (I<= 0.03)
      I = 0;
    I = I*I_corr;

    theta = stampIpos[0] - stampVpos[0];
    theta = (360.0 * theta) / (float)(stampVpos[1] - stampVpos[0]) ;

    power = V * I * cos(theta * pi / 180);
  }

  else {
    for (int i = stampVpos[0]; i <= stampVpos[counterVpos - 1] ; i++) {
      V = voltages[i] * (Vref / 1023.0); //transform to values at pin
      VsqrSum += V * V;
    }

    V = sqrt((VsqrSum) / ((float)(stampVpos[counterVpos - 1] - stampVpos[0]))) * ((R1 + R2) / R2) * (Vp / Vs); //original values
    V = V*V_corr;
    I = 0;
    theta = 0;
    power = V * I * cos(theta);
  }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ssid = "MahathirSayeed";         // Enter the SSID of your WiFi Network. *****************
const char* password = "e569874123";    // Enter the Password of your WiFi Network. ******************
char server[] = "192.168.0.104";    // write SMTP server address ****************
int port = 11500;
//sudo chmod a+rw /dev/ttyUSB0
WiFiClient Client;              //define wifi client as client

////////////////////////////////////////////////////////////////////////////////////////////////////




void setup() {



  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
  Serial.begin(115200);         // set baudrate as 9600 similar to Atmega16
  Serial.println("");
  Serial.print("Connecting To: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);     // connect to WIFI
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  for(int i = 0; i<20; i++)
  {
    digitalWrite(2,HIGH);
    delay(100);
    digitalWrite(2,LOW);
    delay(100);
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
  digitalWrite(2,LOW);
  Client.connect(server, port);
  
  Serial.println(temp++);
  while (Client.connected())
  {
    
    String a = String(V) + "," + String(I) + "," + String(power);

    Serial.print(V);
    Serial.print(' ');
    Serial.print(I);
    Serial.print(' ');
    Serial.println(power);

    Client.println(a);
    ///////////////////////////////////////////////////////////////////////////

    wattmeter();
    digitalWrite(2,HIGH);
    delay(1000);
    digitalWrite(2,LOW);
  }

}
