#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Grapes";
const char* password = "Admin@123";

ESP8266WebServer server(80);
int ledPin = D4;
int ledState = LOW;
String validUsername = "admin";
String validPassword = "password";

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
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
  });

  server.on("/login", []() {
    String username = server.arg("username");
    String password = server.arg("password");
    if (username == validUsername && password == validPassword) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
      server.send(200, "text/plain", "Login successful");
    } else {
      server.send(401, "text/plain", "Invalid username or password");
    }
  });

  server.begin();
}

void loop() {
  server.handleClient();
}