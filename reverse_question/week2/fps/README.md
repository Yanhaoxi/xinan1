---
enabled: true
name: 超级游戏大师
category: 一级 Reverse
url: 
index: 210
flags:
- name:
  score: 15
  type: expr
  flag: f"flag{{you_are_best_player_{md5('Winner'+token)[4:13]}}}"
---
成为超级游戏大师
超过yhx的世界游戏记录来获取属于你的荣耀flag
（需要全屏游玩，否则地图打印会有问题）

tips:只需要注意重要的部分