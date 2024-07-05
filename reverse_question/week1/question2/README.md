---
enabled: true
name: flag 验证机(I)
category: 一级 Reverse
url: 
index: 210
flags:
- name:
  score: 20
  type: expr
  flag: f"flag{{JU5t_x03_1t_{md5('Encrypt10n'+token)[4:12]}_{md5('Encrypt10n'+token)[12:20]}}}"
---
他会告诉你，你的flag是否正确
但不要想他会像第一题那样把flag不加掩饰的放在程序里
看看他的encrypt做了些什么吧