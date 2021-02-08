#define limit 400 // number of samples per one loop of code
float voltages[limit]; // voltage array
float currents[limit]; // current array
long int t0, t1; // time stamp
int sample_per_period = 100; // samples per a period of 20ms for 50Hz AC
int sampling_period; //in microseconds


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
#define ctrl2 16

void startWattmeter(){
  pinMode(inPin, INPUT);
  pinMode(ctrl1, OUTPUT);
  pinMode(ctrl2, OUTPUT);
  digitalWrite(ctrl1, 0);
  digitalWrite(ctrl2, 0);
  sampling_period = 20 * 1000 / sample_per_period; // microseconds
  
  Serial.println("Sampling period ");
  Serial.println(sampling_period);
}

void wattmeter(){
  takeReading();
  calculateVals();
}

void takeReading() {

  double Vsum = 0;
  double Isum = 0;
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
    voltages[i] = analogRead(inPin) - offset;
    digitalWrite(ctrl1, 1);
    currents[i] = analogRead(inPin) - offset;
    delayMicroseconds(sampling_period);
  }
  t1 = micros();
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
