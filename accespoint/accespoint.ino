#include "secrets.h"
#include "web.h"


// #ifndef APSSID
// #define APSSID "Grapes Test"
// #define APPSK "123456789"
// #endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

// ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", login);
  server.on("/login", HTTP_POST, check);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
