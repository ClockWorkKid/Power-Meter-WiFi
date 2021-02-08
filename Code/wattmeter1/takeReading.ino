void takeReading() {
  t0 = micros();
  for (int i = 0; i < limit; i++) {
    voltages[i] = analogRead(inV);
    currents[i] = analogRead(inI);
    delayMicroseconds(sampling_period);
  }
  t1 = micros();
}
