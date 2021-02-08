#define c_len 10

void calculate() {

  int counterVpos = 0, counterVneg = 0, counterIpos = 0, cycles = 0, k = 0;
  int stampVpos[c_len] = {}, stampIpos[c_len] = {};
  unsigned long int duration = 0;
  float VsqrSum = 0, IsqrSum = 0;
  float thetaPos = 0, thetaNeg = 0;

  //identify zero crossings and measure frequency

  for (int i = 0; i < limit ; i++) {
    if ( voltages[i - 1] < 0 && voltages[i] >= 0 && counterVpos < c_len) {
      stampVpos[counterVpos] = i;// voltage positive zero crossing index
      counterVpos++;
    }

    if ( currents[i - 1] < 0 && currents[i] >= 0  && counterIpos < c_len ) {
      stampIpos[counterIpos] = i;// current positive zero crossing index
      counterIpos++;
    }
  }

  Serial.print(counterVpos);
  Serial.print(' ');
  Serial.print(counterIpos);
  Serial.print(' ');

  cycles = counterVpos - 1;
  duration = (t1 - t0) * (stampVpos[counterVpos - 1] - stampVpos[0]) / limit ;
  freq = (float)cycles * (float)1000000 / (float)duration ;


  //measure Vrms Irms

  if (abs(counterVpos - counterIpos) <= 2) {
    // for when there is a valid current waveshape
    for (int i = stampVpos[0]; i < stampVpos[counterVpos - 1] ; i++) {
      V = voltages[i] * (Vref / 1023.0); //transform to values at pin
      VsqrSum += V * V;
      I = currents[i] * (Vref / 1023.0);
      IsqrSum += I * I;
    }
    
    V = sqrt((VsqrSum) / ((float)(stampVpos[counterVpos - 1] - stampVpos[0]))) * ((R1 + R2) / R2) * (Vp / Vs); //original values
    I = sqrt((IsqrSum) / ((float)(stampVpos[counterVpos - 1] - stampVpos[0]))) / RI * (Ip / Is);


    theta = 0;

    thetaPos = stampIpos[0] - stampVpos[0];
    thetaPos = (360.0 * thetaPos) / (float)(stampVpos[1] - stampVpos[0]) ;
    theta = thetaPos;

    PF = cos(theta*pi/180);
    power = V * I * PF;
  }

  else {
    for (int i = stampVpos[0]; i <= stampVpos[counterVpos - 1] ; i++) {
      V = voltages[i] * (Vref / 1023.0); //transform to values at pin
      VsqrSum += V * V;
    }

    V = sqrt((VsqrSum) / ((float)(stampVpos[counterVpos - 1] - stampVpos[0]))) * ((R1 + R2) / R2) * (Vp / Vs); //original values
    I = 0;
    theta = 0;
    power = V * I * cos(theta);
  }

}

