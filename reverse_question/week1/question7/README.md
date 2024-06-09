---
enabled: true
name: 简单计算器
category: 一级 Reverse
url: http://ctf.nbs.jonbgua.com:32117/ezre?token={token}
index: 210
flags:
- name:
  score: 1
  type: expr
  flag: f"flag{{calculation_is_ready_{md5('calculation'+token)[4:12]}}}"
---
萌新实现了一个新的编程语言
实现big_num作为code的简单加密器

hint:
- 如果久久没有进展，可以试试在还原逻辑后的源码上做些调试
- be patient


