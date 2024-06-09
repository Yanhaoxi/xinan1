---
enabled: true
name: main不是一切
category: 一级 Reverse
url: http://ctf.nbs.jonbgua.com:32117/ezre?token={token}
index: 210
flags:
- name:
  score: 30
  type: expr
  flag: f"flag{{m41n_1s_n0t_411_{md5('1st_to_solve'+token)[4:12]}}}"
---
启动密码是flag的flag验证机被人动了手脚竟然打不开了  
快用ida找出启动它的密码  
并找出正确的flag  

hint: 
- IDA 上侧工具栏 view -> open subviews -> strings 可以检索字符串  
- IDA 左侧有函数列表  
- IDA x(查看引用的快捷键)  
- 本题建议详细阅读本次课程的pdf  
- IDA 有时候不能识别GBK(中文编码)参见第二次pdf最后部分  

