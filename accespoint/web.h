#include "secrets.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

// const char *ssid = SECRET_SSID;         
// const char *password = SECRET_OPTIONAL_PASS; 

ESP8266WebServer server(80);
// int ledPin = RELAY_PIN;
int ledState = HIGH;
const char* validUsername = SECRET_USERNAME;
const char* validPassword = SECRET_PASS;

  // server.on("/", login);
  // server.on("/login", HTTP_POST, check);
  // server.begin();
// void loop() {
//   // server.handleClient();
//   // Serial.println("loop");
// }
void login() {
  String html = "<html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Login Page</title><style>";
  html += "body { background-color: #f0f0f0; font-family: Arial, sans-serif; } .container { width: 300px; background-color: #fff; padding: 20px; margin: 50px auto; border: 1px solid #ddd; border-radius: 5px; box-shadow: 2px 2px 5px rgba(0, 0, 0, 0.1); } h1 { text-align: center; margin-bottom: 30px; } label { display: block; margin-bottom: 5px; } input[type=\"text\"], input[type=\"password\"] { width: 100%; padding: 10px; margin-bottom: 20px; border: 1px solid #ddd; border-radius: 5px; box-sizing: border-box; } input[type=\"submit\"] { background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; } input[type=\"submit\"]:hover { background-color: #45a049; } </style></head><body>";
  html += "<div class=\"container\"><h1>Login</h1>";
  html += "<form action=\"/login\" method=\"post\">";
  html += "<label for=\"username\">Username:</label>";
  html += "<input type=\"text\" id=\"username\" name=\"username\">";
  html += "<label for=\"password\">Password:</label>";
  html += "<input type=\"password\" id=\"password\" name=\"password\">";
  html += "<input type=\"submit\" value=\"Submit\">";
  html += "</form></div>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}
void check() {
  String username = server.arg("username");
  String password = server.arg("password");
  if (username == validUsername && password == validPassword) {
    String html = "<html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>LED Control</title><style>";
    html += "body { display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0;position: relative; background-color: #f5f5f5; } ";
    html += ".switch { position: relative; display: inline-block; width: 180px; height: 90px; }";
    html += " .switch input { opacity: 0; width: 0; height: 0; }";
    html += " .slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; -webkit-transition: .4s; transition: .4s; }";
    html += " .slider:before { position: absolute; content: \"\"; height: 76px; width: 76px; left: 8px; bottom: 8px; background-color: white; -webkit-transition: .4s; transition: .4s; }";
    html += " input:checked + .slider { background-color: #2196F3; }";
    html += " input:checked + .slider:before { -webkit-transform: translateX(90px); -ms-transform: translateX(90px); transform: translateX(90px); }";
    html += " .slider.round { border-radius: 90px; } .slider.round:before { border-radius: 50%; }";
    html += ".toggle-title {  margin-top: 20px;  font-size: 48px;   font-weight: bold; }";
    html += ".logout-container {  position: absolute;  top: 20px;  right: 20px; }";
    html += ".logout-button {  margin-top: 0px;  font-size: 24px;  font-weight: bold;  padding: 10px;  background-color: #4CAF50;  border: none;   border-radius: 5px;  color: white;   cursor: pointer;  }";
    html += "</style></head><body>";
    html += "<div class=\"logout-container\">";
    html += "<button class=\"logout-button\" onclick=\"logout()\">Logout</button></div>";
    html += "<label class=\"switch\"><input type=\"checkbox\" id=\"toggleButton\" onchange=\"toggleLED()\"><span class=\"slider round\"></span></label>";
    html += "<div class=\"toggle-title\">Lock</div> </div>";
    html += "<script>function toggleLED() { var xhr = new XMLHttpRequest(); xhr.open('GET', '/toggle', true); xhr.onreadystatechange = function() { if (xhr.readyState == 4 && xhr.status == 200) { if (xhr.responseText == '1') { document.getElementById('toggleButton').checked = true; } else { document.getElementById('toggleButton').checked = false; } } }; xhr.send(); }</script>";
    html += "<script>function logout(){ window.location.href = \"/\";}</script>";
    html += "</div>";
    html += "</body></html>";
    server.send(200, "text/html", html);
    // } else {
    //   server.send(401, "text/plain", "Unauthorized");
    // }
    // });
    server.on("/toggle", []() {
      // if (server.authenticate(validUsername, validPassword)) {
      ledState = !ledState;
      // digitalWrite(ledPin, ledState);
      server.send(200, "text/plain", String(ledState));
      // server.send(200, "text/plain", "OK");
      // } else {
      //   server.send(401, "text/plain", "Unauthorized");
      // }
    });
  } else {
    server.send(401, "text/plain", "Invalid username or password");
  }
}
