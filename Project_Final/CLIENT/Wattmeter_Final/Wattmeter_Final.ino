/***************************************** Definitions for Hardware Part ****************************************/

#define pi  3.1415926535
#define c_len 10
#define limit 450 // number of samples taken per one loop of code

///// Calculation Variables /////

float V_corr = 222.0 / 258.0; // correction factor used for voltage
float I_corr = 1; // correction factor used for current
float voltages[limit]; // voltage array storing voltage readings
float currents[limit]; // current array storing current readings
long int t0, t1; // time stamp (starting and stopping time for samples)
float V = 0, I = 0, theta = 0, power = 0;  //Voltmeter final parameters to be sent

float R1 = 100.00;  //kohm
float R2 = 4.70;    //kohm
float RI = 220.0;    //ohm
float Vp = 220.0;    //volt
float Vs = 9.2;      //volt
float Ip = 5000.0;   //mA
float Is = 5.0;      //mA
float Vref = 3.30;    //volt


///// ESP Pin Definitions /////

#define inPin A0
#define ctrl1 5
#define ctrl2 16


/***************************************** Wattmeter Functions ****************************************/

void startWattmeter() {
  pinMode(inPin, INPUT);
  pinMode(ctrl1, OUTPUT);
  pinMode(ctrl2, OUTPUT);
  digitalWrite(ctrl1, 0);
  digitalWrite(ctrl2, 0);
}

void wattmeter() {
  takeReading();  // takes voltage current samples
  calculateVals(); // does the main calculations
}

void takeReading() {
  
  // (1) take offset reading
  // (2) take voltage current readings
  // (3) offset the voltage current readings to zero
  
  double offset = 0;

  ///// Take offset reading first /////

  digitalWrite(ctrl1, 0);
  digitalWrite(ctrl2, 1);
  offset = analogRead(inPin);
  digitalWrite(ctrl2, 0);

  ///// take voltage current readings /////

  t0 = micros(); //starting time
  for (int i = 0; i < limit; i++) {
    digitalWrite(ctrl1, 0); //set analogpin to voltage
    voltages[i] = analogRead(inPin); //take voltage reading
    digitalWrite(ctrl1, 1); //set analogpin to current
    currents[i] = analogRead(inPin); //take current reading
  }
  t1 = micros(); //stopping time

  ///// zero offset voltage current /////

  for (int i = 0; i < limit; i++) {
    voltages[i] -= offset;
    currents[i] -= offset;
  }
}

void calculateVals() {

  // (1) identify the zero crossings
  // (2) identify full cycles available, measure voltage, current and phase difference

  int counterVpos = 0; // how many times voltage crossed from negative to positive
  int counterIpos = 0; // how many times current crossed from negative to positive
  int stampVpos[c_len] = {}; // array of the sampling indices at which counterVpos increases
  int stampIpos[c_len] = {}; // array of the sampling indices at which counterVpos increases
  float VsqrSum = 0, IsqrSum = 0;
  V = 0; // setting global voltage to zero
  I = 0; // setting global current to zero

  ///// identify positive zero crossings /////

  for (int i = 1; i < limit ; i++) {
    if ( voltages[i - 1] < 0 && voltages[i] >= 0 && counterVpos < c_len) {
      stampVpos[counterVpos] = i; // voltage positive zero crossing index
      counterVpos++;
    }

    if ( currents[i - 1] < 0 && currents[i] >= 0  && counterIpos < c_len ) {
      stampIpos[counterIpos] = i; // current positive zero crossing index
      counterIpos++;
    }
  }

  ///// measure rms values of voltage current and find pf angle /////

  if (abs(counterVpos - counterIpos) <= 2 ) {
    // when there is a valid current waveshape, zero crossings for voltage and current are similar

    // take square sums of voltages and currents for full cycles (excluding data for incomplete cycle)
    for (int i = stampVpos[0]; i < stampVpos[counterVpos - 1] ; i++) {
      // converting analogRead() value to actual voltage value at input pin
      V = voltages[i] * (Vref / 1023.0); 
      VsqrSum += V * V;
      I = currents[i] * (Vref / 1023.0);
      IsqrSum += I * I;
    }

    // converting the voltage values at sensor to actual rms voltage and current value 
    V = sqrt((VsqrSum) / ((float)(stampVpos[counterVpos - 1] - stampVpos[0]))) * ((R1 + R2) / R2) * (Vp / Vs); 
    V = V * V_corr; // multiply correction factor
    I = sqrt((IsqrSum) / ((float)(stampVpos[counterVpos - 1] - stampVpos[0]))) / RI * (Ip / Is);
    if (I <= 0.03)
      I = 0;
    I = I * I_corr;

    // difference between first zero crossing of voltage and current is the phase difference
    theta = stampIpos[0] - stampVpos[0];
    theta = (360.0 * theta) / (float)(stampVpos[1] - stampVpos[0]) ;

    power = V * I * cos(theta * pi / 180);
  }

  else {
    // when there is not a valid current waveshape, current is set to zero

    for (int i = stampVpos[0]; i <= stampVpos[counterVpos - 1] ; i++) {
      V = voltages[i] * (Vref / 1023.0); //transform to values at pin
      VsqrSum += V * V;
    }

    V = sqrt((VsqrSum) / ((float)(stampVpos[counterVpos - 1] - stampVpos[0]))) * ((R1 + R2) / R2) * (Vp / Vs); //original values
    V = V * V_corr;
    I = 0;
    theta = 0;
    power = V * I * cos(theta);
  }
}

/***************************************** Definitions for WiFi Part ****************************************/

#include <ESP8266WiFi.h>

const char* ssid = "HUAWEI nova 3i";         // SSID of WiFi Network
const char* password = "a1dbba4ee739";    // Password of WiFi Network

char server[] = "192.168.43.137";    // Server Address
int port = 11500;                   // Server Port

WiFiClient Client;              // define ESP as client

unsigned long int connection_tries = 0;

/***************************************** WiFi Connection Handler Function ****************************************/

void startWiFi(){

  Serial.print("Connecting To: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);     // connect to WIFI
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  // after successful WiFi connection, the Blue LED blinks 20 times
  for (int i = 0; i < 20; i++)
  {
    digitalWrite(2, HIGH);
    delay(50);
    digitalWrite(2, LOW);
    delay(50);
  }
  
  Serial.println("");
  Serial.println("WiFi Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.flush();
}

/***************************************** Main Handling CODE ****************************************/

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Serial.begin(115200);
  Serial.println();
  startWiFi();
  startWattmeter();
}

void loop() {

  digitalWrite(2, LOW); // when not connected to server, status led will be bright
  
  Client.connect(server, port); // try to connect to server
  Serial.println(++connection_tries); // this number increases if server not found
  
  while (Client.connected())
  {
    wattmeter(); // take wattmeter readings
    digitalWrite(2, HIGH);
    
    String MAIN_DATA = String(V) + "," + String(I) + "," + String(theta); // data string

    Serial.print(V);
    Serial.print(" Volts, ");
    Serial.print(I);
    Serial.print(" Amps, ");
    Serial.print(theta);
    Serial.print(" Degrees, ");
    Serial.print(power);
    Serial.println(" Watts");

    Client.println(MAIN_DATA);  // send data string to server

    digitalWrite(2, LOW);
    delay(1000);
  }
}
