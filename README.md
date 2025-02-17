# AI-Powered LED Control Agent Using ESP8266 WiFi Controller

### Introduction

The project involves developing an AI-driven agent designed to efficiently manage an ESP32 module for precise LED control.
This system supports dynamic lighting effects, remote operation, and intelligent automation for diverse applications. 
It enables full remote access, with the ESP32 configured in Access Point Mode for WiFi connectivity.

### Overview of the Implementation

Python Code Integration with GPT-4
A Python script has been developed to interface with GPT-4. 
The key for GPT-4 integration was obtained from the website aval.ir.
The script listens to any prompt received via the serial port, forwards it to GPT-4, and retrieves a response.
Based on the dictionary message structure in the Python code, the response is converted into a specific command. 
This command is written back to the serial port for further processing.

### Thechnical  Details On Each Part

The Python script utilizes the LangChain OpenAI library to connect to GPT-4 via the provided API key. 
The API setup ensures that the AI can process user inputs and respond with appropriate commands based on the specified system prompt. 
The structured system prompt limits the AI's response to predefined commands (roomON, roomOFF, kitchenON, kitchenOFF), ensuring clarity and precision.
The serial module establishes a connection to the ESP32 board via the specified COM port and baud rate. 
This connection is crucial for transmitting prompts from the ESP32 to the Python script and sending commands back to the ESP32 for execution.
The function get_ai_command processes the prompt received from the ESP32, queries GPT-4, and retrieves a response. 
It ensures that only valid commands are returned by filtering unnecessary or invalid responses.
The send_command_to_esp function appends a newline character to the AI command and sends it back to the ESP32 through the serial port. 
This ensures the command is properly terminated and recognized by the ESP32.
The main function continuously listens for prompts from the ESP32. 
Upon receiving a valid prompt, it queries GPT-4 for a command, which is then transmitted back to the ESP32. 
The loop architecture ensures real-time responsiveness.

### C++ Code Implementation on Arduino

A C++ program was written using the Arduino IDE to handle the commands received via the serial port. 
The program interprets the commands and performs predefined operations on the ESP32 board. 
For example, commands control LED patterns, brightness levels, or turn LEDs on/off.
Once the operation is executed on the board,the result is sent back to the user's Android device through the WiFi controller.
The Android app acts as the user interface, allowing the user to send prompts, receive results, and control the board remotely.

### Thechnical  Details On Each Part

The ESP8266 is configured as an Access Point with a predefined SSID and password, enabling devices to connect directly without requiring an external WiFi network. 
The server listens on port 8888 for client connections, allowing communication with the Android app.
Commands sent by the Python script are read via the serial port and processed in the executeCommand function. 
Each command triggers specific operations, such as turning LEDs on or off (roomON, roomOFF) or enabling blinking (kitchenON, kitchenOFF).
The handleBlinking function uses a non-blocking approach to toggle the LED state based on a timer. 
This ensures that other operations can continue without being interrupted by the blinking logic.
The program sends acknowledgments back to the Android app, confirming the successful execution of commands. 
This ensures the user receives real-time feedback on their actions.

### Workflow

1.	User Input: The user sends a prompt from the Android app via the WiFi controller.
2.	Serial Communication: The prompt is received by the ESP32 via the serial port.
3.	Python Script Processing:
      * The prompt is forwarded to GPT-4 using the API key.
      * GPT-4 generates a command based on the predefined dictionary structure.
      *  The command is sent back through the serial port.
4.	C++ Code Execution: The Arduino program processes the command and performs the corresponding operation on the ESP32 board.
5.	Result Transmission: The result is sent back to the Android app via WiFi for user review.

### Additional feature 

Our system supports multiple actions which is on demond for the user side that gpt4 must return multiple commands separated by comma because the prompt indicates different actions.
This part is handled in python code

Here’s a part in main :

>if len(commands) > 1:
  > time.sleep(4)


Here’a a part in dictionary message :

>If the user's prompt requires multiple actions, respond with a comma-separated list of commands.
>For example: "kitchenON,roomOFF".





