void init_input(){
  pinMode(inPin, INPUT);
  pinMode(ctrl, OUTPUT);
  digitalWrite(ctrl, 0);
  sampling_period = 20 * 1000 / sample_per_period; // microseconds
}

void takeReading() {
  t0 = micros();
  for (int i = 0; i < limit; i++) {
    digitalWrite(ctrl, 0); // select voltage
    voltages[i] = analogRead(inPin);
    digitalWrite(ctrl, 1); // select current
    currents[i] = analogRead(inPin);
    delayMicroseconds(sampling_period);
  }
  t1 = micros();
}

/*****************************************************************************/

void zeroOffset() {
  double Vsum = 0;
  double Isum = 0;

  for (int i = 0; i < limit; i++) {
    Vsum = Vsum + voltages[i];
    Isum = Isum + currents[i];
  }

  Vsum /= limit;
  Isum /= limit;

  for (int i = 0; i < limit; i++) {
    voltages[i] -= Vsum;
    currents[i] -= Isum;
  }
}


/*****************************************************************************/

void showVals(){
  Serial.print("Frequency= ");
  Serial.print(freq);
  Serial.print(" Hz; Voltage= ");
  Serial.print(V);
  Serial.print(" V; Current= ");
  Serial.print(I);
  Serial.print(" A; Power= ");
  Serial.print(V*I);
  Serial.println(" watt");
  delay(1000);
}

/*****************************************************************************/

void plotData() {
  for (int i = 0; i < limit; i++) {
    Serial.print(voltages[i]);
    Serial.print(',');
    Serial.println(currents[i]);
    delay(8);
  }
  for (int i = 0; i < 50; i++) {
    Serial.print(0);
    Serial.print(',');
    Serial.println(0);
  }
  
}
