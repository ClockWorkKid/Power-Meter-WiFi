#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <FS.h>

ESP8266WiFiMulti WiFiMulti;
ESP8266WebServer server(80);

String getContentType(String filename);
bool handleFileRead(String path);

const char* ssid1  = "MahathirSayeed"; const char* password1  = "e569874123";

void setup(void) {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFiMulti.addAP(ssid1, password1);

  Serial.print("Connecting...");

  while (WiFiMulti.run() != WL_CONNECTED ) {
    delay(100);
    Serial.print('.');
  }

  Serial.println();
  Serial.print("Connected to: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("nodemcu"))
    Serial.println("Error in setting up mDNS responder");
  else
    Serial.println("mDNS responder started.");

  SPIFFS.begin();
  server.onNotFound([]() {
    if (!handleFileRead(server.uri()))
      server.send(404, "text/plain", "404: Not Found :p");
  });

  server.begin();
  Serial.println("HTTP server started");

}

void loop(void) {
  server.handleClient();
}

String getContentType(String filename) {
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".png")) return  "image/png";
  else if (filename.endsWith(".gif")) return  "image/gif";
  else if (filename.endsWith(".jpg")) return  "image/jpeg";
  else if (filename.endsWith(".xml")) return  "text/xml";
  else if (filename.endsWith(".pdf")) return  "application/x-pdf";
  else if (filename.endsWith(".zip")) return  "application/x-zip";
  else if (filename.endsWith(".gz"))  return  "application/x-gzip";
  return "text/plain" ;
}

bool handleFileRead(String path) {
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";
  String  contentType = getContentType(path);
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;
}
