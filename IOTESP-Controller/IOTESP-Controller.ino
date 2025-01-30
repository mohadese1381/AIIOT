#include <ESP8266WiFi.h>

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

WiFiServer server(8888); // Define the server to listen on port 8888
const int ledPin = LED_BUILTIN; // Built-in LED pin for status

String clientData = "";  // Variable to store the received data from the client
bool isBlinking = false; // Flag to check if the LED is blinking
unsigned long previousMillis = 0; // Timer for blinking
const long blinkInterval = 500; // Blinking interval in milliseconds

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // Turn off LED initially (active LOW)
  
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
    client.setTimeout(2000); // Set timeout for client communication

    while (client.connected()) {
      while (client.available()) {
        char c = client.read(); // Read one character at a time
        clientData += c;        // Append the character to clientData
      }

      // Process the received data
      if (clientData.length() > 0) {
        Serial.print("Received Prompt from Client: ");
        Serial.println(clientData);

        // Send prompt to the serial port for the Python script
        Serial.println("Prompt:" + clientData); // Send to Python
        clientData = ""; // Reset clientData for next input
      }

      // Check for a command from the Python script
      if (Serial.available()) {
        String command = Serial.readStringUntil('\n'); // Read the response
        command.trim(); // Remove whitespace and newline characters
        Serial.print("Command from Python: ");
        Serial.println(command);

        // Execute the command
        executeCommand(command);

        // Send acknowledgment back to the client
        client.println("Command executed: " + command);
      }

      // Handle blinking if enabled
      handleBlinking();
    }
    client.stop(); // Close the client connection
    Serial.println("Client Disconnected");
  }
}

void executeCommand(String command) {
  if (command == "roomON") {
    isBlinking = false;            // Stop blinking
    digitalWrite(ledPin, LOW);     // Turn on the LED (active LOW)
  } else if (command == "roomOFF") {
    isBlinking = false;            // Stop blinking
    digitalWrite(ledPin, HIGH);    // Turn off the LED
  } else if (command == "kitchenON") {
    isBlinking = true;             // Start blinking
  } else if (command == "kitchenOFF") {
    isBlinking = false;            // Stop blinking
    digitalWrite(ledPin, HIGH);    // Turn off the LED
  } else {
    Serial.println("Invalid command received: " + command);
  }
}

void handleBlinking() {
  if (isBlinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle LED state
    }
  }
}