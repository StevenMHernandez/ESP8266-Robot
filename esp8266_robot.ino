#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h> 

#include "index.h"

int last = -10000;
int motor_speed = 50;
int left_direction = 0;
int right_direction = 0;

const char* ssid = "im_a_robot";
const char* password = "im_very_driven";

ESP8266WebServer server(80);

Servo servoleft;
Servo servoright;

void handleRoot() {
 String s = MAIN_page;
 server.send(200, "text/html", s);
}

void handleSpeed() {
 String t_state = server.arg("speed");
 motor_speed = t_state.toInt();
 Serial.println(t_state);
 server.send(200, "text/plain", "ok");
}

void handleLeft() {
 String direction = server.arg("direction");
 left_direction = direction.toInt();
 last = millis();
 server.send(200, "text/plain", "ok");
}

void handleRight() {
 String direction = server.arg("direction");
 right_direction = direction.toInt();
 last = millis();
 server.send(200, "text/plain", "ok");
}

void setup(void){
  Serial.begin(115200);
  
  servoleft.attach(0);   // D3
  servoright.attach(4);  // D2

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);
  server.on("/setSpeed", handleSpeed);
  server.on("/setLeft", handleLeft);
  server.on("/setRight", handleRight);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();

  if (last + 10000 > millis()) {
    servoleft.write(90 + (left_direction * motor_speed));
    servoright.write(90 + (right_direction * motor_speed));
  } else {
    servoleft.write(90);
    servoright.write(90);
  }

  Serial.print(left_direction);
  Serial.print(",");
  Serial.print(right_direction);
  Serial.print(",");
  Serial.println(motor_speed);

  delay(10);
}
