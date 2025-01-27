#include <ESP8266WiFi.h>

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

WiFiServer server(8888); // Define the server to listen on port 8888
const int ledPin = LED_BUILTIN;

String clientData = "";  // Variable to store the received data from the client
bool isBlinking = false; // Flag to check if the LED is blinking

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Serial.println("Setting up Access Point...");
  WiFi.softAP(ssid, password);  
  server.begin(); // Start the server

  Serial.println("Server started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP()); // Print the IP address of the ESP8266
}

void loop() {
  WiFiClient client = server.available(); // Check if there's a client connected
  if (client) {
    Serial.println("New Client Connected");

    while (client.connected()) {
        
      // Read the data from the client
      while (client.available()) { // If data is available from the client
        char c = client.read();  // Read one character
        clientData += c;         // Append the character to clientData
      }

      // If we have received some data
      if (clientData.length() > 0) {
        Serial.print("Prompt: ");
        Serial.println(clientData);  // Print the received data
               
        delay(2000);  // Slight delay to handle commands properly

        // If serial input is available, read the command
        if (Serial.available()) {
          String promptResponse = Serial.readStringUntil('\n'); // Read the input
          Serial.print("Received: ");
          Serial.println(promptResponse);

          if (promptResponse == "roomON") {
            isBlinking = false;  // Stop blinking if any command is received
            digitalWrite(ledPin, LOW);  // Turn on the LED (room)
          }
          else if (promptResponse == "roomOFF") {
            isBlinking = false;  // Stop blinking if any command is received
            digitalWrite(ledPin, HIGH); // Turn off the LED (room)
          }
          else if (promptResponse == "kitchenOFF") {
            isBlinking = false;  // Stop blinking if any command is received
            digitalWrite(ledPin, HIGH); // Turn off the LED (kitchen)
          }
          else if (promptResponse == "kitchenON") {
            isBlinking = true;  // Start blinking the LED (kitchen)
          }
          else {
            Serial.println("Wrong input");
          }
        }

        // Send a response back to the client
        client.print("Message received: ");
        client.print(clientData); // Echo back the received data

        clientData = "";  // Reset the clientData string for the next input
      }

      // Blinking logic for kitchenON command (interruptible)
      if (isBlinking) {
        unsigned long currentMillis = millis();
        static unsigned long previousMillis = 0;
        const long interval = 500;

        if (currentMillis - previousMillis >= interval) {
          // Save the last time you blinked the LED
          previousMillis = currentMillis;
          
          // Blink the LED
          digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle the LED state
        }
      } 
      else {
        // If not blinking, keep the LED in the desired state (on/off)
        // For example, after turning on the kitchen, stop blinking:
        if (digitalRead(ledPin) == LOW && !isBlinking) {
          digitalWrite(ledPin, LOW);  // Ensure LED is on
        } else if (digitalRead(ledPin) == HIGH && !isBlinking) {
          digitalWrite(ledPin, HIGH);  // Ensure LED is off
        }
      }
    }
  }

  delay(100); // Small delay to avoid excessive CPU usage
}