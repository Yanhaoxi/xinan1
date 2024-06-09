---
enabled: true
name: 老实的命令行程序
category: 一级 Reverse
url: http://ctf.nbs.jonbgua.com:32117/ezre?token={token}
index: 210
flags:
- name:
  score: 20
  type: expr
  flag: f"flag{{4_humbl3_c0mm4nd_l1n3_pr0gr4m_{md5('We1c0me'+token)[4:12]}}}"
---
password赤裸地放在程序里
快在命令行里喊出"flag"
你会得到你想要的
如果你的password正确的话（