import random
flag='_yr_gladoebyae_esr2e1a4pluf_at{8}9f'
numbers=v5 = [
    20, 23, 10, 22, 34, 32, 25, 31, 6, 11,
    27, 16, 7, 14, 17, 29, 30, 8, 26, 24,
    12, 33, 18, 28, 9, 13, 4, 2, 15, 5,
    19, 1, 3, 21, 35
]

flag_list = [i for i in flag]
flag_list.sort()
numbers_list = [i for i in numbers]
numbers_list.sort()
result=''
for i in range(len(numbers_list)):
    tmp=numbers_list.index(numbers[i])
    result+=flag_list[tmp]
    numbers_list[tmp]='_'
print(result)
# 发现分数的计算是，战利品乘以权重，那么大权重对应大字符码即可
