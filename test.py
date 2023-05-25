import requests

res = requests.get("http://127.0.0.1:4242/index.html")

print(res.status_code)
print(res.content)