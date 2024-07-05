---
enabled: true
name: flag 验证机(II)
category: 一级 Reverse
url:
index: 210
flags:
- name:
  score: 20
  type: expr
  flag: f"flag{{brut3_f0rc3_1s_4wes0m3_{md5('Encrypt20n'+token)[4:12]}}}"
---
他会告诉你，你的flag是否正确
但这次的加密会更加复杂
如果没法正面解密，试试别的办法吧
