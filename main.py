import serial
from langchain_openai import ChatOpenAI

# API setup
llm = ChatOpenAI(model="gpt-4o-mini",
                 base_url="https://api.avalai.ir/v1",
                 api_key="aa-f0QUZKi3ybTwtTRQhEUA8MI9OHt3aaYFX5gf3KliWw4ykU4t")
prompt = "The room is too dark; I need more light"

# Serial communication setup
SERIAL_PORT = "COM3"
BAUD_RATE = 9600

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
except Exception as e:
    print(f"Error connecting to serial port: {e}")
    exit()


# Send Prompt to AI and get response
def get_ai_command(prompt):
    message = [
        {
            "role": "system",
            "content": """You are an assistant for an IoT system that
            controls LED lights. Based on the user's prompt, you must decide which
            function to call for controlling the lights.
            - If the input is related to the room, you must decide whether to turn on or off the light on pin 4.
            - If the input is related to the kitchen, you must decide whether to turn on or off the light on pin 33.
            The function options are:
              - 4ON: Turn ON the light on pin 4 (room).
              - 4OFF: Turn OFF the light on pin 4 (room).
              - 33ON: Turn ON the light on pin 33 (kitchen).
              - 33OFF: Turn OFF the light on pin 33 (kitchen).

            You must only respond with a single word (33ON, 33OFF, 4ON, 4OFF)
            corresponding to the function. DO NOT add any other information or
            text."""
        },
        {
            "role": "user",
            "content": prompt
        }
    ]
    try:
        response = llm.invoke(message)
        return response.content.strip()
    except Exception as e:
        print(f"Error communicating with OpenAI: {e}")
        return None


# Write command on serial port for esp
def send_command_to_esp(command):
    try:
        ser.write(command.encode())
        print(f"Sent command to ESP: {command}")
    except Exception as e:
        print(f"Error sending command to ESP: {e}")


def main():
    while True:
        prompt = input("Enter your command (or 'exit' to quit): ")
        if prompt.lower() == "exit":
            print("Exiting...")
            break

        ai_command = get_ai_command(prompt)
        if ai_command:
            print(f"AI decided: {ai_command}")
            send_command_to_esp(ai_command)
        else:
            print("AI could not generate a valid command.")


if __name__ == "__main__":
    main()
