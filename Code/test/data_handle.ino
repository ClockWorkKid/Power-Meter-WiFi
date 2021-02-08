#define pi 3.141592

const float R1 = 99933.5;
const float R2 = 4890;
const float RIsrc1 = 222;
const float RIsrc2 = 218;
const float RIf = 9800;
const float RI1 = 979;
const float RI1_1 = 9780;
const float RI1_2 = 3220;
const float RI2_1 = 9810;
const float RI2_2 = 3180;

const float Vp = 224.0;    //volt
const float Vs = 11.7;      //volt
const float Ip = 5000.0;   //mA
const float Is = 5.0;      //mA
const float Vref = 2.52;    //volt


void take_reading() {
  t0 = micros();
  for (int i = 0; i < limit; i++) {
    volt[i] = analogRead(A0);
    I1[i] = analogRead(A1);
    I2[i] = analogRead(A2);
  }
  t1 = micros();
}

void calculate() {

  int Vsp = 0, Vep = 0, vState, Isp = 0, Iep = 0, iState, zero_cross = 0, vDir = 0, iDir = 0;
  float Vsum = 0, I1sum = 0, I2sum = 0, Vrms = 0, I1rms = 0, I2rms = 0;

  //remove DC offset
  for (int i = 0; i < limit; i++) {
    Vsum = Vsum + volt[i];
    I1sum = I1sum + I1[i];
    I2sum = I2sum + I2[i];
  }

  Vsum /= limit;
  I1sum /= limit;
  I2sum /= limit;

  for (int i = 0; i < limit; i++) {
    volt[i] = volt[i] - Vsum;
    I1[i] = I1[i] - I1sum;
    I2[i] = I2[i] - I2sum;
  }

  //find one cycle

  vState = (volt[0] > 0) ? 1 : 0 ;
  for (int i = 1, zero_cross = 0; i < limit && zero_cross <= 2; i++) {
    if ((volt[i] > 0) != vState) {
      if (vState == 0 && zero_cross == 0) vDir = 1;
      vState = (volt[i] > 0) ;
      zero_cross++;
      if (zero_cross == 1) Vsp = i;
      if (zero_cross == 3) Vep = i;
    }
  }

  //find phase
  iState = (I2[0] > 0) ? 1 : 0;
  for (int i = 1, zero_cross = 0; i < limit && zero_cross <= 2; i++) {
    if ((I2[i] > 0) != iState) {
      if (iState == 0 && zero_cross == 0) iDir = 1;
      iState = (I2[i] > 0) ;
      zero_cross++;
      if (zero_cross == 1) Isp = i;
      if (zero_cross == 3) Iep = i;
    }
  }

  if (vState == iState)
    theta = 2 * pi * (float)(Isp - Vsp) / (float)(Vep - Vsp);
  else
    theta = 2 * pi * ((float)Isp - (float)(Vsp + Vep) / 2) / (float)(Vep - Vsp);

  theta = atan(sin(theta)/cos(theta));
  degree = 180.0 * theta / pi;


  //calculate RMS value of array data
  for (int i = Vsp; i < Vep ; i++)
  {
    Vrms += pow(volt[i] * (Vref / 1023.0), 2);
    I1rms += pow(I1[i] * (Vref / 1023.0), 2);
    I2rms += pow(I2[i] * (Vref / 1023.0), 2);
  }

  Vrms = sqrt(Vrms / (Vep - Vsp));
  I1rms = sqrt(I1rms / (Vep - Vsp));
  I2rms = sqrt(I2rms / (Vep - Vsp));

  //calculate actual voltage current
  V = Vrms * ((R1 + R2) / R2) * (Vp / Vs);

  if (I2rms < .55) {
    I = I2rms * (RI2_1 + RI2_2) / RI2_2 * RI1 / (RIf + RI1) / RIsrc2 * (Ip / Is);
  }
  else
  {
    I = I1rms * (RI1_1 + RI1_2) / RI1_2 / RIsrc2 * (Ip / Is);
  }


  P = V * I * cos(theta);
  freq = 1000000.0 / ((float)(t1 - t0) * (float)(Vep - Vsp) / limit);

}

void plot_data() {
  for (int i = 0; i < limit; i++) {
    Serial.print(volt[i]);
    Serial.print(',');
    Serial.print(I1[i]);
    Serial.print(',');
    Serial.println(I2[i]);
    delay(8);
  }
  for (int i = 0; i < 20; i++) {
    Serial.print(0);
    Serial.print(',');
    Serial.print(0);
    Serial.print(',');
    Serial.println(0);
  }
}

void show_vals() {
  Serial.print("Voltage: ");
  Serial.print(V);
  Serial.print(" volts; Current: ");
  Serial.print(I);
  Serial.print(" amps; Power: ");
  Serial.print(P);
  Serial.print(" Watts; Theta: ");
  Serial.print(degree);
  Serial.println(" degrees; Freq: ");
  Serial.println(freq);
  delay(100);

}
