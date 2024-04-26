# 参考资料
# https://docs.python-requests.org/en/latest/user/quickstart/
# https://docs.python-requests.org/en/latest/api/


import requests

# 发送请求
x = requests.get('https://portal.dahuatech.com/')

# 返回网页内容
# print(x.text)

print("staus:",x.status_code)  # 获取响应状态码
print("headers:",x.headers)  # 获取响应头
print("content:",x.content)  # 获取响应内容

# 返回 json 数据
x = requests.get('https://www.runoob.com/try/ajax/json_demo.json')
print(x.json())