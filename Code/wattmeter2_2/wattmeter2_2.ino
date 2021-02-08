//code is for nodemcu board
#define pi 3.14159265
#define limit 450 // number of samples per one loop of code
float voltages[limit],V; // voltage array
float currents[limit],I; // current array
float power, theta, PF;
float freq;
unsigned long int t0, t1; // time stamp
int sample_per_period = 100; // samples per a period of 20ms for 50Hz AC
int sampling_period; //in microseconds

bool plot = 0;
bool show = 1;

float R1 = 100;  //kohm
float R2 = 4.7;    //kohm
float RI = 220.0;    //ohm
float Vp = 222.0;    //volt
float Vs = 10.4;      //volt
float Ip = 5000.0;   //mA
float Is = 5.0;      //mA
float Vref = 3.30;    //volt

#define inPin A0
#define ctrl1 5
#define ctrl2 16

void setup() {
  Serial.begin(115200);
  init_input();
  //init_LCD();
  delay(1000);
}

void loop() {
  takeReading();
  calculate();
  
  if (plot)
    plotData();
  if (show)
    showVals();
  
}
