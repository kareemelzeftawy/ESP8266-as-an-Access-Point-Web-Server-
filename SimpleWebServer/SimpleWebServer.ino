/*
 * NodeMCU/ESP8266 act as AP (Access Point) and simplest Web Server
 * Connect to AP "arduino-er", password = "password"
 * Open browser, visit 192.168.4.1
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char *ssid = "arduino-er";
const char *password = "password";

ESP8266WebServer server(80);

void handleRoot() {
    server.send(200, "text/html", "<h1>Hello! from arduino-er!</h1>");
}

char* htmlBody_help = "<h1>Help</h1><br/>\n"
  "Visit http://192.168.4.1/ to access web server.<br/>\n"
  "Visit http://192.168.4.1/help to access this page.<br/>\n";

void handleHelp(){
  server.send(200, "text/html", htmlBody_help);
}

void setup() {
    delay(1000);
    Serial.begin(9600);
    Serial.println();

    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.on("/help", handleHelp);
    server.begin();
    Serial.println("HTTP server beginned");
}

void loop() {
    server.handleClient();
}
