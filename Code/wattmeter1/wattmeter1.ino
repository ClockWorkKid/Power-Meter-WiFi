//code is for blue-pill STM32F103C board

#define limit 1600 // number of samples per one loop of code
float voltages[limit]; // voltage array
float currents[limit]; // current array
long int t0, t1; // time stamp
int mavgParam = 3; // number of running average terms
float expo = 0.8;
int sample_per_period = 400; // samples per a period of 20ms for 50Hz AC
int sampling_period; //in microseconds

bool applyExpFilter = 1;
bool applyRunAvg = 1;
bool plot = 0;
bool calculate = 1;

float R1 = 100.600;  //kohm
float R2 = 4.590;    //kohm
float RI = 220.0;    //ohm
float Vp = 220.0;    //volt
float Vs = 9.2;      //volt
float Ip = 5000.0;   //mA
float Is = 5.0;      //mA
float Vref = 3.3;    //volt

#define inV PA0
#define inI PA1

void takeReading();
void filter();
void zeroOffset();
void plotData();
void showVals();

void setup() {
  pinMode(inV, INPUT_ANALOG);
  pinMode(inI, INPUT_ANALOG);
  sampling_period = 20 * 1000 / sample_per_period; // microseconds
  delay(1000);
}

void loop() {
  takeReading();
  filter();
  zeroOffset();
  if (plot)
    plotData();
  if (calculate)
    showVals();
}
