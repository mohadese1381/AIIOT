#include <ESP8266WiFi.h>

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

WiFiServer server(8888); // Define the server to listen on port 8888
const int ledPin = LED_BUILTIN; // Define LED pin (on-board LED)

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);

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

    String clientData = "";  // Variable to store the received data from the client
    while (client.connected()) { // While the client is connected
      while (client.available()) { // If data is available from the client
        clientData = Serial.readStringUntil('\n');        // Append the character to clientData
      }

      // If we have received some data
      if (clientData.length() > 0) {
        Serial.print("Received data: ");
        Serial.println(clientData);  // Print the received data

        // Handle different commands based on the exact received character
        if (clientData == "A") {
          digitalWrite(ledPin, LOW);  // Turn off the LED
        }
        if (clientData == "B") {
          digitalWrite(ledPin, HIGH); // Turn on the LED
        }
        if (clientData == "C") {
          digitalWrite(ledPin, HIGH); // Blink the LED
          delay(500);
          digitalWrite(ledPin, LOW);
          delay(500);
        }
        if (clientData == "D") {
          digitalWrite(ledPin, HIGH); // Turn on the LED
        }

        // Send a response back to the client
        client.print("Message received: ");
        client.print(clientData); // Echo back the received data

        clientData = "";  // Reset the clientData string for the next input
        break;  // Exit the loop once the data is processed
      }
    }
  }

  delay(100); // Small delay to avoid excessive CPU usage
}
