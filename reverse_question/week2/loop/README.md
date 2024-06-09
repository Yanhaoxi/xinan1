---
enabled: true
name: 瞒天过海
category: 一级 Reverse
url: http://ctf.nbs.jonbgua.com:32117/ezre?token={token}
index: 210
flags:
- name:
  score: 30
  type: expr
  flag: f"flag{{equal_sign_is_overloaded_{md5('loop'+token)[4:12]}}}"
---
不小心弄坏妹妹玩具的你想起了在信安实践学习的逆向工程
稍微一看玩具的内部结构，你就知道该怎么做了
