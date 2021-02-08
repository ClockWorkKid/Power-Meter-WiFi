void takeReading() {
  t0 = micros();
  for (int i = 0; i < limit; i++) {
    digitalWrite(ctrl1, 0);
    voltages[i] = analogRead(inPin);
    digitalWrite(ctrl1, 1);
    currents[i] = analogRead(inPin);
    delayMicroseconds(sampling_period);
  }
  t1 = micros();
}
