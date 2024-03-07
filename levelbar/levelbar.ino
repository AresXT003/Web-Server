#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

ESP8266WebServer server(80);
String level="50";

const char *ssid = " SSID ";
const char *password = " PASSWORD ";

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
  server.on("/", waterLevelMonitor);
  server.begin();
}
void loop() {
  server.handleClient();
}
void waterLevelMonitor() {
  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<style>";
  html += ".water-level-bar {";
  html += "  width: 100%;";
  html += "  height: 50px;";
  html += "  background-color: #ddd;";
  html += "  position: relative;";
  html += "}";
  html += ".water-level {";
  html += "  height: 50px;";
  html += "  width: 100%;";
  html += "  position: absolute;";
  html += "  left: 0;";
  html += "  top: 0;";
  html += "}";
  html += ".level-0 {";
  html += "  background-color: red;";
  html += "  width: 0%;";
  html += "}";
  html += ".level-25 {";
  html += "  background-color: orange;";
  html += "  width: 25%;";
  html += "}";
  html += ".level-50 {";
  html += "  background-color: yellow;";
  html += "  width: 50%;";
  html += "  height: 100%;";
  html += "}";
  html += ".level-75 {";
  html += "  background-color: lightgreen;";
  html += "  width: 75%;";
  html += "}";
  html += ".level-100 {";
  html += "  background-color: green;";
  html += "  width: 100%;";
  html += "  height: 100%;";
  html += "}";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Water Level Monitor</h1>";
  html += "<div class=\"water-level-bar\">";
  html += "  <div class=\"water-level level-0\"></div>";
  html += "</div>";
  html += "<script>";
  html +="var waterLevel ="+level+";";
  html += "var waterLevelBar = document.querySelector('.water-level');";
  html += "waterLevelBar.classList.remove('level-0', 'level-25', 'level-50', 'level-75', 'level-100');";
  html += "if (waterLevel == 0) {";
  html += "  waterLevelBar.classList.add('level-0');";
  html += "} else if (waterLevel == 25) {";
  html += "  waterLevelBar.classList.add('level-25');";
  html += "} else if (waterLevel == 50) {";
  html += "  waterLevelBar.classList.add('level-50');";
  html += "} else if (waterLevel == 75) {";
  html += "  waterLevelBar.classList.add('level-75');";
  html += "} else if (waterLevel == 100) {";
  html += "  waterLevelBar.classList.add('level-100');";
  html += "}";
  html += "</script>";
  html += "</body>";
  html += "</html>";
  server.send(200, "text/html", html);
}
