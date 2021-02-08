void init_Meter()
{
  pinMode(inPin, INPUT);
  pinMode(ctrl1, OUTPUT);
  pinMode(ctrl2, OUTPUT);
  pinMode(ctrl3, OUTPUT);
  digitalWrite(ctrl1, 0);
  digitalWrite(ctrl2, 0);
  digitalWrite(ctrl3, 0);
  sampling_period = 20 * 1000 / sample_per_period; // microseconds
}
