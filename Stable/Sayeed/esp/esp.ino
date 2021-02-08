#include <ESP8266WiFi.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ssid = "MahathirSayeed";         // Enter the SSID of your WiFi Network. *****************
const char* password = "e569874123";    // Enter the Password of your WiFi Network. ******************
char server[] = "192.168.0.106";    // write SMTP server address ****************
int port = 11500;
//sudo chmod a+rw /dev/ttyUSB0
WiFiClient Client;              //define wifi client as client
float current=0;
float voltage=0;
float power=0;
////////////////////////////////////////////////////////////////////////////////////////////////////



  
void setup() {



  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.begin(115200);         // set baudrate as 9600 similar to Atmega16
  Serial.println("");
  Serial.print("Connecting To: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);     // connect to WIFI
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.flush();
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
}

void loop() {

//////////////////////////////////////////////////////////////////////
    Client.connect(server, port);
    while(Client.connected())
    {
      String a=""+String(voltage)+" "+String(current)+" "+String(power)+"\n";
    Serial.println(Client.connected());
    Client.println(a);
    ///////////////////////////////////////////////////////////////////////////



    
    voltage+=2.3;
    current+=4.7;
    power+=1.5;

    delay(1000);
      
    }
  
}
