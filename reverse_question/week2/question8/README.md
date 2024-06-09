---
enabled: true
name: 终极加密方案
category: 一级 Reverse
url: http://ctf.nbs.jonbgua.com:32117/ezre?token={token}
index: 210
flags:
- name:
  score: 1
  type: expr
  flag: f"flag{{you_are_final_w1nn3r1_{md5('final_Encrypt10n'+token)[4:12]}}}"
---
如果全被你做出来那我岂不是很没有面子
把代基、线代糅合在一起的白盒加密肯定能保护住flag的秘密

hint:
- 可能有些难度，需要一些想法