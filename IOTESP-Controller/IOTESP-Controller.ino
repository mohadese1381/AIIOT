#include <WiFi.h>
#include <WebServer.h>


const char* ssid = "ESP32-AccessPoint";
const char* password = "یه چیز بذار"; 

WebServer server(80);

#define ROOM_LED_PIN 4
#define KITCHEN_LED_PIN 33

void setup() {

  Serial.begin(9600);

  pinMode(ROOM_LED_PIN, OUTPUT);
  pinMode(KITCHEN_LED_PIN, OUTPUT);
  digitalWrite(ROOM_LED_PIN, LOW); // Turn off LEDs initially
  digitalWrite(KITCHEN_LED_PIN, LOW);

  // Set up the ESP32 as an access point
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP address: ");
  Serial.println(IP);

  server.on("/prompt", HTTP_POST, []() {
    if (server.hasArg("plain")) {
      String prompt = server.arg("plain"); 
      Serial.println(prompt); 

      // Wait for AI to respond:)
      while (!Serial.available()) {
        delay(100);
      }
      String command = Serial.readStringUntil('\n');
      command.trim();
      Serial.println("Command received from Python: " + command);

      if (command == "4ON") {
        digitalWrite(ROOM_LED_PIN, HIGH);
      } else if (command == "4OFF") {
        digitalWrite(ROOM_LED_PIN, LOW);
      } else if (command == "33ON") {
        digitalWrite(KITCHEN_LED_PIN, HIGH);
      } else if (command == "33OFF") {
        digitalWrite(KITCHEN_LED_PIN, LOW);
      }

      // Send response back to the client
      server.send(200, "text/plain", "Command executed: " + command);
    } else {
      server.send(400, "text/plain", "No prompt received!");
    }
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); 
}
