---
enabled: true
name: 错乱的程序
category: 一级 Reverse
url: http://ctf.nbs.jonbgua.com:32117/ezre?token={token}
index: 210
flags:
- name:
  score: 20
  type: expr
  flag: f"flag{{typ3_c0nFus10n_{md5('Chao'+token)[4:12]}}}"
---
程序出现了一些问题类型出现了混乱
本该输出的字符变成了32位的整数
按照程序说的做，他会把flag给你的
如果你能理解它说的（