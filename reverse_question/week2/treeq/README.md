---
enabled: true
name: 梦话
category: 一级 Reverse
url:
index: 210
flags:
- name:
  score: 25
  type: expr
  flag: f"flag{{sleep_talking_interpreter_{md5('sleep'+token)[4:12]}}}"
---
你的室友在睡觉时说了一连串秘密数字
你决定记在本子上
还好会逆向的你
还原出了他的话
