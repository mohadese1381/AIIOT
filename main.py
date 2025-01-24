from langchain_openai import ChatOpenAI

llm = ChatOpenAI(model="gpt-4o-mini",
                 base_url="https://api.avalai.ir/v1",
                 api_key="aa-f0QUZKi3ybTwtTRQhEUA8MI9OHt3aaYFX5gf3KliWw4ykU4t")
prompt = "The second room has too much light; it doesn't feel right."
message = [
 {
 "role": "system",
 "content": """You are an assistant for an IoT system that
controls LED lights. Based on the user's prompt, you must decide which
function to call for controlling the lights.
 The function options are:
 A: turning on the light number 1,
 B: turning off the light number 1,
 C: turning on the light number 2,
 D: turning off the light number 2,
 E: turning on the light number 3,
 F: turning off the light number 3.
 You must only respond with a single character (A, B, C, D, E, or F)
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


