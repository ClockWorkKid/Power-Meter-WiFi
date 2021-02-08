void plotData() {
  for (int i = 0; i < limit; i++) {
    Serial.print(voltages[i]);
    Serial.print(',');
    Serial.println(currents[i]);
    delay(3);
  }
}
