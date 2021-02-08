void zeroOffset() {
  double Vsum = 0;
  double Isum = 0;

  for (int i = 0; i < limit; i++) {
    Vsum = Vsum + voltages[i];
    Isum = Isum + currents[i];
  }

  Vsum/=limit;
  Isum/=limit;

  for (int i = 0; i < limit; i++) {
    voltages[i]-=Vsum;
    currents[i]-=Isum;
  }
}
