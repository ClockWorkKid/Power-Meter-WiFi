void filter() {

  // exponential filter
  if (applyExpFilter)
  for (int i = 0; i < limit; i++) {
      if (i > 0)
      {
        voltages[i] = expo * voltages[i - 1] + (1 - expo) * voltages[i];
        currents[i] = expo * currents[i - 1] + (1 - expo) * currents[i];
      }
    }

  //running average for voltage and current
  if (applyRunAvg)
  for (int i = 0; i < limit; i++) {
      if (i >= (mavgParam - 1)) {
        float sumV = 0;
        float sumI = 0;
        for (int j = i + 1 - mavgParam ; j <= i; j++) {
          sumV = sumV + voltages[j] ;
          sumI = sumI + currents[i] ;
        }
        voltages[i] = sumV / mavgParam ;
        currents[i] = sumI / mavgParam ;
      }
    }
}
