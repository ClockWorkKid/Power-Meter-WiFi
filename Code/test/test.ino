#define limit 100     // number of samples per one loop of code

float V,I,P,theta,degree,freq;
float volt[limit],I1[limit],I2[limit];    // voltage current data array
unsigned long int t0, t1; // time stamp of taking readings

bool plot = 1;
bool show = 0;

#define vPin A0
#define I1Pin A1
#define I2Pin A2
#define softSerialRX A3
#define softSerialTX A4
#define comm_trig A5

void setup() {
  Serial.begin(115200);
  init_comm();
  init_LCD();
}

void loop() {
  take_reading();
  if(plot) plot_data();
  calculate();
  show_on_display();
  if(show) show_vals();
  if(digitalRead(comm_trig)) send_data();
}
