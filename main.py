from langchain_openai import ChatOpenAI

llm = ChatOpenAI(model="gpt-4o-mini",
                 base_url="https://api.avalai.ir/v1",
                 api_key="aa-f0QUZKi3ybTwtTRQhEUA8MI9OHt3aaYFX5gf3KliWw4ykU4t")

result = llm.invoke("hello")
print(result.content)

