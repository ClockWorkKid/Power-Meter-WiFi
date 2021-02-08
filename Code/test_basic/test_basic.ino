#define limit 400
int input[limit];

void setup() {
  Serial.begin(115200);

}

void loop() {
  for (int i = 0; i < limit; i++)
    input[i] = analogRead(A5);
  for (int i = 0; i < limit; i++)
    Serial.println(input[i]);
  for (int i = 0; i < 20; i++)
    Serial.println(0);

}
