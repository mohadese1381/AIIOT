#define ROOM_LED_PIN 4
#define KITCHEN_LED_PIN 33

void setup() {
  Serial.begin(9600); 
  pinMode(ROOM_LED_PIN, OUTPUT); 
  pinMode(KITCHEN_LED_PIN, OUTPUT); 
  digitalWrite(ROOM_LED_PIN, LOW); 
  digitalWrite(KITCHEN_LED_PIN, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); 
    command.trim(); 

    if (command == "4ON") {
      digitalWrite(ROOM_LED_PIN, HIGH);
      Serial.println("Room light turned ON");
    } else if (command == "4OFF") {
      digitalWrite(ROOM_LED_PIN, LOW);
      Serial.println("Room light turned OFF");
    } else if (command == "33ON") {
      digitalWrite(KITCHEN_LED_PIN, HIGH);
      Serial.println("Kitchen light turned ON");
    } else if (command == "33OFF") {
      digitalWrite(KITCHEN_LED_PIN, LOW);
      Serial.println("Kitchen light turned OFF");
    } else {
      Serial.println("Invalid command");
    }
  }
}
