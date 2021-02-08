void init_input() {
  pinMode(inPin, INPUT);
  pinMode(ctrl1, OUTPUT);
  pinMode(ctrl2, OUTPUT);

  digitalWrite(ctrl1, 0);
  digitalWrite(ctrl2, 0);

  sampling_period = 20000/sample_per_period; // microseconds
}

void takeReading() {

  double offset = 0;
  unsigned long int time0, time1;

  digitalWrite(ctrl1, 0);
  digitalWrite(ctrl2, 1);
  offset = analogRead(inPin);
  digitalWrite(ctrl2, 0);

  t0 = micros();  
  for (int i = 0; i < limit; i++) {
      digitalWrite(ctrl1, 0); // select voltage
      voltages[i] = analogRead(inPin);
      digitalWrite(ctrl1, 1); // select current
      currents[i] = analogRead(inPin);
  }
  t1 = micros();

  /////////////////zero offset////////////////////
  for (int i = 0; i < limit; i++) {
      voltages[i] -= offset;
      currents[i] -= offset;
      if (plot)
        currents[i] = currents[i]*10.0;
  }
}


/*****************************************************************************/

void showVals() {
  Serial.print("theta= ");
  Serial.print(theta);
  Serial.print("; F= ");
  Serial.print(freq);
  Serial.print(" Hz; V= ");
  Serial.print(V);
  Serial.print(" V; I= ");
  Serial.print(I);
  Serial.print(" A; P= ");
  Serial.print(power);
  Serial.print(" W; PF = "); 
  Serial.println(PF);
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
