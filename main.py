from langchain_openai import ChatOpenAI

# API setup

llm = ChatOpenAI(model="gpt-4o-mini",
                 base_url="https://api.avalai.ir/v1",
                 api_key="aa-f0QUZKi3ybTwtTRQhEUA8MI9OHt3aaYFX5gf3KliWw4ykU4t")
prompt = "The room is too dark; I need more light"
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
text.""",
 },
 {
 "role": "user",
 "content": prompt
 },
]
result = llm.invoke(message)
print(result.content)


