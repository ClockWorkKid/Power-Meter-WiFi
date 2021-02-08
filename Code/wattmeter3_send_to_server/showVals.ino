void showVals() {
  int counter = 0, state1 = 0, state0 = 0, stamp[40] = {}, cycles = 0;
  long int duration = 0;
  float VsqrSum = 0, IsqrSum = 0;
  V = 0;
  I = 0;
  freq = 0;

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

  cycles = (counter - 1) / 2 ;
  duration = (t1 - t0) * (stamp[counter - 1] - stamp[0]) / limit ;
  freq = (float)cycles * (float)1000000 / (float)duration ;

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

}
